
set(OONET_SOURCES oonet.cpp
	base64.cpp
	binary_data.cpp
	buffer.cpp
	exception.cpp
	host_inet.cpp
	host_resolver.cpp
	mutex_impl_posix.cpp
	netstream.cpp
	netstream_threaded.cpp
	port_inet.cpp
	semaphore_impl_posix.cpp
	socket_address.cpp
	socket_address_inet.cpp
	socket.cpp
	socket_impl_posix.cpp
	string_converter.cpp
	test.cpp
	thread.cpp
	thread_impl_posix.cpp
	http/client.cpp
	http/headers_list.cpp
	http/message.cpp
	http/request.cpp
	http/response.cpp
	http/server_clienthandler.cpp
	http/server.cpp
	http/url.cpp
)

add_library(oonet ${OONET_SOURCES})

