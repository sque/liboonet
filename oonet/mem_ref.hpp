#ifndef OONET_MEM_REF_HPP_INCLUDED
#define OONET_MEM_REF_HPP_INCLUDED

#include "./oonet.hpp"
#include <stdexcept>

namespace oonet
{
	template<typename T>
	struct array_ref
	{
		typedef T value_type;
		typedef value_type * iterator;
		typedef const value_type * const_iterator;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type * pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		
	private:
		pointer ptr_data;
		size_t count_data;
	
	public:
		/////////////////////////////////////////////////////////////////////
		// "CONTAINER" Concept Implementation
		inline const_iterator begin() const	{	return ptr_data;		}
		inline iterator begin()	{	return ptr_data;		}
		inline const_iterator end() const {	return ptr_data + count_data;		}
		inline iterator end() {	return ptr_data + count_data;		}
		inline size_type size() const {	return count_data;		}
		inline size_type max_size() const {	return count_data;		}
		inline bool empty() const {	return (count_data == 0);	}
		inline void assign(const array_ref & r)
		{	ptr_data = r.ptr_data; count_data = r.count_data;	}
		
		void swap(array_ref & other)
		{	// Save in temporary container our pointer/type
			pointer tmp_ptr = ptr_data;
			size_type tmp_count = count_data;
			
			// Swap
			ptr_data = other.ptr_data;
			count_data = other.count_data;
			other.ptr_data = tmp_ptr;
			other.count_data = tmp_count;
		}
	
		///////////////////////////////////////////////////////////////////
		// "ELEMENT_ACCESS" concept implementation
		inline const_reference operator[](size_type off) const
			{	return ptr_data[off];		}
		inline reference operator[](size_type off) {	return ptr_data[off];		}
		inline reference front(){	return *ptr_data;	}
		inline const_reference front() const {	return *ptr_data;	}
		inline reference back(){	return ptr_data[count_data - 1];	}
		inline const_reference back() const {	return ptr_data[count_data - 1];	}
		
		inline const_reference at(size_type off) const
		{	if (off >= count_data)
				throw std::out_of_range("array_ref::at() wrong offset");
			return ptr_data[off];
		}
		
		inline reference at(size_type off)
		{	if (off >= count_data)
				throw std::out_of_range("array_ref::at() wrong offset");
			return ptr_data[off];
		}
		
		///////////////////////////////////////////////////////////////////
		// "ARRAY" concept implemenetation
		inline const pointer c_array() const {	return ptr_data;		}
		inline pointer c_array() {	return ptr_data;		}

		// "CONSTRUCTORS"
		inline array_ref()	:ptr_data(NULL), count_data(0) {} // no-throw
		inline array_ref(pointer _ptr, size_t _count)	// no-throw
			:ptr_data(_ptr), count_data(_count)	{}
		
		// "COPYABLE"
		inline array_ref(const array_ref & r)	// no-throw
			:ptr_data(r.ptr_data), count_data(r.count_data) {}
		inline array_ref & operator=(const array_ref & r)	// no-throw
		{	assign(r);	return *this;	}
	};
		
	// Specialization for byte
	template<>
	struct array_ref<byte>
	{
		typedef byte value_type;
		typedef value_type * iterator;
		typedef const value_type * const_iterator;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type * pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		
	private:
		pointer ptr_data;
		size_t count_data;
	
	public:	
		/////////////////////////////////////////////////////////////////////
		// "CONTAINER" Concept Implementation
		inline const_iterator begin() const	{	return ptr_data;		}
		inline iterator begin()	{	return ptr_data;		}
		inline const_iterator end() const {	return ptr_data + count_data;		}
		inline iterator end() {	return ptr_data + count_data;		}
		inline size_type size() const {	return count_data;		}
		inline size_type max_size() const {	return count_data;		}
		inline bool empty() const {	return (count_data == 0);	}
		inline void assign(const array_ref & r)
		{	ptr_data = r.ptr_data; count_data = r.count_data;	}
		
