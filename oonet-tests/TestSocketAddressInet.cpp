#include "TestSocketAddressInet.h"
#include "socket_address_inet.hpp"

namespace oonet
{
	TestSocketAddressInet theSocketAddressInetTest;

	bool TestSocketAddressInet::TestCtor::OnExecute()
	{	SocketAddressInet a;

		// Check if family is set correctly
		if (((sockaddr_in *)a.getSockaddrPtr())->sin_family != AF_INET)
			return false;
		return true;
	}

	bool TestSocketAddressInet::TestHostPortCtor::OnExecute()
	{	SocketAddressInet a(HostInet::LOCALHOST, PortInet(123));

		// Check if family is set correctly
		if (((sockaddr_in *)a.getSockaddrPtr())->sin_family != AF_INET)
			return false;

        // Check value of port
		if (a.getPortInet().toString() != "123")
			return false;

		// Check value of host
		if (a.getHostInet().toString() != "127.0.0.1")
			return false;
		return true;
	}

	bool TestSocketAddressInet::TestResolverPortCtor::OnExecute()
	{	SocketAddressInet a(HostResolver("192.1.3.4"), PortInet(1234));

		// Check if family is set correctly
		if (((sockaddr_in *)a.getSockaddrPtr())->sin_family != AF_INET)
			return false;

        // Check value of port
		if (a.getPortInet().toString() != "1234")
			return false;

		// Check value of host
		if (a.getHostInet().toString() != "192.1.3.4")
			return false;
		return true;
	}

	bool TestSocketAddressInet::TestSockAddrCtor::OnExecute()
	{	SocketAddress gen_addr(SocketAddress::FAMILY_INET);

		// Populate it
		((SOCKADDR_IN *)gen_addr.getSockaddrPtr())->sin_port = htons(1324);

		// Create inet from existing
		SocketAddressInet a(gen_addr);

		if (a.getPortInet().toString() != "1324")
			return false;

		// change it to see if the changes are reflected
		((SOCKADDR_IN *)gen_addr.getSockaddrPtr())->sin_port = htons(1523);
		if (a.getPortInet().toString() != "1324")
			return false;

		return true;
	}

	bool TestSocketAddressInet::TestSockAddrNonInetCtor::OnExecute()
	{	SocketAddress gen_addr(SocketAddress::FAMILY_INET + 1);
		SocketAddressInet a(gen_addr);	// This must fail
		return false;
	}


	bool TestSocketAddressInet::TestCopyCtor::OnExecute()
	{	SocketAddressInet a(HostResolver("192.1.3.4"), PortInet(1234));
		SocketAddressInet b(a);

		// Check if family is set correctly
		if (((sockaddr_in *)b.getSockaddrPtr())->sin_family != AF_INET)
			return false;

        // Check value of port
		if (b.getPortInet().toString() != "1234")
			return false;

		// Check value of host
		if (b.getHostInet().toString() != "192.1.3.4")
			return false;

		// Change a value in a to see if it is reflected (reassinged pointers)
		a.setPortInet(2);
		if (b.getPortInet().toString() != "1234")
			return false;
		return true;
	}

	bool TestSocketAddressInet::TestCopyOperator::OnExecute()
	{	SocketAddressInet a(HostResolver("192.1.3.4"), PortInet(1234));
		SocketAddressInet b;

		// Copy
		b = a;
		// Check if family is set correctly
		if (((sockaddr_in *)b.getSockaddrPtr())->sin_family != AF_INET)
			return false;

        // Check value of port
		if (b.getPortInet().toString() != "1234")
			return false;

		// Check value of host
		if (b.getHostInet().toString() != "192.1.3.4")
			return false;

		// Change a value in a to see if it is reflected (reassinged pointers)
		a.setPortInet(2);
		if (b.getPortInet().toString() != "1234")
			return false;

		return true;
	}

	bool TestSocketAddressInet::TestCompOperator::OnExecute()
	{	SocketAddressInet a(HostResolver("192.1.3.4"), PortInet(1234));
		SocketAddressInet b(HostResolver("192.1.3.4"), PortInet(1236));
		SocketAddressInet c(HostResolver("192.1.3.5"), PortInet(1234));
		SocketAddressInet d(HostResolver("192.1.3.4"), PortInet(1234));

		// False
		if (a == b)
			return false;
		if (a == c)
			return false;
		if (b == c)
			return false;
		if (b == d)
			return false;
		if (c == d)
			return false;
		if (!(a == d))
			return false;

		// True
		if (a == d)
			return true;

		return false;
	}

