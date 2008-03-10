#include "./StringConverter.h"

namespace OONet
{
	wstring StringConverter::_convert_to_wide(const string &r)
	{
#if (OONET_OS == OONET_OS_WIN32)
		// Calculate size of wchar needed
		size_t sAr = r.size() * sizeof(wchar_t);

		// Allocate space
		wchar_t * pAr = new wchar_t[sAr];

		// Convert chars
		sAr = MultiByteToWideChar(CP_OEMCP, 0, r.c_str(), (int)r.size(), pAr, (int)sAr);
		if (sAr <= 0)
		{
			delete pAr;
			OONET_THROW_EXCEPTION(OONet::ExceptionConvertionUnsupported, "Cannot convert ANSI string to unicode");
		}

		// Create object
		wstring retString(pAr, sAr);

		// delete space
		delete pAr;

		// Return object
		return retString;
#else
        //! @todo Replace this code wcsrtombs family functions
        wstring wideText;
		wchar_t wideChar;
		string::const_iterator It;

		for(It = r.begin();It != r.end();It++)
		{
			wideChar = (char)*It;
			wideText += wideChar;
		}

		return wideText;
		//OONET_THROW_EXCEPTION(ExceptionUnimplemented, _T("String convertion is not supported yet on this platform!"));
#endif

	}
	string StringConverter::_convert_to_mbr(const wstring &r) 	{
#if (OONET_OS == OONET_OS_WIN32)
		// Calculate size of char needed
		size_t sAr = r.size() + 2;

		// Allocate space
		char * pAr = new char[sAr];

		// Convert chars
		sAr = WideCharToMultiByte(CP_OEMCP, 0, r.c_str(), (int)r.size(), pAr, (int)sAr, NULL, NULL);
		if (sAr <= 0)
		{
			delete pAr;
			OONET_THROW_EXCEPTION(OONet::ExceptionConvertionUnsupported, "Cannot convert unicode back to ANSI");
		}

		// Create object
		string retString(pAr, sAr);

		// delete space
		delete pAr;

		// Return object
		return retString;
#else
        //! @todo Replace this code wcsrtombs family functions
        string ansiText;
		char ansiChar;
		wchar_t wideChar;
		wstring::const_iterator It;

		for(It = r.begin();It != r.end();It++)
		{
			wideChar = *It;
			if (wideChar > 255)
				OONET_THROW_EXCEPTION(ExceptionConvertionUnsupported, _T("Cannot convert this unicode string to ansi!"));
			ansiChar = (char) wideChar;
			ansiText += ansiChar;
		}
		return ansiText;
		//OONET_THROW_EXCEPTION(ExceptionUnimplemented, _T("String convertion is not supported yet on this platform!"));
#endif
	}

};	// !OONet namespace
