//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/UiDecl.h>

namespace toy
{
	void Modal::decl(UiNode& node)
	{
		Query& current_query = m_queries[m_current_step];
		auto callback = [&](Var value) { current_query.m_result = value; current_query.m_done = true; };
		node.subdecl(current_query.m_decl, callback);
		if(current_query.m_done)
			m_current_step++;
		if(m_current_step == m_queries.size())
			this->done();
	}

	void Modal::done()
	{
		VarVector results;
		for(Query& query : m_queries)
			results.push_back(query.m_result);
		m_callback(results);
	}
}
