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
	Frame::Frame(Widget& widget)
		: UiRect()
		, d_widget(widget)
		, d_wedge(widget.isa<Wedge>() ? &widget.as<Wedge>() : nullptr)
		, d_parent(nullptr)
		, d_dirty(DIRTY_LAYOUT)
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
		FrameSolver* solver = d_parent ? &d_parent->solver() : nullptr;

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

	void Frame::markDirty(Dirty dirty)
	{
		//if(d_style)
		//	printf("%s dirty\n", d_style->name().c_str());
		this->setDirty(dirty);
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
		d_index[d_parent->d_length] = d_widget.index();
	}

	void Frame::unbind()
	{
		d_parent->markDirty(DIRTY_STRUCTURE);
		d_parent = nullptr;
	}

	void Frame::setStyle(Style& style, bool reset)
	{
		d_style = &style;
		this->updateStyle();
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
		this->markDirty(DIRTY_CONTENT);

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
		this->markDirty(DIRTY_LAYOUT);
	}

	void Frame::setSpanDim(Dimension dim, float span)
	{
		if(d_span[dim] == span) return;
		d_span[dim] = span;
		this->markDirty(DIRTY_LAYOUT);
	}

	void Frame::setPositionDim(Dimension dim, float position)
	{
		//if(d_position[dim] == position) return;
		d_position[dim] = position;
		this->markDirty(DIRTY_LAYOUT);
		//this->setDirty(DIRTY_ABSOLUTE);
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
		global[DIM_X] = (global.x() - d_position.x()) / d_scale;
		global[DIM_Y] = (global.y() - d_position.y()) / d_scale;
	}

	void Frame::derivePosition(Frame& root, DimFloat& local)
	{
		if(this == &root)
			return;

		local[DIM_X] = d_position.x() + local.x() * d_scale;
		local[DIM_Y] = d_position.y() + local.y() * d_scale;
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
		return (pos.x() >= 0.f && pos.x() <= d_size.x()
			 && pos.y() >= 0.f && pos.y() <= d_size.y());
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
	}

	void Frame::relayout()
	{
		if(d_dirty >= DIRTY_STRUCTURE)
		{
			d_wedge->visit([](Widget& widget) -> bool
			{
				widget.makeSolver(); return true;
			});
		}

		FrameVector solvers;
		d_wedge->visit([&solvers](Widget& widget) -> bool
		{
			if(widget.frame().hidden() || !widget.frame().dirty()) return false;
			widget.frame().solver().collect(solvers);
			widget.frame().syncSolver();
			widget.frame().clearDirty();
			widget.frame().layer().setForceRedraw();
			widget.dirtyLayout();
			return true;
		});

		if(solvers.size() == 0)
			return;

		printf("Relayout %u frames\n", solvers.size());
		solvers.erase(solvers.begin());

		d_solver->reset();
		d_solver->d_size = d_size;

		for(FrameSolver* solver : reverse_adapt(solvers))
			solver->compute();

		d_solver->d_prev = nullptr;

		for(FrameSolver* solver : solvers)
			solver->layout();

		for(FrameSolver* solver : solvers)
			if(solver->d_frame)
				solver->d_frame->readSolver();
	}

	void Frame::syncSolver()
	{
		DimFloat size = d_size;

		const BoxFloat& padding = d_inkstyle->m_padding;
		if(d_caption)
			size = d_caption->updateTextSize() + DimFloat{ padding.x0(), padding.y0() } + DimFloat{ padding.x1(), padding.y1() };
		else if(d_icon)
			size = d_icon->contentSize() + DimFloat{ padding.x0(), padding.y0() } + DimFloat{ padding.x1(), padding.y1() };

		d_solver->setup(d_position, size, d_span);
	}

	void Frame::readSolver()
	{
		this->setPosition(d_solver->d_position);
		this->setSize(d_solver->d_size);
		d_span = d_solver->d_span;
		d_length = d_solver->d_length;

		if(d_solver->d_solvers[DIM_X] && !d_solver->d_solvers[DIM_X]->d_frame)
			d_position = d_position + d_solver->d_solvers[DIM_X]->d_position;
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