		void swap(array_ref & other)
		{	// Save in temporary container our pointer/type
			pointer tmp_ptr = ptr_data;
			size_type tmp_count = count_data;
			
			// Swap
			ptr_data = other.ptr_data;
			count_data = other.count_data;
			other.ptr_data = tmp_ptr;
			other.count_data = tmp_count;
		}
	
		///////////////////////////////////////////////////////////////////
		// "ELEMENT_ACCESS" concept implementation
		inline const_reference operator[](size_type off) const
			{	return ptr_data[off];		}
		inline reference operator[](size_type off) {	return ptr_data[off];		}
		inline reference front(){	return *ptr_data;	}
		inline const_reference front() const {	return *ptr_data;	}
		inline reference back(){	return ptr_data[count_data - 1];	}
		inline const_reference back() const {	return ptr_data[count_data - 1];	}
		
		inline const_reference at(size_type off) const
		{	if (off >= count_data)
				throw std::out_of_range("array_ref::at() wrong offset");
			return ptr_data[off];
		}
		
		inline reference at(size_type off)
		{	if (off >= count_data)
				throw std::out_of_range("array_ref::at() wrong offset");
			return ptr_data[off];
		}
		
		///////////////////////////////////////////////////////////////////
		// "ARRAY" concept implemenetation
		inline const pointer c_array() const {	return ptr_data;		}
		inline pointer c_array() {	return ptr_data;		}

		// "CONSTRUCTORS"
		inline array_ref()	:ptr_data(NULL), count_data(0) {} // no-throw
		inline array_ref(pointer _ptr, size_t _count)	// no-throw
			:ptr_data(_ptr), count_data(_count)	{}
		
		// "COPYABLE"
		inline array_ref(const array_ref & r)	// no-throw
			:ptr_data(r.ptr_data), count_data(r.count_data) {}
		inline array_ref & operator=(const array_ref & r)	// no-throw
		{	assign(r);	return *this;	}
		
		
		/////////////////////////////////////////////////////////////////////
		// "array_ref<byte>" Specialized members

		// Create from "MemoryContainer" Concept
		template<typename U>
		array_ref(U & _mem_cont)
			:ptr_data(_mem_cont.mem_ptr()),
			count_data(_mem_cont.mem_size())
		{}
		
		// Create from std::basic_string
		template<typename C>
		inline array_ref(std::basic_string<C> & str)
			:ptr_data((byte *)str.c_str()), count_data(str.size() * sizeof(C)){}
		
