/**
@file binary_data.cpp
@brief Implementation of the binary_data class.
*/
#include "./binary_data.hpp"

#include <math.h>

namespace oonet
{
	// Constants
	const binary_data binary_data::nothing = binary_data();
	const size_t binary_data::npos = 0xFFFFFFFF;

	// Mem-block is internal implementation of the real memory holder,
	// binary_data is a shared_ptr around an object of mem-block
	class binary_data::_mem_block
	{
	public:
		byte bt_dummy;	//!< An internal dummy byte when we dont have allocated mem
		size_t sz_mem;	//!< Size of current allocated buffer
		byte * p_mem;	//!< Pointer to our memory

		void _scale_mem(size_t _sz_desired)
		{	size_t sz_new;

			// Check if we fit (Upper boundry) (Lowest boundry no need to calculate for shrinking) (Half of buff)
			if ((_sz_desired <= sz_mem) && ((sz_mem == 1024) || (_sz_desired >= sz_mem/2)))
				return;

			// Calculate new size
			sz_new = ((_sz_desired) / 1024) + 1;
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

		// Default constructor (empty)
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

		// Construct by repeat pattern
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
		if(!p_mem_block.unique())
		{	boost::shared_ptr<_mem_block> new_block(new _mem_block(p_mem_block->p_mem + off_data, s_data));

			p_mem_block = new_block;
			off_data = 0;
		}
	}

	// Simple constructor
	binary_data::binary_data()
		:p_mem_block(new _mem_block()),
		off_data(0),
		s_data(0)
	{
	}

	binary_data::binary_data(const binary_data & r)
		:p_mem_block(r.p_mem_block),
		off_data(r.off_data),
		s_data(r.s_data)
	{
	}

	// Constructor from a byte replication
	binary_data::binary_data(const_reference bt_repeated, size_type s_times)
		:p_mem_block(new _mem_block(bt_repeated, s_times)),
		off_data(0),
		s_data(s_times)
	{
	}

	// Construct from cmem_ref
	binary_data::binary_data(const cmem_ref & _ref)
		:p_mem_block(new _mem_block(_ref.mem_ptr(), _ref.mem_size())),
		off_data(0),
		s_data(_ref.mem_size())
	{}

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

	binary_data::iterator binary_data::begin()
	{	return p_mem_block->p_mem + off_data;	}
	
	binary_data::const_iterator binary_data::begin() const
	{	return p_mem_block->p_mem + off_data;	}
	
	binary_data::iterator binary_data::end()
	{	return p_mem_block->p_mem + off_data + s_data;	}

	binary_data::const_iterator binary_data::end() const
	{	return p_mem_block->p_mem + off_data + s_data;	}
		
		
	// Access element operation
	binary_data::const_reference binary_data::operator[](size_type offset) const throw()
	{	return p_mem_block->p_mem[off_data + offset];	}

	binary_data::reference binary_data::operator[](size_type offset) throw()
	{	return p_mem_block->p_mem[off_data + offset];	}

	binary_data::const_reference binary_data::at(size_type offset) const
	{	if (offset > s_data)
			throw std::out_of_range("binary_data::at(off) has invalid offset");
		return p_mem_block->p_mem[off_data + offset];
	}

