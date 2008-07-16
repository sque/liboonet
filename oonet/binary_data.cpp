/**
@file binary_data.cpp
@brief Implementation of the binary_data class.
*/
#include "./binary_data.hpp"

#define SMALLEST_MEMBLOCK 32
namespace oonet
{
	// Constants
	const binary_data binary_data::nothing = binary_data();
	const size_t binary_data::npos = 0xFFFFFFFF;

    byte * safe_malloc(size_t _size)
    {   byte * tmp_ptr = (byte *)malloc(_size);
        if (tmp_ptr == NULL)
            throw std::bad_alloc();
        return tmp_ptr;
    }
    
    byte * safe_realloc(byte * _ptr, size_t _size)
    {   byte * tmp_ptr = (byte *)realloc(_ptr, _size);
        if (tmp_ptr == NULL)
            throw std::bad_alloc();
        return tmp_ptr;
    }
    
	// Mem-block is internal implementation of the real memory holder,
	// binary_data is a shared_ptr around an object of mem-block
	struct binary_data::_mem_block
	{
    private:
        // non copyable
        _mem_block(const _mem_block & r);
        _mem_block & operator=(const _mem_block & r);

    public:
		size_t block_size;	//!< Size of current allocated buffer
		byte * block_ptr;	//!< Pointer to our memory
        
        inline bool has_allocated()
        {   return (block_ptr != NULL);    }

        inline void dispose()
        {   if (block_ptr) free(block_ptr);
            block_ptr = NULL;
            block_size = 0;
        }

		inline byte * allocate(size_t _size)
		{	// Deallocate previous block
			dispose();
			
			// Allocate
            block_size = _size;
            return block_ptr = safe_malloc(_size);

		}
		
		// Allocate and copy (it is safe from allocating from the same memblock)
		inline byte * allocate(size_t _alloc_size, const void * _ptr, size_t _size)
		{	// Create a temporary buffer
            byte * tmp_ptr = safe_malloc(_alloc_size);
            memcpy(tmp_ptr, _ptr, _size);
			
            // Dispose the previous
            dispose();
			
            // Save the new
			block_size = _alloc_size;
			return block_ptr = tmp_ptr;
		}
		
        // Resize it and returns a pointer to the starting last used buffer
		byte * scale_to_right(size_t desired_size, size_t left_unused = 0)
		{	size_t double_desired = desired_size * 2;
            // First time allocation allocate desired * 2
            if (!block_ptr)
                return block_ptr = safe_malloc((desired_size > SMALLEST_MEMBLOCK)?double_desired:SMALLEST_MEMBLOCK);
            
			// Check for safe range
            if ((desired_size <= (block_size - left_unused)) && // Safe range is always <= block_size - left_unused
                ((desired_size > block_size /4) || (desired_size == SMALLEST_MEMBLOCK)))
                return block_ptr + left_unused; //No change

            // Shrink/Grow to double size of requested data
            if ((left_unused == 0)
                    || (left_unused <= desired_size))
            {
                block_ptr = safe_realloc(block_ptr, double_desired);
                block_size = double_desired;
                return block_ptr + left_unused;
            }
            
            // Full malloc and copy previous data padded to left
            allocate(double_desired, block_ptr + left_unused, block_size - left_unused);
            
			// Return pointer
			return block_ptr;
		}
        
        // Resize it and returns a pointer to the starting last used buffer
		byte * scale_to_left(size_t desired_size, byte * p_start_data, size_t used_size)
		{	size_t double_desired = desired_size * 2;
            size_t left_unused = p_start_data - block_ptr;
                        
            // First time allocation allocate desired * 2
            if (!block_ptr)
                return block_ptr = safe_malloc((desired_size > SMALLEST_MEMBLOCK)?double_desired:SMALLEST_MEMBLOCK);
            
            // Safe range
            if ((desired_size - used_size) <= left_unused)
                return block_ptr + left_unused - (desired_size - used_size);

            // Allocate temporary space
            byte * tmp_ptr = safe_malloc(double_desired);
            memcpy(tmp_ptr + double_desired - used_size, p_start_data, used_size);
            
            // dispose old memory
            dispose();
            
            block_ptr = tmp_ptr;
            block_size = double_desired;            
            
			// Return pointer
			return block_ptr + desired_size;
		}

		// Default constructor (empty)
		inline _mem_block()
			: block_size(0), block_ptr(NULL)
        {}

		// Construct, allocate and copy data
		inline _mem_block(const void * _ptr, size_t _size)
			:block_size(_size * 2),
            block_ptr(safe_malloc(_size * 2))
		{	OONET_ASSERT(_ptr != NULL);
			memcpy(block_ptr, _ptr, _size);
		}
		
		// Construct and reserve space
		inline _mem_block(size_t reserved_space)
			:block_size(reserved_space),
            block_ptr(safe_malloc(reserved_space))
		{}
		
