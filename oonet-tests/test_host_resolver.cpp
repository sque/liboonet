#include "test_host_resolver.hpp"
#include <oonet/host_resolver.hpp>

namespace oonet
{
	namespace test
	{
		test_host_resolver test_host_resolver_inst;

		bool test_host_resolver::TestErrorResolv::operator()()
		{
			host_resolver myResolv("asdfasdfasd");
			return false;
		}

		bool test_host_resolver::TestLocalhost::operator()()
		{	host_resolver resLocal("localhost");

			if (resLocal.get_host().to_string() != "127.0.0.1")
				return false;
			return true;
		}

		bool test_host_resolver::TestResolveIPs::operator()()
		{
			host_resolver IP1("192.168.0.1");
			if (IP1.get_host().to_string() != "192.168.0.1")
				return false;

			host_resolver IP2("255.255.255.255");
			if (IP2.get_host().to_string() != "255.255.255.255")
				return false;

			host_resolver IP3("0.0.0.0");
			if (IP3.get_host().to_string() != "0.0.0.0")
				return false;
			return true;
		}

		bool test_host_resolver::TestCopyCtor::operator()()
		{	host_resolver local("127.0.0.1");

			host_resolver l2(local);

			if (l2.get_official_name() != local.get_official_name())
				return false;
			if (l2.count_hosts() != local.count_hosts())
				return false;

			for(int i = 0;i < l2.count_hosts();i++)
				if (l2.get_host(i) != local.get_host(i))
					return false;

			return true;
		}

		bool  test_host_resolver::TestGetAddressOver::operator()()
		{	host_resolver local("127.0.0.1");

			local.get_host(local.count_hosts());	// This will overflow
			return true;
		}
	}	// !test namespace
};	// !oonet namespace

