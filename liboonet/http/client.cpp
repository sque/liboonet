/**
@file Client.cpp
@brief Implementation of http::Client class
*/
#include "./client.hpp"
#include "../scoped_lock.hpp"

namespace oonet
{
	namespace http
	{
		// Default constructor
		Client::Client()
			:b_waiting_anwser(false)
		{}

		Client::Client(const socket_address & dst_addr)
			:b_waiting_anwser(false)
		{	connect(dst_addr);		}

		// Destructor
		Client::~Client()
		{}



		// Make an http request
		response Client::send(request & req, long TimeOutMS)
		{	response tmpResponse;
			binary_data BinaryRequest, BinaryReply;

			// Check if we are connected
			if (! connected())
				OONET_THROW_EXCEPTION(ExceptionNotConnected, "Client is not yet connected!");

			// Process the request
			BinaryRequest = req.render();

			// Send it to net
			b_waiting_anwser = true;
			netstream_threaded::send(BinaryRequest);

			// Wait for an answer to arrive
			try
			{
				sem_anwser_arrived.wait(TimeOutMS);
			}
			catch(ExceptionTimeOut)
			{	// Disconnect as the http pipeline will be broken
				if (connected())
					disconnect();
				// Maximum time reached
				OONET_THROW_EXCEPTION(ExceptionTimeOut, "Maximum time has been reached while waiting for an answer.");
			}

			// Gather answer
			{mt::scoped_lock m(mux_access_data);
				if (!tmpResponse.parse(WaitingToProcessData, &WaitingToProcessData ))
					OONET_THROW_EXCEPTION(ExceptionIncomplete, "Couldn't gather the whole packet before connection get closed.");
			}

			return tmpResponse;
		}

		// When data arrives from net
		void Client::on_data_received(const binary_data & data)
		{	response ResponsePacket;

			// Add data in queue
			{mt::scoped_lock m(mux_access_data);
				WaitingToProcessData += data;
			}

			// Check if a response arrived
			try
			{
				// Parse data
				if (!ResponsePacket.parse(WaitingToProcessData))
					return;

				// Raise semaphore
				b_waiting_anwser = false;
				sem_anwser_arrived.post();
			}
			catch(ExceptionWrongFormat)
			{
				// Wrong response
				disconnect();

				// Unlock to get answer
				b_waiting_anwser = false;
				sem_anwser_arrived.post();
			}
		}

		void Client::connect(const socket_address_inet & dest_addr)
		{
			// Clear data
			{mt::scoped_lock m(mux_access_data);
				WaitingToProcessData.clear();
			}

			b_waiting_anwser = false;
			netstream_threaded::connect(dest_addr);
		}

		void Client::on_disconnected()
		{	if (b_waiting_anwser)
				sem_anwser_arrived.post();
		}

	}; // !HTTP Namespace
};	// !oonet namespace
