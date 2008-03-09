/**
@file ClientHandler.cpp
@brief Implementation of HTTP::ClientHandler class
*/
#include "Http/ClientHandler.h"
#include "Http/Server.h"

namespace Slib
{
	namespace HTTP
	{
		// Constructor
		ClientHandler::ClientHandler(HTTP::Server * _pServer)
		{
			pServer = _pServer;
		}

		// Copy Constructor
		ClientHandler::ClientHandler(const ClientHandler &r)
		{	SLIB_THROW_EXCEPTION(ExceptionUnimplemented,
				"ClientHandler is not yet supported to be copiable"
			);
		}

		ClientHandler::~ClientHandler(void)
		{
			initializeDestruction();
		}

		// Copy operator
		ClientHandler & ClientHandler::operator=(const ClientHandler &r)
		{
			SLIB_THROW_EXCEPTION(ExceptionUnimplemented,
				"ClientHandler is not yet supported to be copiable"
			);
			return *this;
		}

		// Get request
		bool ClientHandler::GetRequest(Request & req)
		{	size_t ActualData;

			// Parse request
			try
			{	ActualData = req.parse(streamData);	}
			catch(ExceptionIncomplete)
			{
				return false;
			}

			// Substract from stream
			streamData = streamData.getFrom(ActualData);

			return true;
		}

		// When data arrives
		void ClientHandler::OnDataArrived(const BinaryData & data)
		{	Request TmpRequest;
			Response CustomResponse;

			// Push data in buffer
			streamData += data;

			try
			{
				// Gather all packets
				while(GetRequest(TmpRequest))
				{
					// Triger server event
					CustomResponse = pServer->OnURLRequest(TmpRequest.url, TmpRequest, getRemotePeerAddress());
					// Add extra header for connection control
					CustomResponse.getHeaders().setHeader("Connection", "Keep-Alive");
					// Send response
					send(CustomResponse.render());
				}
			}
			catch(Exception)
			{

				// This mean the end of connection
				disconnect();
			}
		}
	};	//! HTTP Namespace
};	//! Slib namespace
