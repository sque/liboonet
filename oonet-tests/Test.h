#ifndef OONET_TESTS_TESTBASE_H_DEFINED
#define OONET_TESTS_TESTBASE_H_DEFINED

#include "Slib.h"
#include "SubTest.h"
#include <deque>

namespace OONet
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
};	// !OONet namespace
#endif // !OONET_TESTS_TESTBASE_H_DEFINED
