#include "test_benchmark.hpp"
#include <oonet/netserver.hpp>
#include <oonet/socket_address_inet.hpp>
#include <oonet/http/server.hpp>
#include <oonet/http/client.hpp>

namespace oonet
{
	static test_benchmark test_benchmark_inst;
	class bench_server;
	ulong total_data;


	class bench_client:
		public netstream_threaded
	{
	public:
		bench_client()
		{	cur_data = 0;
		}

		~bench_client()
		{}

		binary_data saved;
		mt::semaphore sem_arrived;
		ulong cur_data;
	protected:

		virtual void on_data_received(const binary_data & data)
		{	saved = data;
			cur_data += data.size();

			if (cur_data >= total_data)
				sem_arrived.post();
		}
	};

	// A Simple echo server
	class bench_server
		:public netserver<bench_client>
	{
	protected:

		virtual void parametrize_listen_socket(socket & listen_socket)
		{
			int reuse = 1;
		    listen_socket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		};

		void assign_handler(socket & cl_sock)
		{
			// Create a new handler
			handler_shared_ptr p_streamhandler(new bench_client);
			handlers_pool().push_back(p_streamhandler);

			// Assign socket to it
			p_streamhandler->assign_socket(cl_sock);
		}
	public:
		bench_server(ulong total)
		{	total_data = total;	}

		virtual ~bench_server()
		{	initialize_destruction();	}

		handlers_pool_type & pool()
		{	return handlers_pool();	}
	};


	class bench_http_server:
		public http::server
	{
	private:
		http::request saved;
		http::response test;
		ulong cur_data;

		virtual void parametrize_listen_socket(socket & l_sock)
		{
			int reuse = 1;
		    l_sock.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		};

	public:
		mt::semaphore sem_arrived;
		bench_http_server(ulong total)
		{
			total_data = total;
			cur_data = 0;
		}

		~bench_http_server()
		{	initialize_destruction();	}

		virtual http::response on_url_request(const http::request & full_request,
			const socket_address_inet & client_addr)
		{	saved = full_request;
			cur_data += full_request.body().size();

			if (cur_data >= total_data)
				sem_arrived.post();
			return test;
		}
	};

	// Sub tests implementation
	bool test_benchmark::TestTCPSpeed4G::OnExecute()
	{	bench_server server(4000000000);
		netstream_threaded client;
		binary_data test_d('a', 1000);

		// Start server
		server.start_listen(socket_address_inet(host_inet::ANY, port_inet(40421)), 10);

		// Connect
		client.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(40421)));
		for(long int i=0;i <= (4000*1000);i++)
		{
			client.send(test_d);
		}
		server.pool().front()->sem_arrived.wait();
		return true;
	}

	// Sub tests implementation
	bool test_benchmark::TestHTTPSpeed500Mb::OnExecute()
	{	bench_http_server server(500000000);
		netstream client;
		binary_data test_d('a', 1000);
		http::request tmp_req;
		tmp_req.body() = test_d;
		tmp_req.headers().add("Host", "www.google.com");
		tmp_req.request_method() = http::request::REQUEST_POST;
		test_d = tmp_req.render();
		binary_data blabla;
		// Start server
		server.start_listen(socket_address_inet(host_inet::ANY, port_inet(40422)), 10);

		// Connect
		client.connect(socket_address_inet(host_inet::LOCALHOST, port_inet(40422)));
		for(long int i=0;i <= (500*1000);i++)
		{
			client.send(test_d);
			blabla = client.receive(2000);
		}
		server.sem_arrived.wait();
		return true;
	}
};	// !oonet namespace
