#ifndef TEST_SERIALIZE_HPP_INCLUDED
#define TEST_SERIALIZE_HPP_INCLUDED

#include <oonet/oonet.hpp>
#include "Test.h"

namespace oonet
{
	class test_serialize
		:public Test
	{
	protected:
		////////////////////////////
		// SUB TESTS
		OONET_DECLARESUBTEST(TestBasic,  _T("basic functionality") );
		OONET_DECLARESUBTEST(TestLeftOperator,  _T("operator<< ") );
		OONET_DECLARESUBTEST(TestLeftConstOperator,  _T("operator<< const") );
		OONET_DECLARESUBTEST(TestRightOperator,  _T("operator>>") );
		OONET_DECLARESUBTEST(TestMultipleActions,  _T("Multiple actions") );
		OONET_DECLARESUBTEST(TestCastPod,  _T("Cast POD type") );
		OONET_DECLARESUBTEST(TestSerializeStrings,  _T("Work with std::string") );
		OONET_DECLARESUBTEST(TestSerializeWStrings,  _T("Work with std::wstring") );
		OONET_DECLARESUBTEST(TestSerializeSpeed,  _T("ser/ze() speed w/o cast") );
		OONET_DECLARESUBTEST(TestSerializeSpeedWCast,  _T("ser/ze() speed w/cast") );
		OONET_DECLARESUBTEST(TestSerializeSpeedConst,  _T("ser/ze(const) spd w/o cast") );
		OONET_DECLARESUBTEST(TestSerializeSpeedConstWCast,  _T("ser/ze(const) spd w/cast") );
		OONET_DECLARESUBTEST(TestUnSerializeSpeed,  _T("unser/ze() speed w/o cast") );
		OONET_DECLARESUBTEST(TestUnSerializeSpeedWCast,  _T("unser/ze() speed w/cast") );
		OONET_DECLARESUBTEST(TestSerializeSpeedString,  _T("ser/ze() speed string") );
		OONET_DECLARESUBTEST(TestUnSerializeSpeedString,  _T("unser/ze() speed string") );

	public:
		// Constructor
		test_serialize()
			:Test(_T("serialization"))
		{
			OONET_REGISTERSUBTEST(TestBasic);
			OONET_REGISTERSUBTEST(TestLeftOperator);
			OONET_REGISTERSUBTEST(TestLeftConstOperator);
			OONET_REGISTERSUBTEST(TestRightOperator);
			OONET_REGISTERSUBTEST(TestMultipleActions);
			OONET_REGISTERSUBTEST(TestCastPod);
			OONET_REGISTERSUBTEST(TestSerializeStrings);
			OONET_REGISTERSUBTEST(TestSerializeWStrings);
			OONET_REGISTERSUBTEST(TestSerializeSpeed);
			OONET_REGISTERSUBTEST(TestSerializeSpeedWCast);
			OONET_REGISTERSUBTEST(TestSerializeSpeedConst);
			OONET_REGISTERSUBTEST(TestSerializeSpeedConstWCast);
			OONET_REGISTERSUBTEST(TestUnSerializeSpeed);
			OONET_REGISTERSUBTEST(TestUnSerializeSpeedWCast);
			OONET_REGISTERSUBTEST(TestSerializeSpeedString);
			OONET_REGISTERSUBTEST(TestUnSerializeSpeedString);

		}

	} ;	// !test_serialize class
};	// !oonet namespace


#endif // TEST_SERIALIZE_HPP_INCLUDED
