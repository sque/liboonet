/**
@file Server.cpp
@brief Implementation of HTTP::Server class
*/
#include "Http/Server.h"

namespace oonet
{
	namespace HTTP
	{
		Server::Server(void)
		{
		}

		Server::~Server(void)
		{}


		ClientHandler * Server::impl_new_handler(Socket & cl_socket)
		{	client_iterator it;
			ClientHandler * p_handler;

			// Try to recycle a disconnected one
			for(it = v_pclients.begin();it != v_pclients.end();it++)
			{	p_handler = *it;
				if (! p_handler->connected())
				{
					return p_handler;
				}
			}

			// Create new one
			p_handler = new ClientHandler(this);
			v_pclients.push_back(p_handler);

			return p_handler;
		}

	};	// !HTTP namespace
};	// !oonet namespace
