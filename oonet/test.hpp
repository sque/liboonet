#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include "./oonet.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace oonet
{
	namespace test
	{
		//! One test object
		class one_test
		{
		public:

			//! Constructor of a test that must NOT throw exception
			one_test(const string & _name, bool _speed_test = false);

			//! Constructor of a test that must throw exception.
			one_test(const string & _name,
				const string & _exc_name);

			//! Destructor
			virtual ~one_test(){}

			//! Execute the test and get result true/false if it failed
			bool execute();

			//! Check if test must throw exception
			const bool must_throw() const
			{	return b_must_throw;	}

			//! Get thrown exception of test
			const exception & thrown_exception() const
			{	return m_thrown_exception;	}

			//! Get name of test
			const string & name() const
			{	return m_name;	}

			//! Get expected exception
			const string & expected_exception() const
			{	return m_expected_exception;	}

			//! Time spent in seconds
			double time_spent() const
			{	return m_time_spent;	}
			
			//! Check if it is a speed test
			const bool & is_speed_test() const
			{	return b_speed_test;		}

		protected:

			string m_name;					//!< Name of sub-test
			string m_expected_exception;	//!< Expected exception to throw
			exception m_thrown_exception;	//!< Exception thrown by test.
			bool b_must_throw;				//!< A flag if test must throw
			double m_timer_start;			//!< Start time of timer
			double m_time_spent;			//!< Time spent for test
			bool b_speed_test;				//!< Flag if this test is a speed test

			//! Time passed for the begining of timer
			double time_passed();

			//! Reset timer
			void reset_timer();

			//! Function holding the actual test
			virtual bool operator()() = 0;
		};


		//! A set of tests grouped by a name
		class test_set
		{
		public:
			typedef std::vector< boost::shared_ptr<one_test> > list_type;
			typedef list_type::iterator iterator;
			typedef list_type::const_iterator const_iterator;

		protected:

			string m_name;	//!< Name of test
			std::vector<boost::shared_ptr<one_test> > m_tests;

		public:

			//! Constructor with name
			test_set(const string & _name);

			//! Virtual destructor
			virtual ~test_set(){}

			//! Get reference to name (const)
			const string & name() const
			{	return m_name;	}

			//! Get reference to name
			string & name()
			{	return m_name;	}

			//! Get reference to tests list (const)
			const std::vector<boost::shared_ptr<one_test> > & list() const
			{	return m_tests;	}

			//! Get reference to tests list
			std::vector<boost::shared_ptr<one_test> > & list()
			{	return m_tests;	}

			//! Execute all tests
			bool execute_all(bool b_exclude_speed = false);
		};


#define OONET_DECLARESUBTEST_DETAILED(one_test_class, desc, speed) \
		class one_test_class :public oonet::test::one_test	\
		{	public: one_test_class()	\
				: oonet::test::one_test(desc, speed) {} \
			protected: virtual bool operator()(); \
		};

#define OONET_DECLARESUBTEST(one_test, desc) OONET_DECLARESUBTEST_DETAILED(one_test, desc, false)
#define OONET_DECLARESUBTEST_SPEED(one_test, desc) OONET_DECLARESUBTEST_DETAILED(one_test, desc, true)

#define OONET_DECLARESUBTESTEXC(one_test_class, desc, exc_type) \
		class one_test_class :public oonet::test::one_test	\
		{	public: one_test_class()	\
				: oonet::test::one_test(desc, exc_type) {} \
			protected: virtual bool operator()(); \
		};

#define OONET_REGISTERSUBTEST(subtype) \
		m_tests.push_back(boost::shared_ptr<subtype>( new  subtype()));

	};	// !test namespace
};	// !oonet namespace

#endif // TEST_HPP_INCLUDED