		// Create from built-in types
		explicit inline array_ref(char & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(short & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(int & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(long & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(double & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(float & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}

		explicit inline array_ref(unsigned char & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(unsigned short & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(unsigned int & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(unsigned long & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		
		// "MemoryContainer" concept Implementation
		inline const pointer mem_ptr() const{	return ptr_data;	}
		inline pointer mem_ptr() {	return ptr_data;	}
		inline size_t mem_size() const{	return count_data;	}
	};
	
	// Specialization for const byte
	template<>
	struct array_ref<const byte>
	{
		typedef const byte value_type;
		typedef value_type * iterator;
		typedef const value_type * const_iterator;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type * pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		
	private:
		pointer ptr_data;
		size_t count_data;
	
	public:	
		/////////////////////////////////////////////////////////////////////
		// "CONTAINER" Concept Implementation
		inline const_iterator begin() const	{	return ptr_data;		}
		inline iterator begin()	{	return ptr_data;		}
		inline const_iterator end() const {	return ptr_data + count_data;		}
		inline iterator end() {	return ptr_data + count_data;		}
		inline size_type size() const {	return count_data;		}
		inline size_type max_size() const {	return count_data;		}
		inline bool empty() const {	return (count_data == 0);	}
		inline void assign(const array_ref & r)
		{	ptr_data = r.ptr_data; count_data = r.count_data;	}
		
		void swap(array_ref & other)
		{	// Save in temporary container our pointer/type
			pointer tmp_ptr = ptr_data;
			size_type tmp_count = count_data;
			
			// Swap
			ptr_data = other.ptr_data;
			count_data = other.count_data;
			other.ptr_data = tmp_ptr;
			other.count_data = tmp_count;
		}
	
		///////////////////////////////////////////////////////////////////
		// "ELEMENT_ACCESS" concept implementation
		inline const_reference operator[](size_type off) const
			{	return ptr_data[off];		}
		inline reference operator[](size_type off) {	return ptr_data[off];		}
		inline reference front(){	return *ptr_data;	}
		inline const_reference front() const {	return *ptr_data;	}
		inline reference back(){	return ptr_data[count_data - 1];	}
		inline const_reference back() const {	return ptr_data[count_data - 1];	}
		
		inline const_reference at(size_type off) const
		{	if (off >= count_data)
				throw std::out_of_range("array_ref::at() wrong offset");
			return ptr_data[off];
		}
		
		inline reference at(size_type off)
		{	if (off >= count_data)
				throw std::out_of_range("array_ref::at() wrong offset");
			return ptr_data[off];
		}
		
		///////////////////////////////////////////////////////////////////
		// "ARRAY" concept implemenetation
		inline const pointer c_array() const {	return ptr_data;		}
		inline pointer c_array() {	return ptr_data;		}

		// "CONSTRUCTORS"
		inline array_ref()	:ptr_data(NULL), count_data(0) {} // no-throw
		inline array_ref(pointer _ptr, size_t _count)	// no-throw
			:ptr_data(_ptr), count_data(_count)	{}
		
		// "COPYABLE"
		inline array_ref(const array_ref & r)	// no-throw
			:ptr_data(r.ptr_data), count_data(r.count_data) {}
		inline array_ref & operator=(const array_ref & r)	// no-throw
		{	assign(r);	return *this;	}
	
		/////////////////////////////////////////////////////////////////////
		// "array_ref<byte>" Specialized members

		// Copyable from "non const"
		inline void assign(const array_ref<byte> & r)
		{	ptr_data = &r[0]; count_data = r.size();	}
		inline array_ref(const array_ref<byte> & r)	// no-throw
			:ptr_data(&r[0]), count_data(r.size()) {}
		inline array_ref & operator=(const array_ref<byte> & r)	// no-throw
		{	assign(r);	return *this;	}
		
		// Create from "ConstMemoryContainer" Concept
		template<typename U>
		inline array_ref(const U & _mem_cont)
			:ptr_data(_mem_cont.mem_ptr()),	count_data(_mem_cont.mem_size()) {}
		
		// Create from old static string
		inline array_ref(const char * str):ptr_data((byte *)str), count_data(std::char_traits<char>::length(str)){}
		inline array_ref(const wchar_t * str):ptr_data((byte *)str), count_data(std::char_traits<wchar_t>::length(str) * sizeof(wchar_t)){}

		// Create from std::string
		template<typename C>
		inline array_ref(std::basic_string<C> & str)
			:ptr_data((byte *)str.c_str()), count_data(str.size() * sizeof(C)){}
		
		// Create from const std::string
		template<typename C>
		inline array_ref(const std::basic_string<C> & str)
			:ptr_data((byte *)str.c_str()), count_data(str.size() * sizeof(C)){}

		// Overload for built-in types
		explicit inline array_ref(const char & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(const short & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(const int & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(const long & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(const double & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(const float & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}

		explicit inline array_ref(const unsigned char & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(const unsigned short & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(const unsigned int & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
		explicit inline array_ref(const unsigned long & pod):ptr_data((byte *)&pod), count_data(sizeof(pod)){}
						
		// "ConstMemoryContainer" concept Implementation
		inline pointer mem_ptr() const{	return ptr_data;	}
		inline size_t mem_size() const{	return count_data;	}
	};
	
	// Type definitions of mem_ref
	typedef array_ref<byte> mem_ref;
	typedef array_ref<const byte> cmem_ref;
	
}; // oonet namespace

#endif // !OONET_MEM_REF_HPP_INCLUDED

