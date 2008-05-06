#include "test_host_inet.hpp"
#include <oonet/host_inet.hpp>

namespace oonet
{
	namespace test
	{
		test_host_inet test_host_inet_inst;

		bool test_host_inet::TestDefaultCtor::operator()()
		{	host_inet t1;

			if (t1.to_string() != "0.0.0.0")
				return false;
			return true;
		}

		bool test_host_inet::TestUlongCtor::operator()()
		{
			host_inet t1(1);
			if (t1.to_string() != "0.0.0.1")
				return false;

			host_inet t2(2);
			if (t2.to_string() != "0.0.0.2")
				return false;

			host_inet t256(256);
			if (t256.to_string() != "0.0.1.0")
				return false;

			host_inet t257(257);
			if (t257.to_string() != "0.0.1.1")
				return false;

			host_inet t65536(65536);
			if (t65536.to_string() != "0.1.0.0")
				return false;

			host_inet t65537(65537);
			if (t65537.to_string() != "0.1.0.1")
				return false;

			host_inet t16777216(16777216);
			if (t16777216.to_string() != "1.0.0.0")
				return false;

			host_inet t16777217(16777217);
			if (t16777217.to_string() != "1.0.0.1")
				return false;
			return true;
		}

		bool test_host_inet::TestCopyCtor::operator()()
		{	host_inet t1(256);

			host_inet t2(t1);
			if (t2.to_string() != "0.0.1.0")
				return false;
			return true;
		}

		bool test_host_inet::TestCopyOperator::operator()()
		{	host_inet t1(256), t2, t3;

			t2 = t1;
			if (t1.to_string() != t2.to_string())
				return false;

			if (t2.to_string() == t3.to_string())
				return false;

			return true;
		}

		bool test_host_inet::TestCompOperator::operator()()
		{	host_inet t1(333), t2(333), t3(123);

			// False
			if (t1 == t3)
				return false;
			if (t2 == t3)
				return false;
			if (!(t1 == t2))
				return false;

			// True
			if (t1 == t2)
				return true;

			return false;
		}

		bool test_host_inet::TestInCompOperator::operator()()
		{	host_inet t1(333), t2(333), t3(123);

			// False
			if (t1 != t2)
				return false;
			if (! (t1 != t3))
				return false;

			// True
			if (t2 != t3)
				return true;


			return false;
		}

		bool test_host_inet::TestGetInetHost::operator()()
		{	host_inet t1(11324);
			oonet::ulong u_temp = htonl(11324);

			if (t1.get_nbo() != u_temp)
				return false;
			if (!(t1.get_nbo() == u_temp))
				return false;
			return true;
		}

		bool test_host_inet::TestStaticAddress::operator()()
		{
			if (host_inet::ANY.to_string() != "0.0.0.0")
				return false;
			if (host_inet::LOCALHOST.to_string() != "127.0.0.1")
				return false;
			return true;
		}
	};	// !test namespace
}; // !oonet namespace
