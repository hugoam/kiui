//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Object/mkObjectConfig.h>
#include <Object/String/mkString.h>

#include <algorithm>

namespace mk
{
	StringVector splitString(const string& str, const string& separator)
	{
		StringVector result;
		
		if(str.size() == 0)
			return result;

		size_t cur_pos = 0;
		size_t last_pos = 0;

		while (cur_pos != string::npos)
		{
			cur_pos = str.find(separator, last_pos);
			result.push_back(str.substr(last_pos, cur_pos - last_pos));
			last_pos = cur_pos + separator.size();
		}

		return result;
	}

	string replaceAll(string const& original, string const& before, string const& after)
	{
		string retval;
		string::const_iterator end = original.end();
		string::const_iterator current = original.begin();
		string::const_iterator next = std::search(current, end, before.begin(), before.end());
		while(next != end)
		{
			retval.append(current, next);
			retval.append(after);
			current = next + before.size();
			next = std::search(current, end, before.begin(), before.end());
		}
		retval.append(current, next);
		return retval;
	}
}
