#include "TestPortInet.h"
#include "port_inet.hpp"

namespace oonet
{
	TestPortInet theTestPortInet;

	bool TestPortInet::TestDefaultCtor::OnExecute()
	{
		PortInet t1;

		if (t1.toString() != "0")
			return false;
		return true;
	}

	bool TestPortInet::TestUshortCtor::OnExecute()
	{
		PortInet t1 = PortInet(80);
		PortInet t2 = PortInet(20480); //! This is 80 when endian is mixed up
		if (t1.toString() != "80")
			return false;
		if (t2.toString() != "20480")
			return false;
		return true;
	}

	bool TestPortInet::TestCopyConstructor::OnExecute()
	{	PortInet t1(80);
		PortInet t2(t1);

		if (t1.toString() != "80")
			return false;
		if (t2.toString() != "80")
			return false;
		return true;
	}

	bool TestPortInet::TestCopyOperator::OnExecute()
	{	PortInet t1(80);
		PortInet t2;

		t2 = t1;
		if (t1.toString() != "80")
			return false;
		if (t2.toString() != "80")
			return false;
		return true;
	}

	bool TestPortInet::TestComparisonOperator::OnExecute()
	{	PortInet t1(100), t2(100), t3(101);

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

	bool TestPortInet::TestInComparisonOperator::OnExecute()
	{	PortInet t1(100), t2(100), t3(101);

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

	bool TestPortInet::TestGetInetPort::OnExecute()
	{	PortInet t1(32);
		oonet::ushort u_temp = htons(32);

		if (t1.getNBOPort() != u_temp)
			return false;
		if (!(t1.getNBOPort() == u_temp))
			return false;
		return true;
	}
};	// !oonet namespace
