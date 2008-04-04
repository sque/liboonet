/**
@file binary_data.cpp
@brief Implementation of the binary_data class.
*/
#include "./binary_data.hpp"

#include <math.h>

namespace oonet
{
	///////////////////////////////////////////////
	// Constants
	const binary_data binary_data::EMPTY = binary_data();
	const size_t binary_data::npos = 0xFFFFFFFF;

	// Allocates space to fit specific amount
	void binary_data::_scale_mem(size_t MemBlock, bool)
	{	size_t sz_new;

		// Check if we fit (Upper boundry) (Lowest boundry no need to calculate for shrinking) (Half of buff)
		if ((MemBlock <= s_buff) && ((s_buff == 1024) || (MemBlock >= s_buff/2)))
			return;

		// Calculate new size
		sz_new = ((MemBlock) / 1024) + 1;
		sz_new *= 1024;

		// Allocate mem
		byte * p_temp;   // Temporary pointer
		try
		{
			if (p_data != &bt_dummy)
				// Reallocate
				p_temp = (byte *)realloc(p_data, sz_new);
			else
				// Allocate
				p_temp = new byte[sz_new];
			p_data = p_temp;
		}catch(std::bad_alloc)
		{	p_temp = NULL;	}

		// In any case check it... (realloc doesn't throw exceptions)
		if (p_temp == NULL)
			// Throw our's exception
			OONET_THROW_EXCEPTION(ExceptionBadAllocation, "Cannot allocate memory for binary_data");


		// Save new size of buffer
		s_buff = sz_new;

		// Return pointer
		return;
	}


	// Simple constructor
	binary_data::binary_data():
        s_buff(0),
		p_data(&bt_dummy),
		s_data(0)
	{
	}

	// Copy constuctor
	binary_data::binary_data(const binary_data &r):
		s_buff(0),
		p_data(&bt_dummy)
	{
		// Scale memmory to fit new data
		_scale_mem(r.s_data);

		// Copy new ones
		s_data = r.s_data;
		memcpy(p_data, r.p_data, s_data);
	}

	//Construtor from binary pointer
	binary_data::binary_data(const void * _p_data, size_t _s_data) throw(Exception):
		s_buff(0),
		p_data(&bt_dummy)
	{
		OONET_ASSERT(_p_data != NULL);

		// Scale memory to fit data
		_scale_mem(_s_data);
		s_data = _s_data;

		// Copy data
		memcpy(p_data, _p_data, _s_data);

	}

	// Constructor from a single byte
	binary_data::binary_data(const byte b):
		s_buff(0),
		p_data(&bt_dummy)
	{
		// Calculate space
		s_data = sizeof(byte);

		// Allocate space
		_scale_mem(s_data);

		// Copy data
		*p_data = b;
	}

	// Constructor from a byte replication
	binary_data::binary_data(const byte bt_repeated, size_t s_times) throw(Exception):
		s_buff(0),
		p_data(&bt_dummy)
	{
		// Scale memory to fit new data
		_scale_mem(s_times);
		s_data = s_times;

		// Fill data with a byte
		memset(p_data , bt_repeated, s_data);
	}

	// Constructor from Ansi String
	binary_data::binary_data(const string & str) throw(Exception):
		s_buff(0),
		p_data(&bt_dummy)
	{
		// Count data and scale buffer
		s_data = str.size() * sizeof(string::value_type);
		_scale_mem(s_data);

		// Copy data
		memcpy(p_data, str.c_str(), s_data);
	}

	// Constructor from Unicode String
	binary_data::binary_data(const wstring & str) throw(Exception):
		s_buff(0),
		p_data(&bt_dummy)
	{
		// Count data and scale buffer
		s_data = str.size() * sizeof(wstring::value_type);
		_scale_mem(s_data);

		// Copy data
		memcpy(p_data, str.c_str(), s_data);
	}

	// Destructor
	binary_data::~binary_data()
	{
		// Free allocated space
		if (p_data != &bt_dummy)
			delete [] p_data;
	}

