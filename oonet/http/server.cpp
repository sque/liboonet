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


		void server::assign_handler(socket & cl_socket)
		{	handlers_pool_iterator it;
			handler_shared_ptr p_handler;

			// Try to recycle a disconnected one
			for(it = handlers_pool().begin();it != handlers_pool().end();it++)
			{	p_handler = *it;
				if (! p_handler->connected())
				{	p_handler->assign_socket(cl_socket);
					return;
				}
			}

			// Create new one
			p_handler = handler_shared_ptr(new server_clienthandler(this));
			handlers_pool().push_back(p_handler);
			p_handler->assign_socket(cl_socket);
		}

	};	// !http namespace
};	// !oonet namespace
