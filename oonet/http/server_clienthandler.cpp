/**
@file server_clienthandler.cpp
@brief Implementation of http::server_clienthandler class
*/
#include "./server_clienthandler.hpp"
#include "./server.hpp"

namespace oonet
{
	namespace http
	{
		server_clienthandler::~server_clienthandler()
		{
			initialize_destruction();
		}

		void server_clienthandler::on_connected()
		{	stream_data.clear();										// Clear stream data
			peer_address = get_connection_socket().get_peer_address();	// Cache peer address
		}

		// When data arrives
		void server_clienthandler::on_data_received(const binary_data & data)
		{	request TmpRequest;
			response CustomResponse;

			// Push data in buffer
			stream_data += data;

			try
			{
				// Gather all packets
				while(TmpRequest.parse(stream_data, &stream_data))
				{
					// Triger server event
					CustomResponse = p_server->on_url_request(TmpRequest, peer_address);
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
