/**
@file Server.cpp
@brief Implementation of http::Server class
*/
#include "./server.hpp"

namespace oonet
{
	namespace http
	{
		server::server(void)
		{
		}

		server::~server(void)
		{	initialize_destruction();	}


		server_clienthandler * server::impl_new_handler(socket & cl_socket)
		{	client_iterator it;
			server_clienthandler * p_handler;

			// Try to recycle a disconnected one
			for(it = v_pclients.begin();it != v_pclients.end();it++)
			{	p_handler = *it;
				if (! p_handler->connected())
				{
					return p_handler;
				}
			}

			// Create new one
			p_handler = new server_clienthandler(this);
			v_pclients.push_back(p_handler);

			return p_handler;
		}

	};	// !http namespace
};	// !oonet namespace
