
set(OONET_TESTS_SOURCES
	main.cpp
	oonet-tests.h
	test_benchmark.cpp
	test_benchmark.hpp
	test_binary_data.cpp
	test_binary_data.hpp
	test_buffer.cpp
	test_buffer.hpp
	test_host_inet.cpp
	test_host_inet.hpp
	test_host_resolver.cpp
	test_host_resolver.hpp
	test_http_client.cpp
	test_http_client.hpp
	test_http_headers_list.cpp
	test_http_headers_list.hpp
	test_http_message.cpp
	test_http_message.hpp
	test_http_request.cpp
	test_http_request.hpp
	test_http_response.cpp
	test_http_response.hpp
	test_http_server.cpp
	test_http_server.hpp
	test_mutex.cpp
	test_mutex.hpp
	test_netserver.cpp
	test_netserver.hpp
	test_netstream_threaded.cpp
	test_netstream_threaded.h
	test_port_inet.cpp
	test_port_inet.hpp
	test_semaphore.cpp
	test_semaphore.hpp
	test_serialize.cpp
	test_serialize.hpp
	test_socket_address_inet.cpp
	test_socket_address_inet.hpp
	test_socket.cpp
	test_socket.hpp
	TestStringConverter.cpp
	TestStringConverter.h
	test_thread.cpp
	test_thread.hpp
	test_url.cpp
	test_url.hpp
)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(oonet-tests ${OONET_TESTS_SOURCES})
target_link_libraries(oonet-tests oonet pthread)

