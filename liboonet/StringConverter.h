#ifndef OONET_STRING_CONVERTER_H_DEFINED
#define OONET_STRING_CONVERTER_H_DEFINED

#include "OONet.h"
#include "Exception.h"

namespace OONet
{
	class StringConverter
	{
	private:
		wstring wide_string;		// Unicode string codec

		// Internal tools
		wstring _convert_to_wide(const string &r);
		string _convert_to_mbr(const wstring &r);
	public:

		// Construct by Ansi String
		inline StringConverter(const string & r)
		{	wide_string = _convert_to_wide(r);	}

		// Construct by Unicode String
		inline StringConverter(const wstring & r)
		{	wide_string = r;		}

		// Copy constructor
		inline StringConverter(const StringConverter & r)
		{	wide_string = r.wide_string;	}

		// Copy operator
		inline StringConverter & operator=(const StringConverter & r)
		{	wide_string = r.wide_string;
			return *this;
		}

		// Cast operator to Unicode
		inline operator const wstring & ()
		{	return wide_string;	}

		// Cast operator to Ansii
		inline operator string ()
		{	return _convert_to_mbr(wide_string);	}

		// Cast to Unicode
		inline const wstring & toWide()
		{	return wide_string;	}

		// Cast to Ansi
		inline string toMbr()
		{	return _convert_to_mbr(wide_string);	}

		// Cast to current selected character type
#if (OONET_CHAR == OONET_CHAR_WIDE)
		inline c wstring & toCurrent()
		{	return wide_string;	}
#else
		inline string toCurrent()
		{	return _convert_to_mbr(wide_string);	}
#endif
	};
};

#endif // !OONET_STRING_CONVERTER_H_DEFINED
