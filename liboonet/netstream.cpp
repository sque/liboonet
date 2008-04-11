#include "netstream.hpp"

namespace oonet
{
	netstream::netstream(socket_address & dest_addr)
		:m_socket()
	{
		m_socket.connect(dest_addr);
	}

	// Create a netstream and use a connected socket
	netstream::netstream(socket & new_sock)
		:m_socket(new_sock)
	{}

	netstream::netstream()
		:m_socket()
	{}

	// Connect at an address
	void netstream::connect(const socket_address & dest_addr)
	{	// Create a new socket
		socket tmp_socket(socket::FAMILY_INET, socket::TYPE_STREAM, socket::PROTO_DEFAULT);

		// Connect
		tmp_socket.connect(dest_addr);

		// Assign new socket
		assign_socket(tmp_socket);
	}

	// Disconnect stream and abandon socket
	void netstream::disconnect()
	{
		// Shutdown connection
		m_socket.shutdown();

		// Abandon socket
		{mt::scoped_lock l(mut_change_socket);
			m_socket = socket();
		}
	}

	void netstream::assign_socket(socket & new_socket)
	{
		pre_newsocket_impl(new_socket);
		
		{mt::scoped_lock l(mut_change_socket);
			m_socket = new_socket;
		}
		post_newsocket_impl();
	}
};	// !OONet
