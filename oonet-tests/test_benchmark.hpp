#ifndef TEST_BENCHMARK_HPP_INCLUDED
#define TEST_BENCHMARK_HPP_INCLUDED

#include <oonet/binary_data.hpp>
#include "Test.h"

namespace oonet
{
	class test_benchmark
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestTCPSpeed4G,  _T("Raw tcp data 4Gb") );
		OONET_DECLARESUBTEST(TestHTTPSpeed500Mb,  _T("HTTP data 500Mb") );
	public:
		// Constructor
		test_benchmark()
			:Test(_T("benchmark"))
		{
			OONET_REGISTERSUBTEST(TestTCPSpeed4G);
			OONET_REGISTERSUBTEST(TestHTTPSpeed500Mb);

		}

	} ;	// !TestBinaryData class
};	// !oonet namespace


#endif // TEST_BENCHMARK_HPP_INCLUDED
