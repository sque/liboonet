#ifndef OONET_BINARY_DATA_HPP_INCLUDED
#define OONET_BINARY_DATA_HPP_INCLUDED

#include "./oonet.hpp"
#include "./mem_ref.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace oonet
{
	class binary_data
	{
	public:
		// "CONTAINER" Concept implementation
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
		
	private:
		// Internal implementation
		class _mem_block;
		boost::shared_ptr<_mem_block> p_mem_block;
		pointer real_ptr;		// Pointer to real data on the current memory block
		size_type real_size;	// Size of the real data on the internal memory block

	public:
		binary_data(const cmem_ref &);	// Construct from a memory reference
		explicit binary_data(size_type startup_size);	// Allocate unitialized memory
		// Allocate and initialize memory with default value
		binary_data(size_type startup_size, const_reference def_value);
		binary_data(const_iterator beg, const_iterator end);
		binary_data & operator=(const cmem_ref & ref);
		
		// "Container" concept implementation
		binary_data();					// Empty constructor
		binary_data(const binary_data & r);	
		binary_data & operator=(const binary_data & r);
		~binary_data();
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
		void swap(binary_data & r);
		
		// "ElementAccess" Concept implementation
		inline const_reference operator[](size_type offset) const throw() { return real_ptr[offset];	}
		inline reference operator[](size_type offset) throw() { return real_ptr[offset];	}
		const_reference at(size_type offset) const;
		reference at(size_type offset);
		inline reference front() { return *real_ptr;	}
		inline reference back() { return real_ptr[real_size - 1];	}
		inline const_reference front() const { return *real_ptr;	}
		inline const_reference back() const { return real_ptr[real_size - 1];	}
		
		// "Array" Concept implentation
		inline const pointer c_array() const throw(){ return real_ptr;	}

		// "ConstMemoryContainer" Concept implementation
		inline size_t mem_size() const{	return real_size;	}
		inline const byte * mem_ptr() const{ return real_ptr;	}
		
		////////////////////////////////////////////////////////////////////
		// binary_data specific members
		binary_data get_until(const size_type & size) const throw();
		binary_data get_from(const size_type & offset) const throw();
		size_type find(const cmem_ref & pattern, size_type offset = 0) const;
		binary_data sub_data(size_type offset, size_type sz = npos) const throw();
		void assure_unique_copy();
		
		binary_data operator+(const cmem_ref &r) const;
		binary_data & operator+=(const cmem_ref &r);
		binary_data operator+(const binary_data &r) const;
		binary_data & operator+=(const binary_data &r);
		
		// Static constant variables
		static const binary_data nothing;
		static const size_type npos;
		
		string to_string() const;
		wstring to_wstring() const;
	};
	
	// Global swap function
	inline void swap(binary_data & dt1, binary_data & dt2){	dt1.swap(dt2);	}
	
	// Compare operators
	bool operator==(const binary_data & x, const binary_data & y) throw();
	inline bool operator<(const binary_data & x, const binary_data & y) throw()
	{	return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());	}
	inline bool operator!=(const binary_data & x, const binary_data & y) throw()
	{	return !(x == y);		}
	inline bool operator>(const binary_data & x, const binary_data & y) throw()
	{	return y < x;	}
	inline bool operator<=(const binary_data & x, const binary_data & y) throw()
	{	return !(y < x);	}
	inline bool operator>=(const binary_data & x, const binary_data & y) throw()
	{	return !(x < y);	}
};

#endif // !OONET_BINARY_DATA_HPP_INCLUDED