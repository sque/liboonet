#ifndef OONET_HTTP_SERVER_CLIENTHANDLER_HPP_INCLUDED
#define OONET_HTTP_SERVER_CLIENTHANDLER_HPP_INCLUDED

#include "../oonet.hpp"
#include "../netserver.hpp"

namespace oonet
{
	namespace http
	{
		class server;

		/**
		* The handler of client for the Server
		*/
		class server_clienthandler
			:public netserver_clienthandler<server>
		{
		private:
			// A buffer with the data
			binary_data stream_data;
			socket_address peer_address;

			// httpserver_clienthandler is NonCopyable
			server_clienthandler(const server_clienthandler &);
			server_clienthandler & operator=(server_clienthandler &);

		protected:
			// When data arrives
			virtual void on_data_received(const binary_data & data);

			// On new connection reset buffer
			virtual void on_connected();

		public:

			// Constructor
			server_clienthandler(void * _s)
				:netserver_clienthandler<server>(_s),
				peer_address(socket_address::FAMILY_INET)
			{}

			// Destructor
			virtual ~server_clienthandler(void);


		};
	};	// !http namespace
};	// !oonet namespace

#endif // !OONET_HTTP_SERVER_CLIENTHANDLER_HPP_INCLUDED
