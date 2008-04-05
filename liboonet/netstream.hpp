#ifndef NETSTREAM_HPP_INCLUDED
#define NETSTREAM_HPP_INCLUDED

#include "./oonet.hpp"
#include "./socket.hpp"

namespace oonet
{
	class netstream
	{
	private:
		// NonCopyable
		netstream(const netstream&);
		netstream & operator=(const netstream &);

		// Socket of stream
		socket m_socket;
	protected:
		// Event raised when a new socket is assigned
		virtual void pre_newsocket_impl(socket & n_sock){}

		// Event raised after a new socket is assigned
		virtual void post_newsocket_impl(){}

	public:
		// Create a netstream and connect at specific address
		netstream(socket_address &);

		// Create a netstream and use a connected socket
		netstream(socket &);

		// Create netstream without a binded address
		netstream();

		// Destructor
		virtual ~netstream(){};

		// Connect at an address
		void connect(const socket_address &);

		// Bind on existing socket
		void assign_socket(socket &);

		// Disconnect stream and abandon socket
		void disconnect();

		// Send data
		inline size_t send(const binary_data & data)
		{	return m_socket.send(data);	}

		// Receive data
		binary_data receive(size_t max_data)
		{	return m_socket.receive(max_data);	}

		// Get connection socket
		inline const socket & get_connection_socket() const
		{	return m_socket;	}
	};	//	!netstream
};	// !OONet

#endif // NETSTREAM_HPP_INCLUDED
