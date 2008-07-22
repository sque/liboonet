#ifndef OONET_BINARY_DATA_HPP_INCLUDED
#define OONET_BINARY_DATA_HPP_INCLUDED

#include "./oonet.hpp"
#include "./mem_ref.hpp"
#include <vector>
#include <math.h>
#include <boost/shared_ptr.hpp>
#include <algorithm>
namespace oonet
{
    //! A "container" object of binary_data
    /**
        binary_data support CoW and it is designed to be efficient
        with large data. It can work with stdlib algorithms that require
        forward and reverse iterator support.
    */
	class binary_data
	{
	public:
		//! @name "CONTAINER" Concept implementation
		//! @{
		typedef byte value_type;
		typedef value_type * iterator;
		typedef const value_type * const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type * pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		//! @}s
	private:
		// Internal implementation
		class _mem_block;
		boost::shared_ptr<_mem_block> p_mem_block;
		pointer real_ptr;		// Pointer to real data on the current memory block
		size_type real_size;	// Size of the real data on the internal memory block

	public:

        //! Construct from a memory reference
        /**
            It will allocate the needed space and copy
            data inside the the created object.
        @param _ref A cmem_ref to a memory block
        */
		binary_data(const cmem_ref & _ref);

		//! Construct and allocate some memory space
		/**
            The constructed object will be of "startup_size" size
            but the allocated memory will have garbage.
        @param startup_size The size of memory to allocate at construction time
        */
		explicit binary_data(size_type startup_size);

		//! Allocate and initialize memory with default value
		/**
            It will create an object of the requested size
            and will set all bytes to the requested value.
        @param startup_size The size of memory that binary_data will be.
        @param def_value The default value of all bytes in the object.
        */
		binary_data(size_type startup_size, const_reference def_value);

		//! Range copy constructor
		/**
            It follows the stdlib guidelines of range constructor.
            It allocates memory and copies all the elements found
            form "beg" to "end"
        @param beg The iterator to the first element that will
            be copied.
        @param end The iterator after the last element that will
            be copied internally.
        */
		binary_data(const_iterator beg, const_iterator end);
		binary_data & operator=(const cmem_ref & ref);

        //! Empty constructor
        /**
            Constructs an empty binary_data object of zero size.
            No memory allocation is done at the construction of
            binary_data object.
        */
        binary_data();

		//! @name "Container" concept implementation
		//! @{
		binary_data(const binary_data & r);
		binary_data & operator=(const binary_data & r);
		inline ~binary_data(){}
		inline iterator begin(){	return real_ptr;	}
		inline const_iterator begin() const{	return real_ptr;	}
		inline iterator end() { return real_ptr + real_size;	}
		inline const_iterator end() const {	return real_ptr + real_size;	}
		inline reverse_iterator rbegin() {	return reverse_iterator(end());	}
		inline const_reverse_iterator rbegin() const {	return const_reverse_iterator(end());	}
		inline reverse_iterator rend() { return reverse_iterator(begin());	}
		inline const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
		inline size_type size() const throw(){   return real_size;   }
		inline size_type max_size() const throw(){	return real_size;	}
		inline bool empty() const throw(){	return (real_size == 0);	}
		inline void clear(){	real_size = 0;		}
        void prepend(const binary_data & l);
        void prepend(const cmem_ref & l);
        void append(const binary_data & r);
        void append(const cmem_ref & r);
		void swap(binary_data & r);
        //! @}

        //! @name "ElementAccess" Concept implementation
        //! @{

        //! Direct element access with NO range check
		inline const_reference operator[](size_type offset) const throw() { return real_ptr[offset];	}
		//! Direct element access with NO range check
		inline reference operator[](size_type offset) throw() { return real_ptr[offset];	}
		//! Direct element access WITH range check
		inline const_reference at(size_type offset) const
		{	range_check(offset); return real_ptr[offset];	}
		//! Direct element access WITH range check
		inline reference at(size_type offset)
		{	range_check(offset); return real_ptr[offset];	}
		inline reference front() { return *real_ptr;	}
		inline reference back() { return real_ptr[real_size - 1];	}
		inline const_reference front() const { return *real_ptr;	}
		inline const_reference back() const { return real_ptr[real_size - 1];	}
        //! @}

