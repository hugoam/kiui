//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Frame/Frame.h>

#include <toyobj/Iterable/Reverse.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>

#include <toyui/Solver/Grid.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Style/Style.h>

#include <cmath>
#include <cassert>

namespace toy
{
	template <> string toString<DirtyLayout>(const DirtyLayout& dirty) { if(dirty == CLEAN) return "CLEAN"; else if(dirty == DIRTY_REDRAW) return "DIRTY_REDRAW"; else if(dirty == DIRTY_PARENT) return "DIRTY_PARENT"; else if(dirty == DIRTY_LAYOUT) return "DIRTY_LAYOUT"; else if(dirty == DIRTY_FORCE_LAYOUT) return "DIRTY_FORCE_LAYOUT"; else /*if(dirty == DIRTY_STRUCTURE)*/ return "DIRTY_STRUCTURE"; }

	Frame::Frame(Widget& widget)
		: UiRect()
		, d_widget(widget)
		, d_wedge(widget.isa<Wedge>() ? &widget.as<Wedge>() : nullptr)
		, d_parent(nullptr)
		, d_dirty(DIRTY_STRUCTURE)
		, d_hidden(false)
		, d_index(0, 0)
		, d_style(nullptr)
		, d_hardClip()
		, d_opacity(CLEAR)
		, d_length(DIM_NULL)
		, d_caption()
		, d_icon()
		, d_solver()
	{}

	Frame::~Frame()
	{}

	void Frame::makeSolver()
	{
		LayoutSolver type = d_style->layout().d_solver;
		FrameSolver* solver = d_parent ? d_parent->solver() : nullptr;

		if(type == FRAME_SOLVER)
			d_solver = make_object<FrameSolver>(solver, &d_style->layout(), this);
		else if(type == ROW_SOLVER)
			d_solver = make_object<RowSolver>(solver, &d_style->layout(), this);
		else if(type == GRID_SOLVER)
			d_solver = make_object<GridSolver>(solver, &d_style->layout(), this);
		else if(type == TABLE_SOLVER)
			d_solver = make_object<TableSolver>(solver, &d_style->layout(), this);

		d_solver->applySpace(d_length);
	}

	Frame& Frame::lookup(FrameType type)
	{
		if(this->frameType() < type)
			return d_parent->lookup(type);
		else
			return *this;
	}

	Layer& Frame::layer(FrameType type)
	{
		return this->lookup(type).as<Layer>();
	}

	void Frame::markDirty(DirtyLayout dirty)
	{
		this->setDirty(dirty);
		if(dirty == DIRTY_FORCE_LAYOUT)
			dirty = DIRTY_LAYOUT;
		Frame* parent = this->parent();
		while(parent)
		{
			parent->setDirty(dirty);
			parent = parent->parent();
		}
	}

	void Frame::bind(Frame& parent)
	{
		d_parent = &parent;
		d_parent->markDirty(DIRTY_STRUCTURE);
		//d_index[d_parent->d_length] = d_widget.index();
	}

	void Frame::unbind()
	{
		d_parent->markDirty(DIRTY_STRUCTURE);
		d_parent = nullptr;
	}

	void Frame::setStyle(Style& style, bool reset)
	{
		if(d_style == &style) return;
		d_style = &style;
		this->updateStyle(reset);
	}

	void Frame::updateStyle(bool reset)
	{
		d_opacity = d_style->layout().d_opacity;
		d_size = d_style->layout().d_size.val.null() ? d_size : d_style->layout().d_size;

		this->updateInkstyle(d_style->subskin(d_widget.state()));

		reset ? this->markDirty(DIRTY_STRUCTURE) : this->markDirty(DIRTY_LAYOUT);
	}

	void Frame::updateInkstyle(InkStyle& inkstyle)
	{
		if(d_inkstyle == &inkstyle) return;
		d_inkstyle = &inkstyle;
		this->markDirty(DIRTY_REDRAW);

		if(d_inkstyle->m_image.val)
			this->setIcon(d_inkstyle->m_image.val);
	}

	Caption& Frame::setCaption(const string& text)
	{
		if(!d_caption) d_caption = make_object<Caption>(*this);
		d_caption->setText(text);
		return *d_caption;
	}

	Icon& Frame::setIcon(Image* image)
	{
		if(!d_icon) d_icon = make_object<Icon>(*this);
		d_icon->setImage(image);
		return *d_icon;
	}

	DimFloat Frame::contentSize()
	{
		if(d_icon)
			return d_icon->contentSize();
		else if(d_caption)
			return d_caption->contentSize();
		return { 0.f, 0.f };
	}

