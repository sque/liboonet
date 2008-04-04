#include "SubTest.h"
#include "Test.h"
#include <time.h>


namespace oonet
{
	// Constructor
	SubTest::SubTest(string Name)
		:bMustThrow(false),
		LastException("", 0, "", ""),
		CpuTimeSpent(0)
	{
		SubTestName = Name;
	}

	// Constructor for throw
	SubTest::SubTest(string Name, string ExcType)
		:bMustThrow(true),
		LastException("", 0, "", ""),
		CpuTimeSpent(0)
	{
		SubTestName = Name;
		ExceptionType = ExcType;
	}

	bool SubTest::Execute()
	{	bool bResult;

		try
		{
			StartTime = clock();
			bResult = OnExecute();
			EndTime = clock();
			if (bMustThrow) bResult = false;

		}
		catch(Exception & e)
		{	EndTime = clock();
			LastException = e;
			if ((bMustThrow) && (e.getType() == ExceptionType))
				bResult = true;
			else
				bResult = false;
		}

		// Save time
		CpuTimeSpent = (EndTime - StartTime) * 1000;
        CpuTimeSpent = CpuTimeSpent / CLOCKS_PER_SEC;
		return bResult;
	}

	// Reset timer
	void SubTest::ResetTimer()
	{
		StartTime = clock();
	}

	// Get last system error description
	string SubTest::GetSystemLastErrorDescription()
	{
#if (OONET_OS == OONET_OS_WIN32)
		char cTmpErrorString[MAX_PATH];
		DWORD uLastError;
		string FullMsgDescription;

		// Get last error
		uLastError = GetLastError();

		// Make msg with error
		_stprintf(cTmpErrorString, "Error(0x%08lX):", uLastError);
		FullMsgDescription = cTmpErrorString;

		// Get string error from system
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			uLastError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			cTmpErrorString,
			MAX_PATH,
			NULL
		);
		FullMsgDescription += cTmpErrorString;

		return FullMsgDescription;
#else
        return "unsupported";
#endif
	}
};	// !oonet namespace
