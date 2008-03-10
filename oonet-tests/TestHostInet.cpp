#include "TestHostInet.h"
#include "HostInet.h"

namespace OONet
{
	TestHostInet theTestHostInet;

	bool TestHostInet::TestDefaultCtor::OnExecute()
	{	HostInet t1;

		if (t1.toString() != "0.0.0.0")
			return false;
		return true;
	}

	bool TestHostInet::TestUlongCtor::OnExecute()
	{
		HostInet t1(1);
		if (t1.toString() != "0.0.0.1")
			return false;

		HostInet t2(2);
		if (t2.toString() != "0.0.0.2")
			return false;

		HostInet t256(256);
		if (t256.toString() != "0.0.1.0")
			return false;

		HostInet t257(257);
		if (t257.toString() != "0.0.1.1")
			return false;

		HostInet t65536(65536);
		if (t65536.toString() != "0.1.0.0")
			return false;

		HostInet t65537(65537);
		if (t65537.toString() != "0.1.0.1")
			return false;

		HostInet t16777216(16777216);
		if (t16777216.toString() != "1.0.0.0")
			return false;

		HostInet t16777217(16777217);
		if (t16777217.toString() != "1.0.0.1")
			return false;
		return true;
	}

	bool TestHostInet::TestCopyCtor::OnExecute()
	{	HostInet t1(256);

		HostInet t2(t1);
		if (t2.toString() != "0.0.1.0")
			return false;
		return true;
	}

	bool TestHostInet::TestCopyOperator::OnExecute()
	{	HostInet t1(256), t2, t3;

		t2 = t1;
		if (t1.toString() != t2.toString())
			return false;

		if (t2.toString() == t3.toString())
			return false;

		return true;
	}

	bool TestHostInet::TestCompOperator::OnExecute()
	{	HostInet t1(333), t2(333), t3(123);

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

	bool TestHostInet::TestInCompOperator::OnExecute()
	{	HostInet t1(333), t2(333), t3(123);

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

	bool TestHostInet::TestGetInetHost::OnExecute()
	{	HostInet t1(11324);
		OONet::ulong u_temp = htonl(11324);

		if (t1.getNBOAddress() != u_temp)
			return false;
		if (!(t1.getNBOAddress() == u_temp))
			return false;
		return true;
	}

	bool TestHostInet::TestStaticAddress::OnExecute()
	{
		if (HostInet::ANY.toString() != "0.0.0.0")
			return false;
		if (HostInet::LOCALHOST.toString() != "127.0.0.1")
			return false;
		return true;
	}

}; // !OONet namespace
