#ifndef OONET_HOSTRESOLVER_H_INCLUDED
#define OONET_HOSTRESOLVER_H_INCLUDED

#include "./oonet.hpp"
#include "./host_inet.hpp"

namespace oonet
{

	//! A class for resolving a dns to HostInet
	/**
		It will automatically translate a dns or FQDN to network address or
		convert a human-readable 4 dotted ip to a HostInet address.
	*/
	class host_resolver
	{
	public:
		// Exceptions
		OONET_DECLARE_EXCEPTION(ExceptionServerNotFound);

	private:
		//! The official name of the host
		string s_official_name;

		//! The address list saved in host byte-order.
		host_inet a_address_list[OONET_RESOLVER_MAX_ADDRESSES];

		//! The quantity of addresses
		int qu_addresses;
	public:

		//! Constructor that will try to resolve a specific hostname
		/**
			It will try to resolve by dns or check if it is an ip in dotted format.
		@throw ExceptionServerNotFound Raised if it is unable to do either of those actions.
		@param hostname The name or ip of the host you want to resolve address.
		*/
		explicit host_resolver(const string & hostname);

		//! Copy constructor
		host_resolver(const host_resolver &r) throw();

		//! Destructor
		virtual ~host_resolver(){}

		//! Get the official name of resolved host.
		/**
			It returns, if exists one, the official name of the host that was
			resolved at construction time.
		*/
		const string & get_official_name() const throw();

		//! Direct cast to HostInet address
		/**
			It will get the first HostInet in the list that
			was retrieved at construction time.
		*/
		operator const host_inet & () const;

		//! Get one of the HostInet addresses of the resolved host.
		/**
			DNS support multiple ips over one name, those ip are retrived
			by this function. By default it returs the 1st address
		@param a The index of the address list (zero-based). By default it is passed 0.
		@return The HostInet address of the host.
		@throw ExceptionNotFound If requested index of address is outside the maximum of resolved.
		@see getAddressCount
		*/
		const host_inet & get_host(int a = 0) const;

		//! Get the quantity of addresses of this host.
		int count_hosts() const;

	};  // !HostResolver class
};	// !oonet namespace

#endif // OONET_HOSTRESOLVER_H_INCLUDED
