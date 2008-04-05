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

	class binary_data::_mem_block
	{
	public:
		byte bt_dummy;	//!< An internal dummy byte when we dont have allocated mem
		size_t sz_mem;	//!< Size of current allocated buffer
		byte * p_mem;	//!< Pointer to our memory

		void _scale_mem(size_t desired_mem_block)
		{	size_t sz_new;

			// Check if we fit (Upper boundry) (Lowest boundry no need to calculate for shrinking) (Half of buff)
			if ((desired_mem_block <= sz_mem) && ((sz_mem == 1024) || (desired_mem_block >= sz_mem/2)))
				return;

			// Calculate new size
			sz_new = ((desired_mem_block) / 1024) + 1;
			sz_new *= 1024;

			// Allocate mem
			byte * p_temp;   // Temporary pointer
			try
			{
				if (p_mem != &bt_dummy)
					// Reallocate
					p_temp = (byte *)realloc(p_mem, sz_new);
				else
					// Allocate
					p_temp = (byte*)malloc(sizeof(byte) * sz_new);
				p_mem = p_temp;
			}catch(std::bad_alloc)
			{	p_temp = NULL;	}

			// In any case check it... (realloc doesn't throw exceptions)
			if (p_temp == NULL)
				// Throw our's exception
				OONET_THROW_EXCEPTION(ExceptionBadAllocation, "Cannot allocate memory for binary_data");

			// Save new size of buffer
			sz_mem = sz_new;

			// Return pointer
			return;
		}

		// Shift data left "off" bytes
		void shift_data_left(size_t off)
		{
			memmove(p_mem, p_mem+1, sz_mem - off);
		}

		// Default constructor
		_mem_block():
			sz_mem(0),
			p_mem(&bt_dummy)
		{}

		// Construct by data
		_mem_block(const void * _p_data, size_t _s_data)
			:sz_mem(0),
			p_mem(&bt_dummy)
		{
			OONET_ASSERT(_p_data != NULL);

			// Scale memory to fit data
			_scale_mem(_s_data);

			// Copy data
			memcpy(p_mem, _p_data, _s_data);
		}

		_mem_block(const byte bt_repeated, size_t s_times)
			:sz_mem(0),
			p_mem(&bt_dummy)
		{
			// Scale memory to fit new data
			_scale_mem(s_times);

			// Fill data with a byte
			memset(p_mem, bt_repeated, s_times);
		}

		// Destructor
		~_mem_block()
		{
			// Free allocated space
			if (p_mem != &bt_dummy)
				free(p_mem);
		}
	};


	// Create real copy if needed
	void binary_data::_assure_local_copy()
	{
		// If we are not the only one create a hard copy
		if(p_mem_block.use_count() !=1)
		{	boost::shared_ptr<_mem_block> new_block(new _mem_block(p_mem_block->p_mem + off_data, s_data));

			p_mem_block = new_block;
			off_data = 0;
		}
//		else if (off_data != 0)
//		{	//Move data back
//			p_mem_block->shift_data_left(off_data);
//			off_data = 0;
//		}
	}

	// Simple constructor
	binary_data::binary_data()
		:p_mem_block(new _mem_block()),
		off_data(0),
		s_data(0)
	{
	}

	//Construtor from binary pointer
	binary_data::binary_data(const void * _p_data, size_t _s_data)
		:p_mem_block(new _mem_block(_p_data, _s_data)),
		off_data(0),
		s_data(_s_data)
	{
	}

	binary_data::binary_data(const binary_data & r)
		:p_mem_block(r.p_mem_block),
		off_data(r.off_data),
		s_data(r.s_data)
	{
	}

	// Constructor from a single byte
	binary_data::binary_data(const byte b)
		:p_mem_block(new _mem_block(&b, 1)),
		off_data(0),
		s_data(1)
	{
	}

	// Constructor from a byte replication
	binary_data::binary_data(const byte bt_repeated, size_t s_times)
		:p_mem_block(new _mem_block(bt_repeated, s_times)),
		off_data(0),
		s_data(s_times)
	{
	}

	// Constructor from Ansi String
	binary_data::binary_data(const string & str)
		:p_mem_block(new _mem_block(str.c_str(), str.size() * sizeof(string::value_type))),
		off_data(0),
		s_data(str.size() * sizeof(string::value_type))
	{
	}

	// Constructor from Unicode String
	binary_data::binary_data(const wstring & str)
		:p_mem_block(new _mem_block(str.c_str(), str.size() * sizeof(wstring::value_type))),
		off_data(0),
		s_data(str.size() * sizeof(wstring::value_type))
	{
	}

	// Destructor
	binary_data::~binary_data()
	{
	}

	binary_data & binary_data::operator=(const binary_data & r)
	{
		p_mem_block = r.p_mem_block;
		off_data = r.off_data;
		s_data = r.s_data;

		return *this;
	}

	bool binary_data::operator!=(const binary_data &r) const
	{   return  (! ((*this) == r));    }

	// Access elemnt operation
	byte binary_data::operator[](size_t offset) const
	{
		if (offset > s_data)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");
		return p_mem_block->p_mem[off_data + offset];
	}

	// Add action
	binary_data binary_data::operator+(const binary_data &r) const
	{
		// Create a temp
		binary_data temp = *this;

		// Add the right assignment
		temp +=r;

		// return the result
		return temp;
	}

	// Add action (one byte)
	binary_data binary_data::operator+(const byte &r)const
	{
		// Create a temp
		binary_data temp = *this;

		// Add the right assignment
		temp += r;

		// return result
		return temp;
	}

	// Push action
	binary_data & binary_data::operator+=(const binary_data &r)
	{
		_assure_local_copy();

		// Scale memory to fit all data
		p_mem_block->_scale_mem(off_data + s_data + r.s_data);

		// Copy new data at the end
		memcpy(p_mem_block->p_mem + off_data + s_data, r.get_data_ptr(), r.s_data);

		// Add size
		s_data += r.s_data;

		return *this;
	}

	// Push action (one byte)
	binary_data & binary_data::operator+=(const byte &r)
	{
		_assure_local_copy();

		// Scale memory to fit all data
		p_mem_block->_scale_mem(off_data + s_data + 1);

		// Add byte at end of buffer
		*(p_mem_block->p_mem + off_data + s_data) = r;

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
		if (0 != memcmp(get_data_ptr(), r.get_data_ptr(), s_data))
			return false;

		// Else everything is ok
		return true;
	}


	// Get Ansi String object
	string binary_data::to_string() const
	{
		return string((char *)get_data_ptr(), s_data);
	}

	// Get Winde String object
	wstring binary_data::to_wstring() const
	{	// Calculate size
		float wstring_size = (float)s_data;
		wstring_size /= sizeof(wchar_t);
		wstring_size = floor(wstring_size);
		return wstring((wchar_t *)get_data_ptr(), (wstring::size_type)wstring_size);
	}

	// Get starting packet until that size
	binary_data binary_data::get_until(const size_t & offset) const
	{
		// If requested is more than available, then throw
		if (offset > s_data)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");

		// Create a shadow copy and parametrize it
		binary_data shadow_copy(*this);
		shadow_copy.s_data = offset;
		return shadow_copy;
	}

	// Get the rest of packet from a specific offset
	binary_data binary_data::get_from(const size_t & offset) const
	{
		// If requested is more than available, then return empty
		if (offset > s_data)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");

		// Create a shadow copy and parametrize it
		binary_data shadow_copy(*this);
		shadow_copy.off_data += offset;
		shadow_copy.s_data -= offset;

		return shadow_copy;
	}

	// Slice data from a point, till some size
	binary_data binary_data::slice(size_t offset, size_t sz) const
	{
		if (offset + sz > s_data)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset and size can't work in the size of this data");

		// Create a shadow copy and parametrize it
		binary_data shadow_copy(*this);
		shadow_copy.off_data += offset;
		shadow_copy.s_data = sz;

		return shadow_copy;
	}
	// Find a pattern in the data block
	size_t binary_data::find(const binary_data & pattern) const
	{	const byte * p, * p_end;
		const byte * p_local_data = p_mem_block->p_mem + off_data;
		const byte * p_pattern_data = pattern.p_mem_block->p_mem + pattern.off_data;
		byte first_ch;	// First character that we search

		// Check if there are data
		if (pattern.s_data == 0)
			OONET_THROW_EXCEPTION(ExceptionWrongArgument,
			"Pattern is empty! Cannot search for something that does not exists");

        // Check if data fits in search
        if (pattern.s_data > s_data)
            return npos;

		// Initialize values
		p_end = p_local_data + s_data - pattern.s_data + 1;
		first_ch = *p_pattern_data;

		// Search for pattern - general optimized (The class is general, so we cant optimize it more specificly)
		p = p_local_data;
		while((p =(byte *) memchr(p, first_ch, p_end - p)))
		{
			if (0 == memcmp(p, p_pattern_data, pattern.s_data) )
				return (p - p_local_data);
			p++;
		}

		// Not found
		return npos;
	}

	// Clear
	void binary_data::clear()
	{	_assure_local_copy();

		// Scale the memory to zero size
		p_mem_block->_scale_mem(0);

		// Empty data
		off_data = 0;
		s_data = 0;
	}

	const byte * binary_data::get_data_ptr() const
	{   return p_mem_block->p_mem + off_data;   }
};	// !oonet namespace
