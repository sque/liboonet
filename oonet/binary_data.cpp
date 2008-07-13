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
	struct binary_data::_mem_block
	{
		byte bt_dummy;		//!< An internal dummy byte when we dont have allocated mem
		size_t block_size;	//!< Size of current allocated buffer
		byte * block_ptr;	//!< Pointer to our memory

		void _scale_mem(size_t _sz_desired)
		{	size_t sz_new;

			// Check if we fit (Upper boundry) (Lowest boundry no need to calculate for shrinking) (Half of buff)
			if ((_sz_desired <= block_size) && ((block_size == 1024) || (_sz_desired >= block_size/2)))
				return;

			// Calculate new size
			sz_new = ((_sz_desired) / 1024) + 1;
			sz_new *= 1024;

			// Allocate mem
			byte * p_temp;   // Temporary pointer
			try
			{
				if (block_ptr != &bt_dummy)
					// Reallocate
					p_temp = (byte *)realloc(block_ptr, sz_new);
				else
					// Allocate
					p_temp = (byte*)malloc(sizeof(byte) * sz_new);
				block_ptr = p_temp;
			}catch(std::bad_alloc)
			{	p_temp = NULL;	}

			// In any case check it... (realloc doesn't throw exceptions)
			if (p_temp == NULL)
				// Throw our's exception
				OONET_THROW_EXCEPTION(ExceptionBadAllocation, "Cannot allocate memory for binary_data");

			// Save new size of buffer
			block_size = sz_new;

			// Return pointer
			return;
		}

		// Default constructor (empty)
		inline _mem_block()
			: block_size(0), block_ptr(&bt_dummy) {}

		// Construct, allocate and copy data
		inline _mem_block(const void * _ptr, size_t _size)
			:block_size(0), block_ptr(&bt_dummy)
		{	OONET_ASSERT(_ptr != NULL);
			_scale_mem(_size);
			memcpy(block_ptr, _ptr, _size);
		}
		
		// Construct and reserve space
		inline _mem_block(size_t reserved_space)
			:block_size(0),
			block_ptr(&bt_dummy)
		{
			// Scale memory to fit new data
			_scale_mem(reserved_space);
		}
		
		// Destructor
		inline ~_mem_block()
		{
			// Free allocated space
			if (block_ptr != &bt_dummy) free(block_ptr);
		}
	};


	// Create real copy if needed
	void binary_data::assure_unique_copy()
	{
		// If we are not the only one create a hard copy
		if(!p_mem_block.unique())
		{	// Create a copy of only active data
			boost::shared_ptr<_mem_block> p_tmp_new_block(new _mem_block(real_ptr, real_size));
			p_mem_block.swap(p_tmp_new_block);
			real_ptr = p_mem_block->block_ptr;
		}
	}

	// Simple constructor
	binary_data::binary_data()
		:p_mem_block(new _mem_block()),
		real_ptr(p_mem_block->block_ptr),
		real_size(0)
	{
	}

	binary_data::binary_data(const binary_data & r)
		:p_mem_block(r.p_mem_block),
		real_ptr(r.real_ptr),
		real_size(r.real_size)
	{
	}

	// Reserve unitialized memory
	binary_data::binary_data(size_type startup_size)
		:p_mem_block(new _mem_block(startup_size)),
		real_ptr(p_mem_block->block_ptr),
		real_size(startup_size)
	{	}
	
	// Range constructor
	binary_data::binary_data(const_iterator beg, const_iterator end)
		:p_mem_block(new _mem_block(beg, end - beg)),
		real_ptr(p_mem_block->block_ptr),
		real_size(end - beg)
	{}
	
	// Reserve and initialize memory with default value
	binary_data::binary_data(size_type startup_size, const_reference def_value)
		:p_mem_block(new _mem_block(startup_size)),
		real_ptr(p_mem_block->block_ptr),
		real_size(startup_size)
	{	memset(real_ptr, def_value, startup_size);	}


	// Construct from cmem_ref
	binary_data::binary_data(const cmem_ref & _ref)
		:p_mem_block(new _mem_block(_ref.mem_ptr(), _ref.mem_size())),
		real_ptr(p_mem_block->block_ptr),
		real_size(_ref.mem_size())
	{}

	// Destructor
	binary_data::~binary_data()
	{}

	binary_data & binary_data::operator=(const binary_data & r)
	{
		p_mem_block = r.p_mem_block;
		real_ptr = r.real_ptr;
		real_size = r.real_size;

		return *this;
	}
	
	binary_data & binary_data::operator=(const cmem_ref & ref)
	{
		if(!p_mem_block.unique())
		{	boost::shared_ptr<_mem_block> new_block(new _mem_block(ref.mem_ptr(), ref.mem_size()));

			p_mem_block = new_block;
			real_ptr = p_mem_block->block_ptr;
			real_size = ref.mem_size();
		}
		else if (ref.mem_size() == 0)
		{
			real_ptr = p_mem_block->block_ptr;
			real_size = 0;
		}
		else
		{
			p_mem_block->_scale_mem(ref.mem_size());
			memcpy(p_mem_block->block_ptr, ref.mem_ptr(), ref.mem_size());
			real_ptr = p_mem_block->block_ptr;
			real_size = ref.mem_size();
		}
		return *this;
	}
		
	// Access element operation
	binary_data::const_reference binary_data::at(size_type offset) const
	{	if (offset > real_size)
			throw std::out_of_range("binary_data::at(off) has invalid offset");
		return real_ptr[offset];
	}

	binary_data::reference binary_data::at(size_type offset)
	{	if (offset > real_size)
			throw std::out_of_range("binary_data::at(off) has invalid offset");
		return real_ptr[offset];
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
	
	binary_data binary_data::operator+(const binary_data &r) const
	{
		// Create a temp
		binary_data temp = *this;

		// Add the right assignment
		temp +=r;

		// return the result
		return temp;
	}
	
	binary_data & binary_data::operator+=(const cmem_ref &r)
	{
		assure_unique_copy();

		// move data at the begining
		memmove(p_mem_block->block_ptr, real_ptr, real_ptr - p_mem_block->block_ptr);
		real_ptr = p_mem_block->block_ptr;

		// Scale memory to fit new data
		p_mem_block->_scale_mem(real_size + r.mem_size());
		real_ptr = p_mem_block->block_ptr;

		// Copy new data at the end
		memcpy(p_mem_block->block_ptr + real_size, r.mem_ptr(), r.mem_size());

		// Add size
		real_size += r.mem_size();

		return *this;
	}
	
	binary_data & binary_data::operator+=(const binary_data &r)
	{
		assure_unique_copy();

		// move data at the begining
		memmove(p_mem_block->block_ptr, real_ptr, real_ptr - p_mem_block->block_ptr);
		real_ptr = p_mem_block->block_ptr;

		// Scale memory to fit new data
		p_mem_block->_scale_mem(real_size + r.real_size);
		real_ptr = p_mem_block->block_ptr;

		// Copy new data at the end
		memcpy(p_mem_block->block_ptr + real_size, r.real_ptr, r.real_size);

		// Add size
		real_size += r.real_size;

		return *this;
	}
	
	// Opposite comparison
	bool binary_data::operator!=(const binary_data &r) const throw()
	{   return  (! operator==(r));    }

	// Comparison action
	bool binary_data::operator==(const binary_data &r) const throw()
	{
		// Check sizes
		if (real_size != r.real_size)
			return false;

		// Skip zero size
		if (real_size == 0) return true;

		// Compare data
		if (0 != memcmp(real_ptr, r.real_ptr, real_size))
			return false;

		// Else everything is ok
		return true;
	}

	bool binary_data::operator<(const binary_data & r) const throw()
	{	size_t min_len = (real_size < r.real_size)?real_size:r.real_size;

		int res = memcmp(real_ptr, r.real_ptr, min_len);

		if (res < 0)
			return true;
		// In case equal string till now... bigger is that with more characters
		else if ((res == 0) && (r.real_size > min_len))
			return true;

		return false;
	}
	
	bool binary_data::operator<=(const binary_data & r) const throw()
	{	size_t min_len = (real_size < r.real_size)?real_size:r.real_size;

		int res = memcmp(real_ptr, r.real_ptr, min_len);

		if (res < 0)
			return true;
		// In case equal string till now... bigger is that with more characters
		else if ((res == 0) && (r.real_size >= real_size))
			return true;

		return false;
	}
	
	bool binary_data::operator>(const binary_data & r) const throw()
	{	size_t min_len = (real_size < r.real_size)?real_size:r.real_size;

		int res = memcmp(real_ptr, r.real_ptr, min_len);

		if (res > 0)
			return true;
		// In case equal string till now... bigger is that with more characters
		else if ((res == 0) && (real_size > min_len))
			return true;

		return false;
	}

	bool binary_data::operator>=(const binary_data & r) const throw()
	{	size_t min_len = (real_size < r.real_size)?real_size:r.real_size;

		int res = memcmp(real_ptr, r.real_ptr, min_len);

		if (res > 0)
			return true;
		// In case equal string till now... bigger is that with more characters
		else if ((res == 0) && (real_size >= r.real_size))
			return true;

		return false;
	}
	
	// Get Ansi String object
	string binary_data::to_string() const
	{
		return string((char *)c_array(), real_size);
	}

	// Get Winde String object
	wstring binary_data::to_wstring() const
	{	// Calculate size
		float wstring_size = (float)real_size;
		wstring_size /= sizeof(wchar_t);
		wstring_size = floor(wstring_size);
		return wstring((wchar_t *)real_ptr, (wstring::size_type)wstring_size);
	}

	// Get starting message until that size
	binary_data binary_data::get_until(const size_type & size) const throw()
	{
		// If requested is more than available, then return all data
		if (size > real_size)
			return *this;

		// Create a shallow copy and parametrize it
		binary_data shallow_copy(*this);
		shallow_copy.real_size = size;
		return shallow_copy;
	}

	// Get the rest of message from a specific offset
	binary_data binary_data::get_from(const size_type & offset) const throw()
	{
		// If requested is more than available, then return empty
		if (offset > real_size)
			return nothing;

		// Create a shallow copy and parametrize it
		binary_data shallow_copy(*this);
		shallow_copy.real_ptr += offset;
		shallow_copy.real_size -= offset;

		return shallow_copy;
	}

	// Slice data from a point, till some size
	binary_data binary_data::sub_data(size_type offset, size_type sz) const throw()
	{
		// If requested size is more than available return until the end from the
		// desired offset
		if ((sz == binary_data::npos) || (offset + sz > real_size))
			return get_from(offset);

		// Create a shallow copy and parametrize it
		binary_data shallow_copy(*this);
		shallow_copy.real_ptr += offset;
		shallow_copy.real_size = sz;

		return shallow_copy;
	}
	
	// Find a pattern in the data block
	binary_data::size_type binary_data::find(const cmem_ref & pattern, size_type offset) const
	{	const byte * p, * p_end;
		byte first_ch;	// First character that we search

		// Check if there are data
		if (pattern.mem_size() == 0)
			OONET_THROW_EXCEPTION(ExceptionWrongArgument,
			"Pattern is empty! Cannot search for something that does not exists");

        // Check if data fits in search
        if (pattern.mem_size() > real_size)
            return npos;

		// Check if offset is outside isze
		if (offset >= real_size)
			return npos;

		// Initialize values
		p_end = real_ptr + real_size - pattern.mem_size() + 1;
		first_ch = *pattern.mem_ptr();

		// Search for pattern - general optimized (The class is general, so we cant optimize it more specificly)
		p = real_ptr + offset;
		while((p =(byte *) memchr(p, first_ch, p_end - p)))
		{
			if (0 == memcmp(p, pattern.mem_ptr(), pattern.mem_size()) )
				return (p - real_ptr);
			p++;
		}

		// Not found
		return npos;
	}
	
	void binary_data::swap(binary_data & r)
	{	p_mem_block.swap(r.p_mem_block);
		pointer tmp_ptr = real_ptr;
		size_type tmp_size = real_size;
		
		real_ptr = r.real_ptr;
		real_size = r.real_size;
		r.real_ptr = tmp_ptr;
		r.real_size = tmp_size;
	}
	
};	// !oonet namespace
