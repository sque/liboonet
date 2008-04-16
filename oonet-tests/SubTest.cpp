#include "SubTest.h"
#include "Test.h"
#if OONET_OS == OONET_OS_LINUX
	#include <sys/time.h>
	#include <time.h>
#else
#endif
namespace oonet
{
#if OONET_OS == OONET_OS_LINUX
	double get_current_msecs()
	{	struct timeval t;
		double tmp_out;

		gettimeofday(&t, NULL);
		tmp_out = t.tv_sec * 1000.0;
		tmp_out += ((double)t.tv_usec /1000.0);

		return tmp_out;
	}
#elif OONET_OS == OONET_OS_WIN32
	double get_current_msecs()
	{	
		double tm = timeGetTime();
		return tm;
	}
#endif

	// Constructor
	SubTest::SubTest(string Name)
		:bMustThrow(false),
		LastException("", 0, "", ""),
		CpuTimeSpent(0.0)
	{
		SubTestName = Name;
	}

	// Constructor for throw
	SubTest::SubTest(string Name, string ExcType)
		:bMustThrow(true),
		LastException("", 0, "", ""),
		CpuTimeSpent(0.0)
	{
		SubTestName = Name;
		ExceptionType = ExcType;
	}

	// Get current time
	double SubTest::TimePassed()
	{	return get_current_msecs() - StartTime;	}

	bool SubTest::Execute()
	{	bool bResult;

		try
		{
			StartTime = get_current_msecs();
			bResult = OnExecute();
			EndTime = get_current_msecs();
			if (bMustThrow) bResult = false;

		}
		catch(exception & e)
		{	EndTime = get_current_msecs();
			LastException = e;
			if ((bMustThrow) && (e.get_type() == ExceptionType))
				bResult = true;
			else
				bResult = false;
		}

		// Save time
		CpuTimeSpent = (EndTime - StartTime);
		return bResult;
	}

	// Reset timer
	void SubTest::ResetTimer()
	{
		StartTime = get_current_msecs();
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
