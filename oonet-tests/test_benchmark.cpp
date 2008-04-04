#include "test_benchmark.hpp"
#include "netserver.hpp"
#include "socket_address_inet.hpp"
#include "Http/Server.h"
#include "Http/Client.h"

namespace oonet
{
	static test_benchmark test_benchmark_inst;
	class bench_server;
	ulong total_data;


	class bench_client:
		public netserver_clienthandler<bench_server>
	{
	public:
		bench_client(void * s)
			:netserver_clienthandler<bench_server>(s)
		{	cur_data = 0;
		}

		~bench_client()
		{}

		binary_data saved;
		MT::semaphore sem_arrived;
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

		virtual void parametrize_listen_socket(Socket & listen_socket)
		{
			int reuse = 1;
		    listen_socket.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		};
	public:
		bench_server(ulong total)
		{	total_data = total;	}

		virtual ~bench_server()
		{	initialize_destruction();	}
	};


	class bench_http_server:
		public HTTP::Server
	{
	private:
		HTTP::Request saved;
		HTTP::Response test;
		ulong cur_data;

		virtual void parametrize_listen_socket(Socket & l_sock)
		{
			int reuse = 1;
		    l_sock.set_option(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		};

	public:
		MT::semaphore sem_arrived;
		bench_http_server(ulong total)
		{
			total_data = total;
			cur_data = 0;
		}

		~bench_http_server()
		{	initialize_destruction();	}

		virtual HTTP::Response on_url_request(const HTTP::Url & Uri,
			const HTTP::Request & full_request,
			const SocketAddressInet & client_addr)
		{	saved = full_request;
			cur_data += full_request.getBody().size();

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
		server.start_listen(SocketAddressInet(HostInet::ANY, PortInet(40421)), 10);

		// Connect
		client.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(40421)));
		for(long int i=0;i <= (4000*1000);i++)
		{
			client.send(test_d);
		}
		server.get_clients().front()->sem_arrived.wait();
		return true;
	}

	// Sub tests implementation
	bool test_benchmark::TestHTTPSpeed500Mb::OnExecute()
	{	bench_http_server server(500000000);
		netstream client;
		binary_data test_d('a', 1000);
		HTTP::Request tmp_req;
		tmp_req.setBody(test_d);
		tmp_req.getHeaders().setHeader("Host", "www.google.com");
		tmp_req.http_type = HTTP::Request::REQUEST_POST;
		test_d = tmp_req.render();
		binary_data blabla;
		// Start server
		server.start_listen(SocketAddressInet(HostInet::ANY, PortInet(40422)), 10);

		// Connect
		client.connect(SocketAddressInet(HostInet::LOCALHOST, PortInet(40422)));
		for(long int i=0;i <= (500*1000);i++)
		{
			client.send(test_d);
			blabla = client.receive(2000);
		}
		server.sem_arrived.wait();
		return true;
	}
};	// !oonet namespace