	binary_data::reference binary_data::at(size_type offset)
	{	if (offset > s_data)
			throw std::out_of_range("binary_data::at(off) has invalid offset");
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

	binary_data binary_data::operator+(const cmem_ref &r) const
	{
		// Create a temp
		binary_data temp = *this;

		// Add the right assignment
		temp +=r;

		// return the result
		return temp;
	}
	
	// Push action
	binary_data & binary_data::operator+=(const binary_data &r)
	{
		_assure_local_copy();

		// move data at the begining
		memmove(p_mem_block->p_mem + off_data, p_mem_block->p_mem, s_data);
		off_data = 0;

		// Scale memory to fit new data
		p_mem_block->_scale_mem(s_data + r.s_data);

		// Copy new data at the end
		memcpy(p_mem_block->p_mem + s_data, r.c_array(), r.s_data);

		// Add size
		s_data += r.s_data;

		return *this;
	}

	binary_data & binary_data::operator+=(const cmem_ref &r)
	{
		_assure_local_copy();

		// move data at the begining
		memmove(p_mem_block->p_mem + off_data, p_mem_block->p_mem, s_data);
		off_data = 0;

		// Scale memory to fit new data
		p_mem_block->_scale_mem(s_data + r.mem_size());

		// Copy new data at the end
		memcpy(p_mem_block->p_mem + s_data, r.mem_ptr(), r.mem_size());

		// Add size
		s_data += r.mem_size();

		return *this;
	}
	
	// Opposite comparison
	bool binary_data::operator!=(const binary_data &r) const throw()
	{   return  (! operator==(r));    }

	// Comparison action
	bool binary_data::operator==(const binary_data &r) const throw()
	{
		// Check sizes
		if (s_data != r.s_data)
			return false;

		// Skip zero size
		if (s_data == 0) return true;

		// Compare data
		if (0 != memcmp(c_array(), r.c_array(), s_data))
			return false;

		// Else everything is ok
		return true;
	}

	bool binary_data::operator<(const binary_data & r) const throw()
	{	size_t min_len = (s_data < r.s_data)?s_data:r.s_data;

		int res = memcmp(p_mem_block->p_mem + off_data,
			r.p_mem_block->p_mem + r.off_data, min_len);

		if (res < 0)
			return true;
		// In case equal string till now... bigger is that with more characters
		else if ((res == 0) && (r.s_data > min_len))
			return true;

		return false;
	}

	// Get Ansi String object
	string binary_data::to_string() const
	{
		return string((char *)c_array(), s_data);
	}

	// Get Winde String object
	wstring binary_data::to_wstring() const
	{	// Calculate size
		float wstring_size = (float)s_data;
		wstring_size /= sizeof(wchar_t);
		wstring_size = floor(wstring_size);
		return wstring((wchar_t *)c_array(), (wstring::size_type)wstring_size);
	}

	// Get starting message until that size
	binary_data binary_data::get_until(const size_type & offset) const throw()
	{
		// If requested is more than available, then return all data
		if (offset > s_data)
			return *this;

		// Create a shallow copy and parametrize it
		binary_data shallow_copy(*this);
		shallow_copy.s_data = offset;
		return shallow_copy;
	}

	// Get the rest of message from a specific offset
	binary_data binary_data::get_from(const size_type & offset) const throw()
	{
		// If requested is more than available, then return empty
		if (offset > s_data)
			return nothing;

		// Create a shallow copy and parametrize it
		binary_data shallow_copy(*this);
		shallow_copy.off_data += offset;
		shallow_copy.s_data -= offset;

		return shallow_copy;
	}

	// Slice data from a point, till some size
	binary_data binary_data::sub_data(size_type offset, size_type sz) const throw()
	{
		// If requested size is more than available return until the end from the
		// desired offset
		if ((sz == binary_data::npos) || (offset + sz > s_data))
			return get_from(offset);

		// Create a shallow copy and parametrize it
		binary_data shallow_copy(*this);
		shallow_copy.off_data += offset;
		shallow_copy.s_data = sz;

		return shallow_copy;
	}
	
	// Find a pattern in the data block
	binary_data::size_type binary_data::find(const cmem_ref & pattern, size_type offset) const
	{	const byte * p, * p_end;
		const byte * p_local_data = p_mem_block->p_mem + off_data;
		byte first_ch;	// First character that we search

		// Check if there are data
		if (pattern.mem_size() == 0)
			OONET_THROW_EXCEPTION(ExceptionWrongArgument,
			"Pattern is empty! Cannot search for something that does not exists");

        // Check if data fits in search
        if (pattern.mem_size() > s_data)
            return npos;

		// Check if offset is outside isze
		if (offset >= s_data)
			return npos;

		// Initialize values
		p_end = p_local_data + s_data - pattern.mem_size() + 1;
		first_ch = *pattern.mem_ptr();

		// Search for pattern - general optimized (The class is general, so we cant optimize it more specificly)
		p = p_local_data + offset;
		while((p =(byte *) memchr(p, first_ch, p_end - p)))
		{
			if (0 == memcmp(p, pattern.mem_ptr(), pattern.mem_size()) )
				return (p - p_local_data);
			p++;
		}

		// Not found
		return npos;
	}

	// Clear
	void binary_data::clear()
	{	s_data = 0;		}

	const binary_data::pointer binary_data::c_array() const throw()
	{   return p_mem_block->p_mem + off_data;   }

	binary_data::pointer binary_data::c_array() throw()
	{   return p_mem_block->p_mem + off_data;   }

	const byte * binary_data::mem_ptr() const
	{	return p_mem_block->p_mem + off_data;	}
	
	byte * binary_data::mem_ptr()
	{	return p_mem_block->p_mem + off_data;	}
	
};	// !oonet namespace
