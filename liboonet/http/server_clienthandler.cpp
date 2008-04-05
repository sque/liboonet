/**
@file ClientHandler.cpp
@brief Implementation of http::ClientHandler class
*/
#include "./server_clienthandler.hpp"
#include "./server.hpp"

namespace oonet
{
	namespace http
	{
		// When data arrives
		void server_clienthandler::on_data_received(const binary_data & data)
		{	Request TmpRequest;
			Response CustomResponse;

			// Push data in buffer
			stream_data += data;

			try
			{
				// Gather all packets
				while(TmpRequest.parse(stream_data, &stream_data))
				{
					// Triger server event
					CustomResponse = get_server_ptr()->on_url_request(TmpRequest.url, TmpRequest, get_connection_socket().get_peer_address());
					// Add extra header for connection control
					CustomResponse.headers().set("Connection", "Keep-Alive");
					// Send response
					send(CustomResponse.render());
				}
			}
			catch(exception)
			{
				// This mean the end of connection
				disconnect();
			}
		}
	};	// !HTTP Namespace
};	// !oonet namespace