		//! "Array" Concept implentation
		inline const pointer c_array() const throw(){ return real_ptr;	}

		//! @name "ConstMemoryContainer" Concept implementation
		//! @{
		inline size_t mem_size() const{	return real_size;	}
		inline const byte * mem_ptr() const{ return real_ptr;	}
        //! @}

		////////////////////////////////////////////////////////////////////
		// binary_data specific members
		binary_data get_until(const size_type & size) const throw();
		binary_data get_from(const size_type & offset) const throw();
		inline size_type find(const cmem_ref & pattern, size_type offset = 0) const
		{	const_iterator it = std::search(real_ptr + offset, real_ptr + real_size,
				pattern.mem_ptr(), pattern.mem_ptr() + pattern.mem_size());
			if ((it != real_ptr + real_size) || (pattern.mem_size() == 0))
				return it - real_ptr;
			return npos;
		}
		inline size_type find(const binary_data & pattern, size_type offset = 0) const
		{	const_iterator it = std::search(real_ptr + offset, real_ptr + real_size,
				pattern.real_ptr, pattern.real_ptr + pattern.real_size);
			if ((it != real_ptr + real_size) || (pattern.real_size == 0))
				return it - real_ptr;
			return npos;
		}
        inline size_type find(const byte _byte, size_type offset = 0) const
		{	const_iterator it = std::find(real_ptr + offset, real_ptr + real_size,
				_byte);
			if (it != real_ptr + real_size) return it - real_ptr;
			return npos;
		}
		binary_data sub_data(size_type offset, size_type sz = npos) const throw();

		//! Assure a unique copy of the reserved memory
		/**
            Because binary_data support CoW the reserved memory
            may be used by other objects too. This functions breaks refernces
            and creates a unique copy for this object only. If it is already
            unique copy it just exists.
        */
		void assure_unique_copy();

		//! Check an offset if it is inrange.
		inline void range_check(size_type offset) const
		{	if (offset >= real_size) throw std::out_of_range("binary_data invalid offset");	}

		binary_data operator+(const cmem_ref &r) const;

		//! Static constant that represents an empty binary_data
		static const binary_data nothing;
		//! NO position offset.
		static const size_type npos;
	};

	// Global swap function
	inline void swap(binary_data & dt1, binary_data & dt2){	dt1.swap(dt2);	}

	// Compare operators
	inline bool operator==(const binary_data & x, const binary_data & y) throw()
	{
		// Check sizes
		if (x.size() != y.size()) return false;

		// Skip same contents
		if (x.c_array() == y.c_array()) return true;

		// Compare data
		return std::equal(x.begin(), x.end(), y.begin());
	}
	inline bool operator!=(const binary_data & x, const binary_data & y) throw()
	{	return !(x == y);		}
	inline bool operator<(const binary_data & x, const binary_data & y) throw()
	{	return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());	}
	inline bool operator>(const binary_data & x, const binary_data & y) throw()
	{	return y < x;	}
	inline bool operator<=(const binary_data & x, const binary_data & y) throw()
	{	return !(y < x);	}
	inline bool operator>=(const binary_data & x, const binary_data & y) throw()
	{	return !(x < y);	}

    // Math operators
    inline binary_data & operator+=(binary_data &x, const binary_data &y)
    {   x.append(y);  return x;   }
    inline binary_data & operator+=(binary_data &x, const cmem_ref &y)
    {   x.append(y);  return x;   }
    template<typename T>
    inline binary_data & operator+=(binary_data &x, const T &y)
    {   x.append(cmem_ref(y));  return x;   }

	//! Cast binary_data to string
	inline string to_string(const binary_data & x)
	{	return string((char *)x.c_array(), x.size());	}

    //! Cast operator to wstring
	inline wstring to_wstring(const binary_data & x)
	{	// Calculate size
		float wstring_size = (float)x.size();
		wstring_size /= sizeof(wchar_t);
		wstring_size = floor(wstring_size);
		return wstring((wchar_t *)x.c_array(), (wstring::size_type)wstring_size);
	}
};

#endif // !OONET_BINARY_DATA_HPP_INCLUDED

