//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_STRINGCONVERT_H_INCLUDED
#define MK_STRINGCONVERT_H_INCLUDED

/* Basic headers */
#include <Object/mkObjectForward.h>
#include <Object/mkObject.h>
#include <Object/mkStem.h>
#include <Object/mkRef.h>
#include <Object/String/mkString.h>

#include <memory>
#include <sstream>

namespace mk
{
	template <class T>
	inline T fromString(const string& str)
	{
		return AsString<T>::from(str);
	}

	template <class T>
	inline void fromString(const string& str, T& val)
	{
		AsString<T>::from(str, val);
	}

	template <class T>
	inline string toString(const T& val)
	{
		return AsString<T>::to(val);
	}

	template <class T>
	inline void toString(const T& val, string& str)
	{
		return AsString<T>::to(val, str);
	}

	// string - string conversion
	template <> inline string fromString<string>(const string& str) { return str; }
	template <> inline void fromString<string>(const string& str, string& val) { val = str; }

	template <> inline string toString<string>(const string& val){ return val; }
	template <> inline void toString<string>(const string& val, string& str){ str = val; }

	template <class T>
	inline void string_to_type(const string& str, T& val)
	{
		std::stringstream ss(str);
		ss >> val;
	}

	template <class T>
	inline void type_to_string(const T& val, string& str)
	{
		std::stringstream ss;
		ss << val;
		str += ss.str();
	}

	// Vector - string con*version
	template <class T>
	inline void vector_to_string(const T& val, string& str)
	{
		for(const typename T::value_type& v : val)
		{
			toString(v, str);
			str += ",";
		}
		if(val.size() > 0)
			str.pop_back();
	}

	template <class T>
	inline string vector_to_string(const T& val)
	{
		string str;
		vector_to_string(val, str);
		return str;
	}

	template <class T>
	inline void string_to_vector(const string& str, T& vec)
	{
		auto first = str.begin();
		auto end = str.end();
		auto second = std::find(first, end, ',');

		while(true)
		{
			second = std::find(first, end, ',');
			vec.push_back(fromString<typename T::value_type>(str.substr(first - str.begin(), second - first)));
			
			if(second != end)
				first = second + 1;
			else
				break;
		}
	}

	template <class T>
	inline T string_to_vector(const string& str)
	{
		T vec;
		string_to_vector(str, vec);
		return vec;
	}

	template <class T, size_t size>
	inline void fixed_vector_to_string(const T& val, string& str)
	{
		for(size_t i = 0; i < size; ++i)
		{
			toString(val[i], str);
			str += ",";
		}
		str.pop_back();
	}

	template <class T, size_t size>
	inline string fixed_vector_to_string(const T& val)
	{
		string str;
		fixed_vector_to_string<T, size>(val, str);
		return str;
	}

	template <class Vec, class T>
	inline void string_to_fixed_vector(const string& str, Vec& vec)
	{
		auto first = str.begin();
		auto end = str.end();
		auto second = std::find(first, end, ',');

		size_t i = 0;
		while(true)
		{
			second = std::find(first, end, ',');
			//vec[i] = strtk::string_to_type_converter<T>(first, second);
			vec[i] = fromString<T>(str.substr(first - str.begin(), second - first));

			++i;
			if(second != end)
				first = second + 1;
			else
				break;
		}
	}


	template <class T, bool isobject = std::is_base_of<Object, BareType<T>::type>::value, bool isenum = std::is_enum<T>::value>
	struct AsString
	{
		static inline void to(const T& val, string& str) { type_to_string(val, str); }
		static inline string to(const T& val) { string str; type_to_string(val, str); return str; }

		static inline T from(const string& str) { T val; string_to_type<T>(str, val); return val; }
		static inline void from(const string& str, T& val){ string_to_type<T>(str, val); }
	};

	template <class T>
	struct AsString<T, false, true>
	{
		static inline void to(const T& val, string& str) { type_to_string(static_cast<const unsigned int&>(val), str); }
		static inline string to(const T& val) { string str; type_to_string(static_cast<const unsigned int&>(val), str); return str; }

		static inline T from(const string& str) { T val; string_to_type<unsigned int>(str, val); return static_cast<T>(val); }
		static inline void from(const string& str, T& val){ string_to_type<unsigned int>(str, (unsigned int&)(val));}
	};

	template <class T>
	struct AsString<T, true, false>
	{
		static inline void to(const T& val, string& str) {}
		static inline string to(const T& val) { return ""; }

		static inline void from(const string& str, T& val) {}
		static inline T from(const string& str) { return T(); }
	};

	template <class T>
	struct AsString<std::unique_ptr<T>, false, false>
	{
		static inline void to(const std::unique_ptr<T>& val, string& str) { type_to_string(val.get(), str); }
		static inline string to(const std::unique_ptr<T>& val) { string str; type_to_string(val.get(), str); return str; }

		static inline void from(const string& str, std::unique_ptr<T>& vec) {}
		static inline std::unique_ptr<T> from(const string& str) { return std::unique_ptr<T>(); }
	};

	template <class T>
	struct AsString<std::vector<T>, false, false>
	{
		static inline void to(const std::vector<T>& val, string& str) { vector_to_string(val, str); }
		static inline string to(const std::vector<T>& val) { return vector_to_string(val); }

		static inline void from(const string& str, std::vector<T>& vec) { string_to_vector(str, vec); }
		static inline std::vector<T> from(const string& str) { return string_to_vector(str); }
	};


	// IdObject - string conversion
	template <> inline IdObject* fromString<IdObject*>(const string& str) { return nullptr; }
	template <> inline void fromString<IdObject*>(const string& str, IdObject*& val) {}

	template <> inline string toString<IdObject*>(IdObject* const& object) { return AsString<Id>::to(object->id()); }
	template <> inline void toString<IdObject*>(IdObject* const& object, string& str) { AsString<Id>::to(object->id(), str); }


	// Part - string conversion
	template <> inline Part* fromString<Part*>(const string& str) { return nullptr; }
	template <> inline void fromString<Part*>(const string& str, Part*& val) {}

	template <> inline string toString<Part*>(Part* const& part) { return AsString<Id>::to(part->stem()->id()); }
	template <> inline void toString<Part*>(Part* const& part, string& str) { AsString<Id>::to(part->stem()->id(), str); }
}

#endif // MK_STRINGCONVERT_H_INCLUDED
