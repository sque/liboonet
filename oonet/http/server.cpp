/**
@file server.cpp
@brief Implementation of http::server class
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


		netserver<server_clienthandler>::handler_shared_ptr server::impl_new_handler(socket & cl_socket)
		{	handlers_pool_iterator it;
			handler_shared_ptr p_handler;

			// Try to recycle a disconnected one
			for(it = m_handlers_pool.begin();it != m_handlers_pool.end();it++)
			{	p_handler = *it;
				if (! p_handler->connected())
				{
					return p_handler;
				}
			}

			// Create new one
			p_handler = handler_shared_ptr(new server_clienthandler(this));
			m_handlers_pool.push_back(p_handler);

			return p_handler;
		}

	};	// !http namespace
};	// !oonet namespace
