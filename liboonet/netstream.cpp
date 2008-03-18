#include "netstream.hpp"

namespace OONet
{
	netstream::netstream(SocketAddress & dest_addr)
		:m_socket()
	{
		m_socket.connect(dest_addr);
	}

	netstream::netstream()
		:m_socket()
	{}

	// Connect at an address
	void netstream::connect(const SocketAddress & dest_addr)
	{	// Create a new socket
		Socket tmp_socket(Socket::FAMILY_INET, Socket::TYPE_STREAM, Socket::PROTO_DEFAULT);

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
		m_socket = Socket();
	}

	void netstream::assign_socket(Socket & new_socket)
	{	pre_newsocket_impl(new_socket);
		m_socket = new_socket;
		post_newsocket_impl();
	}
};	// !OONet
