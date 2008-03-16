/**
@file Client.cpp
@brief Implementation of HTTP::Client class
*/
#include "Http/Client.h"

namespace OONet
{
	namespace HTTP
	{
		// Construct and connect
		Client::Client(const SocketAddressInet & _s_addr)
		{
			serv_addr = _s_addr;
			_ConnectToServer();
		}

		// Default constructor
		Client::Client()
		{}

		// Copy constructor
		Client::Client(const Client & r)
		{	OONET_THROW_EXCEPTION(ExceptionUnimplemented, "Never tested this function!");		}

		// Destructor
		Client::~Client()
		{
		    OONET_DEBUG_L2(_T("~HTTPClient()_\n"));
		    initialize_destruction();
		}

		// Copy operator
		Client & Client::operator=(const Client &r)
		{
			OONET_THROW_EXCEPTION(ExceptionUnimplemented, "Never implemented this function!");
			return *this;
		}

		// Make an http request
		Response Client::send(Request & req, long TimeOutMS)
		{	Response tmpResponse;
			BinaryData BinaryRequest, BinaryReply;

			// Check if we are connected
			if (! isConnected())
				OONET_THROW_EXCEPTION(ExceptionNotConnected, "Client is not yet connected!");

			// Process the request
			BinaryRequest = req.render();

			// Send it to net
			InetClient::send(BinaryRequest);

			// Wait for an answer to arrive
			OONET_DEBUG_L2(_T("HTTPClient::Send() request send waiting for result...\n"));
			try
			{
				SemAnswerArrived.wait(TimeOutMS);
				OONET_DEBUG_L2(_T("HTTPClient::Send() We got result!\n"));
			}
			catch(ExceptionTimeOut)
			{
			    OONET_DEBUG_L2(_T("HTTPClient::Send() timed out waiting for result..\n"));
				// Disconnect if connected
				if (isConnected())
					disconnect();
				// Maximum time reached
				OONET_THROW_EXCEPTION(ExceptionTimeOut, "Maximum time has been reached while waiting for an answer.");
			}

			// Gather answer
			WaitingToProcessData = WaitingToProcessData.getFrom(tmpResponse.parse(WaitingToProcessData));

			return tmpResponse;
		}

		// When data arrives from net
		void Client::OnDataArrived(const BinaryData & data)
		{	Response ResponsePacket;

			// Add data in queue
			WaitingToProcessData += data;

			// Check if a response arrived
			try
			{
				// Parse data
				ResponsePacket.parse(WaitingToProcessData);
				// Raise semaphore
				SemAnswerArrived.post();
			}
			catch(ExceptionIncomplete)
			{
				// No error here.. we must gather more packets
				OONET_DEBUG_L2(_T("HTTPClient::OnDataArrived() incomplete packet arrived\n"));
			}
			catch(ExceptionWrongFormat)
			{
			    OONET_DEBUG_L2(_T("HTTPClient::OnDataArrived() wrong formated packet arrived\n"));

				// Wrong response
				try {
                    disconnect();
				}catch (std::exception){}

				// And post semaphore
				SemAnswerArrived.post();
			}
		}

		// Ask to reconnect at server
		void Client::reconnect()
		{
			if (isConnected())
				disconnect();

			// Erase previous data
			WaitingToProcessData.clear();

			// And reconnect
			_ConnectToServer();
		}

		void Client::_ConnectToServer()
		{	connect(serv_addr);		}

		// Change host
		void Client::changeHost(const SocketAddressInet & _s_addr)
		{
			serv_addr = _s_addr;	// Store new server
			reconnect();			// And reconnect
		}
	}; // !HTTP Namespace
};	// !OONet namespace
