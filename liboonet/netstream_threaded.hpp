#ifndef NETSTREAM_THREADED_HPP_INCLUDED
#define NETSTREAM_THREADED_HPP_INCLUDED

#include "OONet.h"
#include "Thread.h"
#include "Semaphore.h"
#include "netstream.hpp"

namespace OONet
{

	class netstream_threaded
		: public netstream,	private MT::Thread
	{
	private:
		// NonCopyable
		netstream_threaded(const netstream_threaded &);
		const netstream_threaded & operator=(const netstream_threaded &);

		// Hide receive
		BinaryData receive(size_t);

		// Implement events
		void thread_routine();
		void pre_newsocket_impl(Socket &);
		void post_newsocket_impl();

		// Private Data
		bool b_connected;			// A flag if we are connected
		MT::Semaphore sem_connect;	// Semaphore used when data collection thread is started
	protected:
		// Events
		virtual void on_data_received(const BinaryData &){};
		virtual void on_connected(){};
		virtual void on_disconnected(){};

	public:
		// Constructor
		netstream_threaded();

		// Destructor
		virtual ~netstream_threaded();

		// Return if it is connected
		inline bool connected() const
		{	return b_connected;	}

	};	// !netstream_threaded
};	// !OONet

#endif // NETSTREAM_THREADED_HPP_INCLUDED
