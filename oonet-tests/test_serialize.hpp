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
			OONET_DECLARE_SUBTEST(TestBasic, "basic functionality");
			OONET_DECLARE_SUBTEST(TestLeftOperator, "operator<< ");
			OONET_DECLARE_SUBTEST(TestLeftConstOperator, "operator<< const");
			OONET_DECLARE_SUBTEST(TestRightOperator, "operator>>");
			OONET_DECLARE_SUBTEST(TestMultipleActions, "Multiple actions");
			OONET_DECLARE_SUBTEST(TestCastPod, "Cast POD type");
			OONET_DECLARE_SUBTEST(TestSerializeStrings, "Work with std::string");
			OONET_DECLARE_SUBTEST(TestSerializeWStrings, "Work with std::wstring");
			OONET_DECLARE_SUBTEST(TestSerializeSTLList, "Work with std::list<>");
			OONET_DECLARE_SUBTEST(TestSerializeSTLVector, "Work with std::vector<>");
			OONET_DECLARE_SUBTEST(TestSerializeSTLPair, "Work with std::pair<>");
			OONET_DECLARE_SUBTEST(TestSerializeSTLMap, "Work with std::map<>");
			OONET_DECLARE_SUBTEST_SPEED(TestSerializeSpeed, "ser/ze() speed w/o cast");
			OONET_DECLARE_SUBTEST_SPEED(TestSerializeSpeedWCast, "ser/ze() speed w/cast");
			OONET_DECLARE_SUBTEST_SPEED(TestSerializeSpeedConst, "ser/ze(const) spd w/o cast");
			OONET_DECLARE_SUBTEST_SPEED(TestSerializeSpeedConstWCast, "ser/ze(const) spd w/cast");
			OONET_DECLARE_SUBTEST_SPEED(TestUnSerializeSpeed, "unser/ze() speed w/o cast");
			OONET_DECLARE_SUBTEST_SPEED(TestUnSerializeSpeedWCast, "unser/ze() speed w/cast");
			OONET_DECLARE_SUBTEST_SPEED(TestSerializeSpeedString, "ser/ze() speed string");
			OONET_DECLARE_SUBTEST_SPEED(TestUnSerializeSpeedString, "unser/ze() speed string");
			OONET_DECLARE_SUBTEST_SPEED(TestSerializeSpeedList, "ser/ze() speed std::list");
			OONET_DECLARE_SUBTEST_SPEED(TestUnSerializeSpeedList, "unser/ze() speed std::list");


		public:
			// Constructor
			test_serialize()
				:test_set(_T("serialization"))
			{
				OONET_EXECUTE_SUBTEST(TestBasic);
				OONET_EXECUTE_SUBTEST(TestLeftOperator);
				OONET_EXECUTE_SUBTEST(TestLeftConstOperator);
				OONET_EXECUTE_SUBTEST(TestRightOperator);
				OONET_EXECUTE_SUBTEST(TestMultipleActions);
				OONET_EXECUTE_SUBTEST(TestCastPod);
				OONET_EXECUTE_SUBTEST(TestSerializeStrings);
				OONET_EXECUTE_SUBTEST(TestSerializeWStrings);
				OONET_EXECUTE_SUBTEST(TestSerializeSTLList);
				OONET_EXECUTE_SUBTEST(TestSerializeSTLVector);
				OONET_EXECUTE_SUBTEST(TestSerializeSTLPair);
				OONET_EXECUTE_SUBTEST(TestSerializeSTLMap);
				OONET_EXECUTE_SUBTEST(TestSerializeSpeed);
				OONET_EXECUTE_SUBTEST(TestSerializeSpeedWCast);
				OONET_EXECUTE_SUBTEST(TestSerializeSpeedConst);
				OONET_EXECUTE_SUBTEST(TestSerializeSpeedConstWCast);
				OONET_EXECUTE_SUBTEST(TestUnSerializeSpeed);
				OONET_EXECUTE_SUBTEST(TestUnSerializeSpeedWCast);
				OONET_EXECUTE_SUBTEST(TestSerializeSpeedString);
				OONET_EXECUTE_SUBTEST(TestUnSerializeSpeedString);
				OONET_EXECUTE_SUBTEST(TestSerializeSpeedList);
				OONET_EXECUTE_SUBTEST(TestUnSerializeSpeedList);

				register_test(this);
			}

		} ;	// !test_serialize class
	}	// !test namespace
};	// !oonet namespace


#endif // TEST_SERIALIZE_HPP_INCLUDED
