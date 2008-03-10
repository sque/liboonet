#ifndef SLIB_TESTS_TESTBASE_H_DEFINED
#define SLIB_TESTS_TESTBASE_H_DEFINED

#include "Slib.h"
#include "SubTest.h"
#include <deque>

namespace Slib
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

#define SLIB_REGISTERSUBTEST(subtype) \
	SubTests.push_back(new subtype());
};	//! Slib namespace
#endif //! SLIB_TESTS_TESTBASE_H_DEFINED
