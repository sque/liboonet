#ifndef NETSTREAM_THREADED_HPP_INCLUDED
#define NETSTREAM_THREADED_HPP_INCLUDED

#include "./oonet.hpp"
#include "./thread.hpp"
#include "./semaphore.hpp"
#include "./netstream.hpp"

namespace oonet
{

	class netstream_threaded
		: public netstream,	private MT::thread
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
		bool b_zombie;					// A flag if we are getting destroyed
		bool b_connected;				// A flag if we are connected
		MT::semaphore sem_connect;		// Semaphore used when new assigned socket is ready
		MT::semaphore sem_newsocket;	// Semaphore when new socket is assigned to stream
		MT::semaphore sem_disconnect;	// Semaphore when current assigned socket gets disconnected

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
