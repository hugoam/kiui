//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TABLE_H
#define TOY_TABLE_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Table : public Wedge
	{
	public:
		Table(const Params& params, StringVector columns, std::vector<float> weights);

		virtual void makeSolver();

		void resize(Frame& first, Frame& second);

	protected:
		StringVector m_columns;
		std::vector<float> m_weights;

	public:
		GridSheet m_head;
	};
}

#endif
