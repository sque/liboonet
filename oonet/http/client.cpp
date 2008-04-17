/**
@file client.cpp
@brief Implementation of http::client class
*/
#include "./client.hpp"
#include "../scoped_lock.hpp"

namespace oonet
{
	namespace http
	{
		// Default constructor
		client::client()
			:b_waiting_anwser(false)
		{}

		client::client(const socket_address_inet & dst_addr)
			:b_waiting_anwser(false)
		{	connect(dst_addr);		}

		// Destructor
		client::~client()
		{	initialize_destruction();	}



		// Make an http request
		response client::send(request & req, long TimeOutMS)
		{	binary_data BinaryRequest;

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
				OONET_THROW_EXCEPTION(ExceptionTimeOut,
					"Maximum time has been reached while waiting for an answer.");
			}

			// Gather answer
			{mt::scoped_lock m(mux_access_data);

				if (m_response_queue.size() > 0)
				{
					response tmpResponse(m_response_queue.front());
					m_response_queue.pop_front();
					return tmpResponse;
				}

				//if (!tmpResponse.parse(WaitingToProcessData))
					//OONET_THROW_EXCEPTION(ExceptionIncomplete, "Couldn't gather the whole message before connection get closed.");

			}
		}

		// When data arrives from net
		void client::on_data_received(const binary_data & data)
		{	response ResponsePacket;

			// Add data in queue
			{mt::scoped_lock m(mux_access_data);
				WaitingToProcessData += data;

				// Check if a response arrived
				try
				{
					// Parse data
					if (!ResponsePacket.parse(WaitingToProcessData, &WaitingToProcessData))
						return;

					// Save result
					m_response_queue.push_back(ResponsePacket);
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
		}

		void client::connect(const socket_address_inet & dest_addr)
		{
			// Clear data
			{mt::scoped_lock m(mux_access_data);
				WaitingToProcessData.clear();
				m_response_queue.clear();
			}

			b_waiting_anwser = false;
			netstream_threaded::connect(dest_addr);
		}

		void client::on_disconnected()
		{	if (b_waiting_anwser)
				sem_anwser_arrived.post();
		}

	}; // !HTTP Namespace
};	// !oonet namespace
