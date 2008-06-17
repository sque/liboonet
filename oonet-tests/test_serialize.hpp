#ifndef TEST_SERIALIZE_HPP_INCLUDED
#define TEST_SERIALIZE_HPP_INCLUDED

#include "oonet-tests.h"

namespace oonet
{
	namespace test
	{
		class test_serialize
			:public test_set
		{
		protected:
			////////////////////////////
			// SUB TESTS
			OONET_DECLARESUBTEST(TestBasic, "basic functionality");
			OONET_DECLARESUBTEST(TestLeftOperator, "operator<< ");
			OONET_DECLARESUBTEST(TestLeftConstOperator, "operator<< const");
			OONET_DECLARESUBTEST(TestRightOperator, "operator>>");
			OONET_DECLARESUBTEST(TestMultipleActions, "Multiple actions");
			OONET_DECLARESUBTEST(TestCastPod, "Cast POD type");
			OONET_DECLARESUBTEST(TestSerializeStrings, "Work with std::string");
			OONET_DECLARESUBTEST(TestSerializeWStrings, "Work with std::wstring");
			OONET_DECLARESUBTEST(TestSerializeSTLList, "Work with std::list<>");
			OONET_DECLARESUBTEST(TestSerializeSTLVector, "Work with std::vector<>");
			OONET_DECLARESUBTEST(TestSerializeSTLPair, "Work with std::pair<>");
			OONET_DECLARESUBTEST(TestSerializeSTLMap, "Work with std::map<>");
			OONET_DECLARESUBTEST_SPEED(TestSerializeSpeed, "ser/ze() speed w/o cast");
			OONET_DECLARESUBTEST_SPEED(TestSerializeSpeedWCast, "ser/ze() speed w/cast");
			OONET_DECLARESUBTEST_SPEED(TestSerializeSpeedConst, "ser/ze(const) spd w/o cast");
			OONET_DECLARESUBTEST_SPEED(TestSerializeSpeedConstWCast, "ser/ze(const) spd w/cast");
			OONET_DECLARESUBTEST_SPEED(TestUnSerializeSpeed, "unser/ze() speed w/o cast");
			OONET_DECLARESUBTEST_SPEED(TestUnSerializeSpeedWCast, "unser/ze() speed w/cast");
			OONET_DECLARESUBTEST_SPEED(TestSerializeSpeedString, "ser/ze() speed string");
			OONET_DECLARESUBTEST_SPEED(TestUnSerializeSpeedString, "unser/ze() speed string");
			OONET_DECLARESUBTEST_SPEED(TestSerializeSpeedList, "ser/ze() speed std::list");
			OONET_DECLARESUBTEST_SPEED(TestUnSerializeSpeedList, "unser/ze() speed std::list");


		public:
			// Constructor
			test_serialize()
				:test_set(_T("serialization"))
			{
				OONET_REGISTERSUBTEST(TestBasic);
				OONET_REGISTERSUBTEST(TestLeftOperator);
				OONET_REGISTERSUBTEST(TestLeftConstOperator);
				OONET_REGISTERSUBTEST(TestRightOperator);
				OONET_REGISTERSUBTEST(TestMultipleActions);
				OONET_REGISTERSUBTEST(TestCastPod);
				OONET_REGISTERSUBTEST(TestSerializeStrings);
				OONET_REGISTERSUBTEST(TestSerializeWStrings);
				OONET_REGISTERSUBTEST(TestSerializeSTLList);
				OONET_REGISTERSUBTEST(TestSerializeSTLVector);
				OONET_REGISTERSUBTEST(TestSerializeSTLPair);
				OONET_REGISTERSUBTEST(TestSerializeSTLMap);
				OONET_REGISTERSUBTEST(TestSerializeSpeed);
				OONET_REGISTERSUBTEST(TestSerializeSpeedWCast);
				OONET_REGISTERSUBTEST(TestSerializeSpeedConst);
				OONET_REGISTERSUBTEST(TestSerializeSpeedConstWCast);
				OONET_REGISTERSUBTEST(TestUnSerializeSpeed);
				OONET_REGISTERSUBTEST(TestUnSerializeSpeedWCast);
				OONET_REGISTERSUBTEST(TestSerializeSpeedString);
				OONET_REGISTERSUBTEST(TestUnSerializeSpeedString);
				OONET_REGISTERSUBTEST(TestSerializeSpeedList);
				OONET_REGISTERSUBTEST(TestUnSerializeSpeedList);

				register_test(this);
			}

		} ;	// !test_serialize class
	}	// !test namespace
};	// !oonet namespace


#endif // TEST_SERIALIZE_HPP_INCLUDED
