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
		// Get request
		bool server_clienthandler::get_request(Request & req)
		{	size_t ActualData;

			// Parse request
			try
			{	ActualData = req.parse(streamData);	}
			catch(ExceptionIncomplete)
			{
				return false;
			}

			// Substract from stream
			streamData = streamData.get_from(ActualData);

			return true;
		}

		// When data arrives
		void server_clienthandler::on_data_received(const binary_data & data)
		{	Request TmpRequest;
			Response CustomResponse;

			// Push data in buffer
			streamData += data;

			try
			{
				// Gather all packets
				while(get_request(TmpRequest))
				{
					// Triger server event
					CustomResponse = get_server_ptr()->on_url_request(TmpRequest.url, TmpRequest, get_connection_socket().get_peer_address());
					// Add extra header for connection control
					CustomResponse.getHeaders().setHeader("Connection", "Keep-Alive");
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
