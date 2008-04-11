#include "test_port_inet.hpp"
#include "port_inet.hpp"

namespace oonet
{
	TestPortInet theTestPortInet;

	bool TestPortInet::TestDefaultCtor::OnExecute()
	{
		port_inet t1;

		if (t1.to_string() != "0")
			return false;
		return true;
	}

	bool TestPortInet::TestUshortCtor::OnExecute()
	{
		port_inet t1 = port_inet(80);
		port_inet t2 = port_inet(20480); //! This is 80 when endian is mixed up
		if (t1.to_string() != "80")
			return false;
		if (t2.to_string() != "20480")
			return false;
		return true;
	}

	bool TestPortInet::TestCopyConstructor::OnExecute()
	{	port_inet t1(80);
		port_inet t2(t1);

		if (t1.to_string() != "80")
			return false;
		if (t2.to_string() != "80")
			return false;
		return true;
	}

	bool TestPortInet::TestCopyOperator::OnExecute()
	{	port_inet t1(80);
		port_inet t2;

		t2 = t1;
		if (t1.to_string() != "80")
			return false;
		if (t2.to_string() != "80")
			return false;
		return true;
	}

	bool TestPortInet::TestComparisonOperator::OnExecute()
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

	bool TestPortInet::TestInComparisonOperator::OnExecute()
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

	bool TestPortInet::TestGetInetPort::OnExecute()
	{	port_inet t1(32);
		oonet::ushort u_temp = htons(32);

		if (t1.get_nbo() != u_temp)
			return false;
		if (!(t1.get_nbo() == u_temp))
			return false;
		return true;
	}
};	// !oonet namespace
