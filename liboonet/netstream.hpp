#ifndef NETSTREAM_HPP_INCLUDED
#define NETSTREAM_HPP_INCLUDED

#include "OONet.h"
#include "Socket.h"

namespace OONet
{
	class netstream
	{
	private:
		// NonCopyable
		netstream(const netstream&);
		netstream & operator=(const netstream &);

		// Socket of stream
		Socket m_socket;
	protected:
		// Event raised when a new socket is assigned
		virtual void pre_newsocket_impl(Socket & n_sock){}

		// Event raised after a new socket is assigned
		virtual void post_newsocket_impl(){}

	public:
		// Create a netstream and connect at specific address
		netstream(SocketAddress &);

		// Create a netstream and use a connected socket
		netstream(Socket &);

		// Create netstream without a binded address
		netstream();

		// Destructor
		virtual ~netstream(){};

		// Connect at an address
		void connect(const SocketAddress &);

		// Bind on existing socket
		void assign_socket(Socket &);

		// Disconnect stream and abandon socket
		void disconnect();

		// Send data
		inline size_t send(const BinaryData & data)
		{	return m_socket.send(data);	}

		// Receive data
		BinaryData receive(size_t max_data)
		{	return m_socket.receive(max_data);	}

		// Get connection socket
		inline const Socket & get_connection_socket() const
		{	return m_socket;	}
	};	//	!netstream
};	// !OONet

#endif // NETSTREAM_HPP_INCLUDED
