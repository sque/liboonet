
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

set(OONET_HEADERS
	base64.hpp
	binary_data.hpp
	buffer.hpp
	exception.hpp
	host_inet.hpp
	host_resolver.hpp
	mutex.hpp
	netserver.hpp
	netstream.hpp
	netstream_threaded.hpp
	oonet.hpp
	port_inet.hpp
	scoped_lock.hpp
	semaphore.hpp
	serialization.hpp
	serialization_operators.hpp
	socket_address.hpp
	socket_address_inet.hpp
	socket.hpp
	test.hpp
	thread.hpp
	string_converter.h
)
set(OONET_HTTP_HEADERS
	http/client.hpp
	http/headers_list.hpp
	http/message.hpp
	http/request.hpp
	http/response.hpp
	http/server_clienthandler.hpp
	http/server.hpp
	http/url.hpp
)

add_library(oonet ${OONET_SOURCES})
install(TARGETS oonet RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${OONET_HEADERS} DESTINATION include/oonet)
install(FILES ${OONET_HTTP_HEADERS} DESTINATION include/oonet/http)

