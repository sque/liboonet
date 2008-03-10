#ifndef OONET_TESTS_SUBTESTBASE_H_DEFINED
#define OONET_TESTS_SUBTESTBASE_H_DEFINED

#include "Slib.h"
#include <time.h>

namespace OONet
{
	class Test;	// Prototype of Test class

	class SubTest
	{
	public:
		// Constructor
		SubTest(string Name);

		// Constructor for throw
		SubTest(string Name, string ExcType);

		// Destructor
		virtual ~SubTest(){};

		// Execute
		bool Execute();

		// Reset timer
		void ResetTimer();

		string SubTestName;		// Subtest name
		bool bMustThrow;		// When this test forces to throw exception
		string ExceptionType;	// The exception type that must throw
		Exception LastException;
		ulong CpuTimeSpent;		// How many cpu time was spent
	protected:
		clock_t StartTime, EndTime;

		// On test run
		virtual bool OnExecute() = 0;

		// Get last system error description
		string GetSystemLastErrorDescription();
	};	//! SubTest class

	// Fast declare a subtest
#define OONET_DECLARESUBTEST(testtype, name) \
		class testtype :public SubTest	\
		{	public: testtype()	\
				:SubTest(name) {} \
			protected: virtual bool OnExecute(); \
		};

#define OONET_DECLARESUBTESTEXC(testtype, name, exctype) \
		class testtype :public SubTest	\
		{	public: testtype()	\
				:SubTest(name, exctype) {} \
			protected: virtual bool OnExecute(); \
		};
};	// !OONet namespace

#endif // !OONET_TESTS_SUBTESTBASE_H_DEFINED
