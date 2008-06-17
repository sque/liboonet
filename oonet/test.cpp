#include "./test.hpp"

// Include unix time
#if (OONET_OS != OONET_OS_WIN32)
	#include <sys/time.h>
	#include <time.h>
#endif

namespace oonet
{
	namespace test
	{

#if OONET_OS == OONET_OS_WIN32
		double get_current_msecs()
		{
			double tm = timeGetTime();
			return tm;
		}
#else
		double get_current_msecs()
		{	struct timeval t;
			double tmp_out;

			gettimeofday(&t, NULL);
			tmp_out = t.tv_sec * 1000.0;
			tmp_out += ((double)t.tv_usec /1000.0);

			return tmp_out;
		}
#endif
		one_test::one_test(const string & _name, bool _speed_test)
			:m_name(_name),
			m_thrown_exception("", 0, "", ""),
			b_must_throw(false),
			b_speed_test(_speed_test)
		{
		}

		one_test::one_test(const string & _name,
			const string & _exc_name)
			:m_name(_name),
			m_expected_exception(_exc_name),
			m_thrown_exception("", 0, "", ""),
			b_must_throw(true),
			b_speed_test(false)
		{
		}

		double one_test::time_passed()
		{	return get_current_msecs() - m_timer_start;	}

		void one_test::reset_timer()
		{	m_timer_start = get_current_msecs();	}

		bool one_test::execute()
		{	bool b_result;

			// Reset timer
			reset_timer();

			// Run test
			try
			{
				b_result = operator()();

				// Calculate spent time
				m_time_spent = time_passed();
			}
			catch(exception & e)
			{	m_thrown_exception = e;	// Save exception

				// Calculate spent time
				m_time_spent = time_passed();

				if ((b_must_throw) && (m_thrown_exception.get_type() == m_expected_exception))
					return true;
				return false;
			}

			return b_result;
		}

		test_set::test_set(const string & _name)
			:m_name(_name)
		{
		}

		bool test_set::execute_all(bool b_exclude_speed)
		{	iterator it;
			int count = 0;
			bool b_fail_flag = false;	// A flag raised if at least one test was failed

			// Print main test title
			printf("____________________________________+_Test_+_CPU__+_Exception_________________\r___%s_(%d_tests)\n",
				m_name.c_str(),
				m_tests.size()
			);

			// Run one-by-one the tests
			for(it = m_tests.begin(); it != m_tests.end(); it++)
			{	one_test & m_test = *it->get();
				
				// skip speed tests if requested
				if ((b_exclude_speed) && (m_test.is_speed_test()))
					continue;
					
				// Increment counter
				count++;

				// Print title
				printf("  %2d| %-30s", count, string(m_test.name() + "...").c_str());
				fflush(stdout);

				// Execute test
				if (m_test.execute())
				{	// Succeded
					printf("| ok   |%4.1f |%-20s\n",
						m_test.time_spent(),
						m_test.thrown_exception().get_type().c_str()
					);
				}
				else
				{	// Failed
					b_fail_flag = true;

					printf("| FAIL |%4.1f |%-20s\n",
						m_test.time_spent(), m_test.thrown_exception().get_type().c_str()
					);
				}
			}

			return !b_fail_flag;
		}
	};	// !test namespace
};	// !oonet namespace
