#include "Test.h"
#include "TestEssentials.h"

namespace oonet
{
	// Constructor
	Test::Test(const string & Name)
	{
		TestName = Name;
		RegisterTest(this);
	}
	// Run all subtests
	bool Test::Execute()
	{	std::deque<SubTest *>::iterator it;
		SubTest * pSubTest;
		int SubCount = 0;
		bool bAllSuccess = true;

		// Print main test title
		_tprintf(_T("____________________________________+_Test_+_CPU__+_Exception_________________\r___%s_(%d_tests)\n"), TestName.c_str(), SubTests.size());

		for(it = SubTests.begin();it != SubTests.end(); it++)
		{
			SubCount ++;
			pSubTest = *it;
			_tprintf(_T("  %2d| %-30s"), SubCount, string(pSubTest->SubTestName + "...").c_str());

			// Test
			if (pSubTest->Execute())
				_tprintf(_T("| ok   |%5ld |%-20s\n"), pSubTest->CpuTimeSpent,pSubTest->LastException.getType().c_str());
			else
			{
				_tprintf(_T("| FAIL |%5ld |%-20s\n"), pSubTest->CpuTimeSpent, pSubTest->LastException.getType().c_str());
				_tprintf(_T("    >> %s - %s(%ld)\n       %s\n"), pSubTest->LastException.getType().c_str(),
                    pSubTest->LastException.getFile().c_str(), pSubTest->LastException.getLine(),
                    pSubTest->LastException.getDescription().c_str());
				bAllSuccess = false;
			}
		}

		return bAllSuccess;
	}

	// Destructor
	Test::~Test()
	{	// Delete all sub tests
		SubTest * pSubTest;
		std::deque<SubTest *>::iterator it;

		while ((it = SubTests.begin()) != SubTests.end())
		{
			pSubTest = *it;
			delete pSubTest;
			SubTests.erase(it);
		}

	}
};	// !oonet namespace