		// Destructor
		inline ~_mem_block()
		{	// Free allocated space
			dispose();
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
	{   }

	// Copy constructor
	binary_data::binary_data(const binary_data & r)
		:p_mem_block(r.p_mem_block),
		real_ptr(r.real_ptr),
		real_size(r.real_size)
	{   }

	// Reserve unitialized memory
	binary_data::binary_data(size_type startup_size)
		:p_mem_block(new _mem_block(startup_size)),
		real_ptr(p_mem_block->block_ptr),
		real_size(startup_size)
	{   }
	
	// Range constructor
	binary_data::binary_data(const_iterator beg, const_iterator end)
		:p_mem_block(new _mem_block(beg, end - beg)),
		real_ptr(p_mem_block->block_ptr),
		real_size(end - beg)
	{   }
	
	// Reserve and initialize memory with default value
	binary_data::binary_data(size_type startup_size, const_reference def_value)
		:p_mem_block(new _mem_block(startup_size)),
		real_ptr(p_mem_block->block_ptr),
		real_size(startup_size)
	{	memset(real_ptr, def_value, startup_size);    }


	// Construct from cmem_ref
	binary_data::binary_data(const cmem_ref & _ref)
		:p_mem_block(new _mem_block(_ref.mem_ptr(), _ref.mem_size())),
		real_ptr(p_mem_block->block_ptr),
		real_size(_ref.mem_size())
	{   }

	// Assign operator for binary_data (Shallow copy)
	binary_data & binary_data::operator=(const binary_data & r)
	{
		p_mem_block = r.p_mem_block;
		real_ptr = r.real_ptr;
		real_size = r.real_size;

		return *this;
	}

	// Assign operator for memory reference
	binary_data & binary_data::operator=(const cmem_ref & ref)
	{	real_size = ref.mem_size();
	
		// Fast reject equal to zero
		if (real_size == 0)
			return *this;
		
		// Create a unique copy if needed
		if(!p_mem_block.unique())
		{	boost::shared_ptr<_mem_block> p_new_block(new _mem_block(ref.mem_ptr(), ref.mem_size()));
			p_mem_block = p_new_block;
			real_ptr = p_mem_block->block_ptr;
			return *this;
		}
		
		// Scale memory and fit it inside
        real_size = ref.mem_size();
		real_ptr = p_mem_block->scale_to_right(real_size);
        memcpy(real_ptr, ref.mem_ptr(), real_size);
		return *this;
	}
		
	binary_data binary_data::operator+(const cmem_ref &r) const
	{	// Create a temporary copy
		binary_data tmp_storage(real_size + r.mem_size());

		// Concatenate data
		memcpy(tmp_storage.real_ptr, real_ptr, real_size);
		memcpy(tmp_storage.real_ptr + real_size, r.mem_ptr(), r.mem_size());
		
		// return the result
		return tmp_storage;
	}

    void binary_data::append(const cmem_ref & r)
    {   size_type r_size = r.mem_size();
	
		// New buffer from scratch
		if (!p_mem_block.unique())
		{	boost::shared_ptr<_mem_block> p_new_block(new _mem_block(real_size + r_size));
			memcpy(p_new_block->block_ptr, real_ptr, real_size);
            memcpy(p_new_block->block_ptr + real_size, r.mem_ptr(), r_size);
			
			p_mem_block.swap(p_new_block);
			real_ptr = p_mem_block->block_ptr;
			real_size += r_size;
			return;
		}

		real_ptr = p_mem_block->scale_to_right(real_size + r_size, real_ptr - p_mem_block->block_ptr);
   		memcpy(real_ptr + real_size, r.mem_ptr(), r_size);
        real_size += r_size;
    }
    
	void binary_data::append(const binary_data &r)
	{	
		// New buffer from scratch
		if (!p_mem_block.unique())
		{	boost::shared_ptr<_mem_block> p_new_block(new _mem_block(real_size + r.real_size));
			memcpy(p_new_block->block_ptr, real_ptr, real_size);
            memcpy(p_new_block->block_ptr + real_size, r.real_ptr, r.real_size);
			
			p_mem_block.swap(p_new_block);
			real_ptr = p_mem_block->block_ptr;
			real_size += r.real_size;
			return;
		}

		real_ptr = p_mem_block->scale_to_right(real_size +r.real_size, real_ptr - p_mem_block->block_ptr);
   		memcpy(real_ptr + real_size, r.real_ptr, r.real_size);
        real_size += r.real_size;
	}
    
    void binary_data::prepend(const binary_data & l)
    {   // New buffer from scratch
		if (!p_mem_block.unique())
		{	boost::shared_ptr<_mem_block> p_new_block(new _mem_block(real_size + l.real_size));
			memcpy(p_new_block->block_ptr, l.real_ptr, l.real_size);
            memcpy(p_new_block->block_ptr + l.real_size, real_ptr, real_size);            
			
			p_mem_block.swap(p_new_block);
			real_ptr = p_mem_block->block_ptr;
			real_size += l.real_size;
			return;
		}

        real_ptr = p_mem_block->scale_to_left(real_size + l.real_size, real_ptr, real_size);
        memcpy(real_ptr, l.real_ptr, l.real_size);
		real_size += l.real_size;
    }

    void binary_data::prepend(const cmem_ref & l)
    {   size_t l_size = l.mem_size();
        // New buffer from scratch
		if (!p_mem_block.unique())
		{	boost::shared_ptr<_mem_block> p_new_block(new _mem_block(real_size + l_size));
			memcpy(p_new_block->block_ptr, l.mem_ptr(), l_size);
            memcpy(p_new_block->block_ptr + l_size, real_ptr, real_size);            
			
			p_mem_block.swap(p_new_block);
			real_ptr = p_mem_block->block_ptr;
			real_size += l_size;
			return;
		}

        real_ptr = p_mem_block->scale_to_left(real_size + l_size, real_ptr, real_size);
        memcpy(real_ptr, l.mem_ptr(), l_size);
		real_size += l_size;
    }
    
	// Get starting message until that size
	binary_data binary_data::get_until(const size_type & size) const throw()
	{	// If requested is more than available, then return all data
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
