#ifndef OONET_BINARY_DATA_HPP_INCLUDED
#define OONET_BINARY_DATA_HPP_INCLUDED

#include "./oonet.hpp"
#include "./mem_ref.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace oonet
{

	struct binary_data
	{
		// "CONTAINER" Concept implementation
		typedef byte value_type;
		typedef value_type * iterator;
		typedef const value_type * const_iterator;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type * pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		
	private:
		// Internal implementation
		class _mem_block;
		boost::shared_ptr<_mem_block> p_mem_block;

	protected:
		size_type off_data;		// Offset to internal memory block
		size_type s_data;		// Size of data on the internal memory block
		
		void _assure_local_copy();
		
	public:		
		binary_data();	// Empty constructor
		binary_data(const cmem_ref &);	// Construct from a memory reference
		binary_data(const_reference bt_repeated, size_type s_times);	// Construct by repeating a pattern
		virtual ~binary_data();

		// CopyAble
		binary_data(const binary_data & r);		
		binary_data & operator=(const binary_data & r);
	
		// "Container" concept implementation
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		inline size_type size() const throw(){   return s_data;   }
		inline size_type max_size() const throw(){	return s_data;	}
		inline bool empty() const throw(){	return (s_data == 0);	}
		
		// "ElementAccess" Concept implementation
		const_reference operator[](size_type offset) const throw();
		reference operator[](size_type offset) throw();
		const_reference at(size_type offset) const;
		reference at(size_type offset);
		
		// "Array" Concept implentation
		const pointer c_array() const throw();
		pointer c_array() throw();

		// Compare container
		bool operator==(const binary_data & r) const throw();
		bool operator!=(const binary_data & r) const throw();
		bool operator<(const binary_data & r) const throw();

		// "MemoryContainer" Concept implementation
		inline size_t mem_size() const{	return s_data;	}
		byte * mem_ptr();
		const byte * mem_ptr() const;
		
		////////////////////////////////////////////////////////////////////
		// binary_data specific members
		binary_data get_until(const size_type & offset) const throw();
		binary_data get_from(const size_type & offset) const throw();
		size_type find(const cmem_ref & pattern, size_type offset = 0) const;
		binary_data sub_data(size_type offset, size_type sz = npos) const throw();
		void clear();
		
		binary_data operator+(const binary_data &r) const;
		binary_data operator+(const cmem_ref &r) const;
		
		binary_data & operator+=(const binary_data &r);
		binary_data & operator+=(const cmem_ref &r);
		
		// Static constant variables
		static const binary_data nothing;
		static const size_type npos;
		
		string to_string() const;
		wstring to_wstring() const;
	};  
};  

#endif // !OONET_BINARY_DATA_HPP_INCLUDED
