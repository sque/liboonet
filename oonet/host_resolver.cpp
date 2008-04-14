/**
 @file host_resolver.cpp
 @brief Implementation of the host_resolver class.
 */
#include "./host_resolver.hpp"

namespace oonet
{
	// Copy constructor
	host_resolver::host_resolver(const host_resolver &r) throw()
	{
		// Copy all data
		s_official_name = r.s_official_name;
		qu_addresses = r.qu_addresses;
		for (int i = 0;i < qu_addresses;i++)
			a_address_list[i] = r.a_address_list[i];
	}

	// Default constructor
	host_resolver::host_resolver(const string & hostname)
	{
		struct hostent *p_temp;
		struct in_addr addr;

		// Initialize info of host
		s_official_name = hostname;
		qu_addresses = 0;

		// Try to resolve by dns.
		p_temp = gethostbyname(hostname.c_str());
		if (p_temp != NULL)
		{   // Found by dns

			// Count addresses
			qu_addresses = 0;
			while (p_temp->h_addr_list[++qu_addresses] != NULL);

			// Copy one by one addresses
			for(int i = 0;i < qu_addresses;i++)
				a_address_list[i] = host_inet(ntohl(*(ulong *)p_temp->h_addr_list[i]));

			// Copy official name
			if (p_temp->h_name)
				s_official_name = p_temp->h_name;
			return;
		}

		//Else check if the string contains the ip in human-readable way.
		if ((addr.s_addr = inet_addr(hostname.c_str())) != 0xffffffff)
		{
				// It was an ip in string format.
				qu_addresses = 1;
				a_address_list[0] = host_inet(ntohl((ulong)addr.s_addr));
				return;
		}

		// Error not found
		OONET_THROW_EXCEPTION(ExceptionServerNotFound,
			string("Cannot resolve host's address: ") + hostname);
	}

	// Get official name
	const string & host_resolver::get_official_name() const throw()
	{
		return s_official_name;
	}

	// Get the address from list
	const host_inet & host_resolver::get_host(int a) const
	{

		// Check if there is that address
		if (a >= qu_addresses)
		{
			OONET_THROW_EXCEPTION(ExceptionNotFound,
				"Requested address out of address-list limits!");
			return host_inet::ANY;
		}

		return a_address_list[a];
	}

	host_resolver::operator const host_inet & () const
	{
		return get_host();
	}

	// Return the size of the address list
	int host_resolver::count_hosts() const
	{
		return qu_addresses;
	}
};	// !oonet namespace
