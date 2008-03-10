#include "TestHostResolver.h"
#include "HostResolver.h"

namespace Slib
{
	TestHostResolver theHostResolverTest;

	bool TestHostResolver::TestErrorResolv::OnExecute()
	{
		HostResolver myResolv("asdfasdfasd");
		return false;
	}

	bool TestHostResolver::TestLocalhost::OnExecute()
	{	HostResolver resLocal("localhost");

		if (resLocal.getAddress().toString() != "127.0.0.1")
			return false;
		return true;
	}

	bool TestHostResolver::TestResolveIPs::OnExecute()
	{
		HostResolver IP1("192.168.0.1");
		if (IP1.getAddress().toString() != "192.168.0.1")
			return false;

		HostResolver IP2("255.255.255.255");
		if (IP2.getAddress().toString() != "255.255.255.255")
			return false;

		HostResolver IP3("0.0.0.0");
		if (IP3.getAddress().toString() != "0.0.0.0")
			return false;
		return true;
	}

	bool TestHostResolver::TestCopyCtor::OnExecute()
	{	HostResolver local("127.0.0.1");

		HostResolver l2(local);

		if (l2.getOfficialName() != local.getOfficialName())
			return false;
		if (l2.getAddressCount() != local.getAddressCount())
			return false;

		for(int i = 0;i < l2.getAddressCount();i++)
			if (l2.getAddress(i) != local.getAddress(i))
				return false;

		return true;
	}

	bool  TestHostResolver::TestGetAddressOver::OnExecute()
	{	HostResolver local("127.0.0.1");

		local.getAddress(local.getAddressCount());	// This will overflow
		return true;
	}
};	//! Slib namespace