	bool TestSocketAddressInet::TestInCompOperator::OnExecute()
	{	SocketAddressInet a(HostResolver("192.1.3.4"), PortInet(1234));
		SocketAddressInet b(HostResolver("192.1.3.4"), PortInet(1236));
		SocketAddressInet c(HostResolver("192.1.3.5"), PortInet(1234));
		SocketAddressInet d(HostResolver("192.1.3.4"), PortInet(1234));

		// False
		if (!(a != b))
			return false;
		if (!(a != c))
			return false;
		if (!(b != c))
			return false;
		if (!(b != d))
			return false;
		if (!(c != d))
			return false;
		if (a != d)
			return false;

		// True
		if (b != c)
			return true;

		return false;
	}

	bool TestSocketAddressInet::TestSetHost::OnExecute()
	{	SocketAddressInet a(HostResolver("192.1.3.4"), PortInet(1234));

		// Assign a new host
		a.setHostInet(HostInet::LOCALHOST);

		// Check if family is set correctly
		if (((sockaddr_in *)a.getSockaddrPtr())->sin_family != AF_INET)
			return false;

        // Check value of port
		if (a.getPortInet().toString() != "1234")
			return false;

		// Check value of host
		if (a.getHostInet().toString() != "127.0.0.1")
			return false;

		// Check in structure value of host
		if (((sockaddr_in *)a.getSockaddrPtr())->sin_addr.s_addr != HostInet::LOCALHOST.getNBOAddress())
			return false;
		return true;
	}

	bool TestSocketAddressInet::TestSetPost::OnExecute()
	{	SocketAddressInet a(HostResolver("192.1.3.4"), PortInet(1234));

		// Assign a new host
		a.setPortInet(8512);

		// Check if family is set correctly
		if (((sockaddr_in *)a.getSockaddrPtr())->sin_family != AF_INET)
			return false;

        // Check value of port
		if (a.getPortInet().toString() != "8512")
			return false;

		// Check value of host
		if (a.getHostInet().toString() != "192.1.3.4")
			return false;

		// Check in structure value of host
		if (((sockaddr_in *)a.getSockaddrPtr())->sin_port != ntohs(8512))
			return false;
		return true;
	}
	bool TestSocketAddressInet::TestDefaultValues::OnExecute()
	{	SocketAddressInet a;

		if (a.getHostInet().toString() != "0.0.0.0")
			return false;

		if (a.getPortInet().toString() != "0")
			return false;

		return true;
	}
};	// !oonet namespace
/*
bool TestSocketAddressInet(void)
{
    // Test 1.
    std::cout << "1. Create some SocketAddressInet objects\n";
    SocketAddressInet a, b;

    // Test 2
    std::cout << "2. Set/Get port & addres and validate with binary data\n";
    a.setInetAddress(HostInet::LOCALHOST);
    a.setInetPort(PortInet(80));
    // Create a structure and compare it
    SOCKADDR_IN bin_addr;
    memset(&bin_addr, 0, sizeof(SOCKADDR_IN));
    bin_addr.sin_port = htons(80);
    bin_addr.sin_family = AF_INET;
    bin_addr.sin_addr.s_addr = htonl(0x7f000001);
    // compera
    if (0 != memcmp(a.getStructPointer(), &bin_addr, sizeof(SOCKADDR_IN)))
        return false;


    // Test 3
    std::cout << "3. Test copy operator=\n";
    b = a;
    if (0 != memcmp(b.getStructPointer(), &bin_addr, sizeof(SOCKADDR_IN)))
        return false;
    if (a.getStructPointer() == b.getStructPointer())
        return false;

    // Test 4
    std::cout << "4. operator== and operator!=\n";
    if (a != b)
        return false;
    if (!(a == b))
        return false;
    a = SocketAddressInet(HostInet::ANY, PortInet(0));
    b = SocketAddressInet(HostInet::ANY, PortInet(1));
    if (!(a != b))
        return false;
    if (a == b)
        return false;

    // Test 5
    std::cout << "5. Test copy constuctor\n";
    SocketAddressInet c = b;
    if (c != b)
        return false;

    // Test 6.
    std::cout << "6. Construction from an already SocketAddress\n";
    SocketAddress tempAbs = SocketAddress(SocketAddress::FAMILY_INET);
    a = tempAbs;
    if (a.getStructPointer() == tempAbs.getStructPointer())
        return false;
    return true;
}
*/