	// Copy action
	binary_data &binary_data::operator=(const binary_data &r) throw(Exception)
	{
		// Scale memmory
		_scale_mem(r.s_data);

		// Copy data from the right operand
		s_data = r.s_data;
		memcpy(p_data, r.p_data, s_data);
		return *this;
	}

	bool binary_data::operator!=(const binary_data &r) const
	{   return  (! ((*this) == r));    }

	// Access elemnt operation
	byte binary_data::operator[](size_t offset) const throw(Exception)
	{
		if (offset > s_data)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");
		return p_data[offset];
	}
	// Add action
	binary_data binary_data::operator+(const binary_data &r) const throw(Exception)
	{
		// Create a temp
		binary_data temp = *this;

		// Add the right assignment
		temp +=r;

		// return the result
		return temp;
	}

	// Add action (one byte)
	binary_data binary_data::operator+(const byte &r)const throw(Exception)
	{
		// Create a temp
		binary_data temp = *this;

		// Add the right assignment
		temp += r;

		// return result
		return temp;
	}

	// Push action
	binary_data & binary_data::operator+=(const binary_data &r) throw(Exception)
	{
		// Scale memory to fit all data
		_scale_mem(s_data + r.s_data);

		// Copy new data at the end
		memcpy(p_data + s_data, r.p_data, r.s_data);

		// Add size
		s_data += r.s_data;

		return *this;
	}

	// Push action (one byte)
	binary_data & binary_data::operator+=(const byte &r) throw(Exception)
	{
		// Scale memory to fit all data
		_scale_mem(s_data + 1);

		// Add byte at end of buffer
		*(p_data + s_data) = r;

		// Increase buffer
		s_data ++;

		return (*this);
	}

	// Comparison action
	bool binary_data::operator==(const binary_data &r) const
	{
		// Check sizes
		if (s_data != r.s_data)
			return false;

		// Compare data
		if (0 != memcmp(p_data, r.p_data, s_data))
			return false;

		// Else everything is ok
		return true;
	}


	// Get Ansi String object
	string binary_data::to_string() const
	{
		return string((char *)p_data, s_data);
	}

	// Get Winde String object
	wstring binary_data::to_wstring() const
	{	// Calculate size
		float wstring_size = (float)s_data;
		wstring_size /= sizeof(wchar_t);
		wstring_size = floor(wstring_size);
		return wstring((wchar_t *)p_data, (wstring::size_type)wstring_size);
	}

	// Get starting packet until that size
	binary_data binary_data::get_until(const size_t & offset) const throw(ExceptionNotFound)
	{
		// If requested is more than available, then throw
		if (offset > s_data)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");

		return binary_data(p_data, offset);
	}

	// Get the rest of packet from a specific offset
	binary_data binary_data::get_from(const size_t & offset) const throw(ExceptionNotFound)
	{
		// If requested is more than available, then return empty
		if (offset > s_data)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");

		return binary_data(p_data + offset, s_data - offset);
	}

	// Slice data from a point, till some size
	binary_data binary_data::slice(size_t offset, size_t sz) const
	{
		if (offset + sz > s_data)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset and size can't work in the size of this data");

		return binary_data(p_data + offset, sz);
	}
	// Find a pattern in the data block
	size_t binary_data::find(const binary_data & pattern) const
	{	byte  * p, * pEnd, firstChar;

		// Check if there are data
		if (pattern.s_data == 0)
			OONET_THROW_EXCEPTION(ExceptionWrongArgument, "Pattern is empty! Cannot search for something that does not exists");

        // Check if data fits in search
        if (pattern.s_data > s_data)
            return npos;

		// Initialize values
		pEnd = p_data + s_data - pattern.s_data + 1;
		firstChar = *pattern.p_data;

		// Search for pattern - general optimized (The class is general, so we cant optimize it more specificly)
		p = p_data;
		while((p =(byte *) memchr(p, firstChar, pEnd - p)))
		{
			if (0 == memcmp(p, pattern.p_data, pattern.s_data) )
				return (p - p_data);
			p++;
		}

		// Not found
		return npos;
	}

	// Clear
	void binary_data::clear()
	{
		// Scale the memory to zero size
		_scale_mem(0);

		// Empty data
		s_data = 0;
	}
};	// !oonet namespace
