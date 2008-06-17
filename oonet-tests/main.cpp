#include <oonet/oonet.hpp>
#include <map>
#include <oonet/test.hpp>

using namespace std;
using namespace oonet;

typedef map<string, test::test_set *> TestMap_t;
typedef map<string, test::test_set *>::iterator TestMapIterator;

TestMap_t * pTestsMap = 0;

// Prototypes
extern void RegisterTest(test::test_set * p_test);
void printRegisteredTests();

// Main function
int _tmain(int argc, TCHAR * argv[])
{
    TestMapIterator it;
    string testname;
	bool res;
	bool b_exclude_speed = false;

	// Display intro
	printf(	"+-------------------------------------------------+\n"
			"|OONet's Test Suite                               |\n"
			"| compiled against version %u.%u.%u %-17s|\n"
			"| linked against version %u.%u.%u %-17s  |\n"
			"| registered: %d tests                            |\n"
			"+-------------------------------------------------+\n\n",
		OONET_VERSION_MAJOR,
		OONET_VERSION_MINOR,
		OONET_VERSION_MICRO,
		OONET_VERSION_PHRASE,
		oonet::version_major(),
		oonet::version_minor(),
		oonet::version_micro(),
		oonet::version_phrase().c_str(),
		pTestsMap->size()
	);
	// For windows
#if (OONET_OS ==  OONET_OS_WIN32)
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	WSAStartup(wVersionRequested, &wsaData);
#endif

	// Check arguments
    if ((argc == 1) ||
		((argc == 2) && (strcmp(argv[1], "-nospeed") == 0)))
    {
		res = true;		// Result true by default
		
		// Exclude speed results
		if (argc == 2)
			b_exclude_speed = true;

        // Run all registered tests
        for(it = pTestsMap->begin();it != pTestsMap->end(); it++)
		{
            if (it->second->execute_all(b_exclude_speed) == false) res = false;
			printf("\n");
		}

		if (!res)
			printf("!!One or more tests failed!!!\n");
    }
    else
    {
		// Run the selected ones only
        for(int i=1; i < argc;i++)
        {			
			// Check if it is an option
			if (strcmp(argv[i], "-nospeed") == 0)
			{
				b_exclude_speed = true;
				continue;
			}
				
            testname = argv[i];
            it = pTestsMap->find(testname);
            if (it != pTestsMap->end())
            {
               if (it->second->execute_all(b_exclude_speed))
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

#if (OONET_OS == OONET_OS_WIN32)
	WSACleanup();
#endif
	_tprintf(_T("Finished.. PRESS anykey to continue\n"));
    getc(stdin);
}

void register_test(test::test_set * p_test)
{   // Allocate space first run time
	if (pTestsMap == NULL)
	{	pTestsMap = new TestMap_t;
	}
	(*pTestsMap)[p_test->name()] = p_test;
}

void printRegisteredTests()
{   TestMapIterator it;
	test::test_set * p_test;

	printf("Registered tests are:\n");
    for(it = pTestsMap->begin();it != pTestsMap->end(); it++)
	{	p_test = it->second;
		printf("  %s\n", p_test->name().c_str());
    }
}
