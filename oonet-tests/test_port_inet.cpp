#include "test_port_inet.hpp"
#include <oonet/port_inet.hpp>

namespace oonet
{
	namespace test
	{
		test_port_inet test_port_inet_inst;

		bool test_port_inet::TestDefaultCtor::operator()()
		{
			port_inet t1;

			if (t1.to_string() != "0")
				return false;
			return true;
		}

		bool test_port_inet::TestUshortCtor::operator()()
		{
			port_inet t1 = port_inet(80);
			port_inet t2 = port_inet(20480); //! This is 80 when endian is mixed up
			if (t1.to_string() != "80")
				return false;
			if (t2.to_string() != "20480")
				return false;
			return true;
		}

		bool test_port_inet::TestCopyConstructor::operator()()
		{	port_inet t1(80);
			port_inet t2(t1);

			if (t1.to_string() != "80")
				return false;
			if (t2.to_string() != "80")
				return false;
			return true;
		}

		bool test_port_inet::TestCopyOperator::operator()()
		{	port_inet t1(80);
			port_inet t2;

			t2 = t1;
			if (t1.to_string() != "80")
				return false;
			if (t2.to_string() != "80")
				return false;
			return true;
		}

		bool test_port_inet::TestComparisonOperator::operator()()
		{	port_inet t1(100), t2(100), t3(101);

			// False...
			if (t1 == t3)
				return false;
			if (t2 == t3)
				return false;
			if (! (t1 == t2))
				return false;

			// True...
			if (t1 == t2)
				return true;

			return false;
		}

		bool test_port_inet::TestInComparisonOperator::operator()()
		{	port_inet t1(100), t2(100), t3(101);

			// False ...
			if (t1 != t2)
				return false;
			if (! (t1 != t3))
				return false;
			if (! (t2 != t3))
				return false;

			// True..
			if (t1 != t3)
				return true;
			return false;
		}

		bool test_port_inet::TestGetInetPort::operator()()
		{	port_inet t1(32);
			oonet::ushort u_temp = htons(32);

			if (t1.get_nbo() != u_temp)
				return false;
			if (!(t1.get_nbo() == u_temp))
				return false;
			return true;
		}
	}	// !test namespace
};	// !oonet namespace
