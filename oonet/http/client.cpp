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
			:b_waiting_answer(false)
		{}

		client::client(const socket_address_inet & dst_addr)
			:b_waiting_answer(false)
		{	connect(dst_addr);		}

		// Destructor
		client::~client()
		{	initialize_destruction();	}



		// Make an http request
		response client::send(request & req, long tm_timeoutms)
		{	response tmp_response;
			if (!connected())
				OONET_THROW_EXCEPTION(ExceptionNotConnected,
					"You must connect before sending an http request!");

			// Initialize flags
			b_have_response = false;
			b_waiting_answer = true;

			// Send Real data
			netstream_threaded::send(req.render());

			// Wait for answer
			try	{	sem_answer_received.wait(tm_timeoutms);	}
			catch(oonet::exception)
			{	// Stream is broken, we need to disconnect
				b_waiting_answer = false;
				disconnect();
				throw;
			}
			b_waiting_answer = false;

			// Event raised
			if (b_have_response)
				return m_last_response;
			else if (!tmp_response.parse(dt_unprocessed))
				OONET_THROW_EXCEPTION(ExceptionIncomplete, "Couldn't gather the whole message before connection get closed.");

			OONET_ASSERT(0);	// This point is unreachable!
		}

		// When data arrives from net
		void client::on_data_received(const binary_data & dt_received)
		{	binary_data dt_remain;

			// Push data in queue
			dt_unprocessed += dt_received;

			// Parse last response
			try
			{
				if (m_last_response.parse(dt_unprocessed, &dt_remain))
				{
					b_have_response = true;
					dt_unprocessed = dt_remain;
					sem_answer_received.post();
				}
			}
			catch(oonet::exception)
			{
				sem_answer_received.post();
			}
		}

		void client::connect(const socket_address_inet & dest_addr)
		{
			netstream_threaded::connect(dest_addr);
		}

		void client::on_disconnected()
		{
			if (b_waiting_answer)
				sem_answer_received.post();

			// Clear data
			b_waiting_answer = false;
			dt_unprocessed.clear();
		}

	}; // !HTTP Namespace
};	// !oonet namespace
