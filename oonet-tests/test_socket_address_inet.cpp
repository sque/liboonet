#include "test_socket_address_inet.hpp"
#include <oonet/socket_address_inet.hpp>

namespace oonet
{
	namespace test
	{
		test_socket_address_inet test_socket_address_inet_inst;

		bool test_socket_address_inet::TestCtor::operator()()
		{	socket_address_inet a;

			// Check if family is set correctly
			if (((sockaddr_in *)a.sockaddr_ptr())->sin_family != AF_INET)
				return false;
			return true;
		}

		bool test_socket_address_inet::TestHostPortCtor::operator()()
		{	socket_address_inet a(host_inet::LOCALHOST, port_inet(123));

			// Check if family is set correctly
			if (((sockaddr_in *)a.sockaddr_ptr())->sin_family != AF_INET)
				return false;

			// Check value of port
			if (a.get_port().to_string() != "123")
				return false;

			// Check value of host
			if (a.get_host().to_string() != "127.0.0.1")
				return false;
			return true;
		}

		bool test_socket_address_inet::TestResolverPortCtor::operator()()
		{	socket_address_inet a(host_resolver("192.1.3.4"), port_inet(1234));

			// Check if family is set correctly
			if (((sockaddr_in *)a.sockaddr_ptr())->sin_family != AF_INET)
				return false;

			// Check value of port
			if (a.get_port().to_string() != "1234")
				return false;

			// Check value of host
			if (a.get_host().to_string() != "192.1.3.4")
				return false;
			return true;
		}

		bool test_socket_address_inet::TestSockAddrCtor::operator()()
		{	socket_address gen_addr(socket_address::FAMILY_INET);

			// Populate it
			((SOCKADDR_IN *)gen_addr.sockaddr_ptr())->sin_port = htons(1324);

			// Create inet from existing
			socket_address_inet a(gen_addr);

			if (a.get_port().to_string() != "1324")
				return false;

			// change it to see if the changes are reflected
			((SOCKADDR_IN *)gen_addr.sockaddr_ptr())->sin_port = htons(1523);
			if (a.get_port().to_string() != "1324")
				return false;

			return true;
		}

		bool test_socket_address_inet::TestSockAddrNonInetCtor::operator()()
		{	socket_address gen_addr(socket_address::FAMILY_INET + 1);
			socket_address_inet a(gen_addr);	// This must fail
			return false;
		}


		bool test_socket_address_inet::TestCopyCtor::operator()()
		{	socket_address_inet a(host_resolver("192.1.3.4"), port_inet(1234));
			socket_address_inet b(a);

			// Check if family is set correctly
			if (((sockaddr_in *)b.sockaddr_ptr())->sin_family != AF_INET)
				return false;

			// Check value of port
			if (b.get_port().to_string() != "1234")
				return false;

			// Check value of host
			if (b.get_host().to_string() != "192.1.3.4")
				return false;

			// Change a value in a to see if it is reflected (reassinged pointers)
			a.set_port(2);
			if (b.get_port().to_string() != "1234")
				return false;
			return true;
		}

		bool test_socket_address_inet::TestCopyOperator::operator()()
		{	socket_address_inet a(host_resolver("192.1.3.4"), port_inet(1234));
			socket_address_inet b;

			// Copy
			b = a;
			// Check if family is set correctly
			if (((sockaddr_in *)b.sockaddr_ptr())->sin_family != AF_INET)
				return false;

			// Check value of port
			if (b.get_port().to_string() != "1234")
				return false;

			// Check value of host
			if (b.get_host().to_string() != "192.1.3.4")
				return false;

			// Change a value in a to see if it is reflected (reassinged pointers)
			a.set_port(2);
			if (b.get_port().to_string() != "1234")
				return false;

			return true;
		}

		bool test_socket_address_inet::TestCompOperator::operator()()
		{	socket_address_inet a(host_resolver("192.1.3.4"), port_inet(1234));
			socket_address_inet b(host_resolver("192.1.3.4"), port_inet(1236));
			socket_address_inet c(host_resolver("192.1.3.5"), port_inet(1234));
			socket_address_inet d(host_resolver("192.1.3.4"), port_inet(1234));

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

		bool test_socket_address_inet::TestInCompOperator::operator()()
		{	socket_address_inet a(host_resolver("192.1.3.4"), port_inet(1234));
			socket_address_inet b(host_resolver("192.1.3.4"), port_inet(1236));
			socket_address_inet c(host_resolver("192.1.3.5"), port_inet(1234));
			socket_address_inet d(host_resolver("192.1.3.4"), port_inet(1234));

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

		bool test_socket_address_inet::TestSetHost::operator()()
		{	socket_address_inet a(host_resolver("192.1.3.4"), port_inet(1234));

			// Assign a new host
			a.set_host(host_inet::LOCALHOST);

			// Check if family is set correctly
			if (((sockaddr_in *)a.sockaddr_ptr())->sin_family != AF_INET)
				return false;

			// Check value of port
			if (a.get_port().to_string() != "1234")
				return false;

			// Check value of host
			if (a.get_host().to_string() != "127.0.0.1")
				return false;

			// Check in structure value of host
			if (((sockaddr_in *)a.sockaddr_ptr())->sin_addr.s_addr != host_inet::LOCALHOST.get_nbo())
				return false;
			return true;
		}

		bool test_socket_address_inet::TestSetPost::operator()()
		{	socket_address_inet a(host_resolver("192.1.3.4"), port_inet(1234));

			// Assign a new host
			a.set_port(8512);

			// Check if family is set correctly
			if (((sockaddr_in *)a.sockaddr_ptr())->sin_family != AF_INET)
				return false;

			// Check value of port
			if (a.get_port().to_string() != "8512")
				return false;

			// Check value of host
			if (a.get_host().to_string() != "192.1.3.4")
				return false;

			// Check in structure value of host
			if (((sockaddr_in *)a.sockaddr_ptr())->sin_port != ntohs(8512))
				return false;
			return true;
		}
		bool test_socket_address_inet::TestDefaultValues::operator()()
		{	socket_address_inet a;

			if (a.get_host().to_string() != "0.0.0.0")
				return false;

			if (a.get_port().to_string() != "0")
				return false;

			return true;
		}
	}	// !test namespace
};	// !oonet namespace
/*
bool test_socket_address_inet(void)
{
    // Test 1.
    std::cout << "1. Create some socket_address_inet objects\n";
    socket_address_inet a, b;

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
    a = socket_address_inet(HostInet::ANY, PortInet(0));
    b = socket_address_inet(HostInet::ANY, PortInet(1));
    if (!(a != b))
        return false;
    if (a == b)
        return false;

    // Test 5
    std::cout << "5. Test copy constuctor\n";
    socket_address_inet c = b;
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