	void Frame::setSizeDim(Dimension dim, float size)
	{
		if(d_size[dim] == size) return;
		d_size[dim] = size;
		this->markDirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::setSpanDim(Dimension dim, float span)
	{
		if(d_span[dim] == span) return;
		d_span[dim] = span;
		this->markDirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::setPositionDim(Dimension dim, float position)
	{
		if(d_position[dim] == position) return;
		d_position[dim] = position;
		this->markDirty(DIRTY_REDRAW);
	}

	void Frame::show()
	{
		d_hidden = false;
		this->markDirty(DIRTY_LAYOUT);
	}

	void Frame::hide()
	{
		d_hidden = true;
		this->markDirty(DIRTY_LAYOUT);
	}

	bool Frame::visible()
	{
		if(d_hidden)
			return false;
		else
			return d_parent ? d_parent->visible() : !d_hidden;
	}

	void Frame::integratePosition(Frame& root, DimFloat& global)
	{
		if(this == &root)
			return;
		
		d_parent->integratePosition(root, global);
		global.x = (global.x - d_position.x) / d_scale;
		global.y = (global.y - d_position.y) / d_scale;
	}

	void Frame::derivePosition(Frame& root, DimFloat& local)
	{
		if(this == &root)
			return;

		local.x = d_position.x + local.x * d_scale;
		local.y = d_position.y + local.y * d_scale;
		d_parent->derivePosition(root, local);
	}

	float Frame::deriveScale(Frame& root)
	{
		if(this == &root)
			return d_scale;
		else 
			return d_parent->deriveScale(root) * d_scale;
	}

	bool Frame::inside(const DimFloat& pos)
	{
		return (pos.x >= 0.f && pos.x <= d_size.x
			 && pos.y >= 0.f && pos.y <= d_size.y);
	}

	void Frame::setHardClip(const BoxFloat& hardClip)
	{
		d_hardClip = hardClip;
		if(d_parent)
			d_parent->setHardClip(hardClip);
	}

	bool Frame::first(Frame& frame)
	{
		return &frame.d_widget == d_wedge->contents().front();
	}

	bool Frame::last(Frame& frame)
	{
		return &frame.d_widget == d_wedge->contents().back();
	}

	Frame* Frame::pinpoint(DimFloat pos, const Filter& filter)
	{
		if(this->hidden() || this->hollow() || (this->clip() && !this->inside(pos)))
			return nullptr;

		if(d_wedge)
			for(Widget* widget : reverse_adapt(d_wedge->contents()))
			{
				DimFloat local = widget->frame().integratePosition(pos, *this);
				Frame* target = widget->frame().pinpoint(local, filter);
				if(target)
					return target;
			}

		if(filter(*this) && this->inside(pos))
			return this;
		return nullptr;
	}

	void Frame::transferPixelSpan(Frame& prev, Frame& next, float pixelSpan)
	{
		float pixspan = 1.f / this->d_size[d_length];
		float offset = pixelSpan * pixspan;

		prev.setSpanDim(d_length, std::max(0.01f, prev.d_span[d_length] + offset));
		next.setSpanDim(d_length, std::max(0.01f, next.d_span[d_length] - offset));
		this->markDirty(DIRTY_FORCE_LAYOUT);
	}

	void Frame::relayout()
	{
		DirtyLayout dirty = this->clearDirty();
		if(!dirty) return;

		if(dirty >= DIRTY_STRUCTURE)
		{
			d_wedge->visit([](Widget& widget, bool&)
			{
				widget.makeSolver();
			});
		}

		SolverVector solvers;
		for(Widget* widget : d_wedge->contents())
			widget->frame().collect(solvers, dirty);

		d_solver->reset();
		d_solver->d_size = d_size;

		this->relayout(solvers);
	}

	void Frame::collect(SolverVector& solvers, DirtyLayout dirtyTop)
	{
		if(dirtyTop >= DIRTY_FORCE_LAYOUT)
			this->setDirty(DIRTY_FORCE_LAYOUT);
		else if(dirtyTop >= DIRTY_LAYOUT)
			this->setDirty(DIRTY_PARENT);

		if(d_hidden || !d_dirty)
			return;

		//this->debugPrintDepth();
		//printf(" >> %s %s\n", d_style->name().c_str(), toString(d_dirty).c_str());

		if(d_dirty >= DIRTY_PARENT)
		{
			d_solver->collect(solvers);
			d_widget.dirtyLayout();
		}

		if(d_dirty >= DIRTY_REDRAW)
		{
			this->layer().setRedraw();
			this->layer().setForceRedraw(); // @ kludge for nodes in canvas when moving the canvas window
		}

		if(d_wedge)
			for(Widget* widget : d_wedge->contents())
				widget->frame().collect(solvers, d_dirty);

		this->clearDirty();
	}

	void Frame::relayout(SolverVector& solvers)
	{
		//for(FrameSolver* solver : solvers)
		//	solver->sync();

		for(FrameSolver* solver : reverse_adapt(solvers))
			solver->compute();

		for(FrameSolver* solver : solvers)
			solver->layout();

		for(FrameSolver* solver : solvers)
			solver->read();
	}

	void Frame::syncSolver(FrameSolver& solver)
	{
		if(d_caption || d_icon)
		{
			DimFloat content = (d_caption ? d_caption->updateTextSize() : d_icon->contentSize()) + d_inkstyle->m_padding.val.size();
			solver.setup(d_position, d_size, d_span, &content);
		}
		else
		{
			solver.setup(d_position, d_size, d_span, nullptr);
		}

		if(d_dirty == DIRTY_PARENT)
		{
			// @bug this causes a bug in the relayout if we want to implement scarce behavior for wrap frames, since here the content is instead just the unpadded size
			solver.d_content = d_size - solver.d_style->d_padding.val.size();
		}
	}

	void Frame::readSolver(FrameSolver& solver)
	{
		this->setPosition(solver.d_position);
		this->setSize(solver.d_size);
		d_span = solver.d_span;

		if(solver.d_solvers[DIM_X] && !solver.d_solvers[DIM_X]->d_frame)
			d_position = d_position + solver.d_solvers[DIM_X]->d_position;
	}

	void Frame::debugPrintDepth()
	{
		Frame* parent = this->parent();
		while(parent)
		{
			printf("  ");
			parent = parent->parent();
		}
	}
}
