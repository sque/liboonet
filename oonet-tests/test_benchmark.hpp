#ifndef TEST_BENCHMARK_HPP_INCLUDED
#define TEST_BENCHMARK_HPP_INCLUDED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_benchmark
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARE_SUBTEST_SPEED(TestTCPSpeed4G, "Raw tcp data 4Gb");
			OONET_DECLARE_SUBTEST_SPEED(TestHTTPSpeed500Mb, "HTTP data 500Mb");
		public:
			// Constructor
			test_benchmark()
				:test_set("benchmark")
			{
				OONET_EXECUTE_SUBTEST(TestTCPSpeed4G);
				OONET_EXECUTE_SUBTEST(TestHTTPSpeed500Mb);

				register_test(this);
			}

		};	// !test_benchmark class
	} ;	// !test namespace
};	// !oonet namespace


#endif // TEST_BENCHMARK_HPP_INCLUDED
