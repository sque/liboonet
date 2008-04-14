#include "test_host_resolver.hpp"
#include <oonet/host_resolver.hpp>

namespace oonet
{
	TestHostResolver theHostResolverTest;

	bool TestHostResolver::TestErrorResolv::OnExecute()
	{
		host_resolver myResolv("asdfasdfasd");
		return false;
	}

	bool TestHostResolver::TestLocalhost::OnExecute()
	{	host_resolver resLocal("localhost");

		if (resLocal.get_host().to_string() != "127.0.0.1")
			return false;
		return true;
	}

	bool TestHostResolver::TestResolveIPs::OnExecute()
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

	bool TestHostResolver::TestCopyCtor::OnExecute()
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

	bool  TestHostResolver::TestGetAddressOver::OnExecute()
	{	host_resolver local("127.0.0.1");

		local.get_host(local.count_hosts());	// This will overflow
		return true;
	}
};	// !oonet namespace

