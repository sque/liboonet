#include "platform.h"
#include <map>
#include "TestEssentials.h"

using namespace std;
using namespace Slib;

typedef map<string, Test *> TestMap_t;
typedef map<string, Test *>::iterator TestMapIterator;

TestMap_t * pTestsMap = 0;

// Prototypes
extern void RegisterTest(Test * pTest);
void printRegisteredTests();

// Main function
int _tmain(int argc, TCHAR * argv[])
{
    TestMapIterator it;
    string testname;
	bool res;

	// For windows
#if (SLIB_OS ==  SLIB_OS_WIN32)
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	WSAStartup(wVersionRequested, &wsaData);
#endif

	// Check arguments
    if (argc == 1)
    {
		res = true;		// Result true by default

        // Run all registered tests
        for(it = pTestsMap->begin();it != pTestsMap->end(); it++)
		{
            if (it->second->Execute() == false) res = false;
			printf("\n");
		}

		if (!res)
			_tprintf(_T("!!One or more tests failed!!!\n"));
    }
    else
    {
		// Run the selected ones only
        for(int i=1;i < argc;i++)
        {
            testname = argv[i];
            it = pTestsMap->find(testname);
            if (it != pTestsMap->end())
            {
               if (it->second->Execute())
				   _tprintf(_T("OK\n"));
			   else
				   _tprintf(_T("FAILED!\n"));
            }
            else
            {
				_tprintf(_T("[Error] Cannot find test with name: %s\n"), testname.c_str());
                printRegisteredTests();
            }
        }
    }

#if (SLIB_OS == SLIB_OS_WIN32)
	WSACleanup();
#endif
	_tprintf(_T("Finished.. PRESS anykey to continue\n"));
    getc(stdin);
}

void RegisterTest(Test * pTest)
{   // Allocate space first run time
	if (pTestsMap == NULL)
	{	pTestsMap = new TestMap_t;
	}
	(*pTestsMap)[pTest->TestName] = pTest;	}

void printRegisteredTests()
{   TestMapIterator it;
	Test * pTest;

	_tprintf(_T("Registered tests are:\n"));
    for(it = pTestsMap->begin();it != pTestsMap->end(); it++)
	{	pTest = it->second;
		_tprintf(_T("  %s\n"), pTest->TestName.c_str());
    }
}
