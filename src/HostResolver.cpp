/**
 @file HostResolver.cpp
 @brief Implementation of the HostResolver class.
 */
#include "./HostResolver.h"
#include "./StringConverter.h"

namespace Slib
{
	// Copy constructor
	HostResolver::HostResolver(const HostResolver &r) throw()
	{
		// Copy all data
		sOfficialName = r.sOfficialName;
		mAddresses = r.mAddresses;
		for (int i = 0;i < mAddresses;i++)
			aAddressList[i] = r.aAddressList[i];
	}

	// Default constructor
	HostResolver::HostResolver(const string & hostname) throw(Exception)
	{
		struct hostent *p_temp;
		struct in_addr addr;

		// Initialize info of host
		sOfficialName = hostname;
		mAddresses = 0;

		// Try to resolve by dns.
		p_temp = gethostbyname(hostname.c_str());
		if (p_temp != NULL)
		{   // Found by dns

			// Count addresses
			mAddresses = 0;
			while (p_temp->h_addr_list[++mAddresses] != NULL);

			// Copy one by one addresses
			for(int i = 0;i < mAddresses;i++)
				aAddressList[i] = HostInet(ntohl(*(ulong *)p_temp->h_addr_list[i]));

			// Copy official name
			if (p_temp->h_name)
				sOfficialName = p_temp->h_name;
			return;
		}

		//Else check if the string contains the ip in human-readable way.
		if ((addr.s_addr = inet_addr(hostname.c_str())) != 0xffffffff)
		{
				// It was an ip in string format.
				mAddresses = 1;
				aAddressList[0] = HostInet(ntohl((ulong)addr.s_addr));
				return;
		}

		// Error not found
		SLIB_THROW_EXCEPTION(ExceptionServerNotFound,
			string("Cannot resolve host's address: ") + hostname);
	}

	// Get official name
	const string & HostResolver::getOfficialName() const throw()
	{
		return sOfficialName;
	}

	// Get the address from list
	const HostInet & HostResolver::getAddress(int a) const throw(Exception)
	{

		// Check if there is that address
		if (a >= mAddresses)
		{
			SLIB_THROW_EXCEPTION(ExceptionNotFound,
				"Requested address out of address-list limits!");
			return HostInet::ANY;
		}

		return aAddressList[a];
	}

	HostResolver::operator const HostInet & () const
	{
		return getAddress();
	}

	// Return the size of the address list
	int HostResolver::getAddressCount() const
	{
		return mAddresses;
	}
};	//! Slib namespace
