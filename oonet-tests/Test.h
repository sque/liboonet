#ifndef OONET_TESTS_TESTBASE_H_DEFINED
#define OONET_TESTS_TESTBASE_H_DEFINED

#include "SubTest.h"
#include <deque>

namespace oonet
{
	class Test
	{
	public:
		// Constructor
		Test(const string & Name);

		// Destructor
		virtual ~Test();

		string TestName;	// The name of the test

		// Sub tests
		std::deque<SubTest *> SubTests;

		// Run all subtests
		bool Execute();

	};

#define OONET_REGISTERSUBTEST(subtype) \
	SubTests.push_back(new subtype());
};	// !oonet namespace
#endif // !OONET_TESTS_TESTBASE_H_DEFINED
