#ifndef OONET_BINARY_DATA_HPP_INCLUDED
#define OONET_BINARY_DATA_HPP_INCLUDED

#include "./oonet.hpp"

#include <vector>
#include <boost/shared_ptr.hpp>

namespace oonet
{
	//! Object representing data blocks
	/**
		Similar to std::string, this is a class for handling binary data.
		It supports all the basic operations as copying, comparing, expanding,
		shrinking as extra operations like searching inside them. It is highly
		optimized and is easy to use it. It can supports creating binary objects
		from std::string or std::wstring and converting back to them.
	*/
	class binary_data
	{
	private:
		class _mem_block;
		boost::shared_ptr<_mem_block> p_mem_block;

	protected:
		size_t off_data;	//!< Offset of memory block
		size_t s_data;		//!< Size of data

		//! Create real copy if needed
		void _assure_local_copy();

	public:
		//! A constant of empty binary_data. Usefull for comparisons.
		static const binary_data nothing;

		//! A constant which means <b>no position</b>
		static const size_t npos;

		//! Default constructor
		/**
			Creates an empty binary_data object
		*/
		binary_data();

		//! Destructor
		virtual ~binary_data();

		//! Copy constructor
		binary_data(const binary_data & r);

		//! Copy operator
		binary_data & operator=(const binary_data & r);

		//! Constructor from std::string
		/**
			A new object is created and all the characters of std::string
			are copied <b>WITHOUT</b> a null character at the end.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		explicit binary_data(const string & str);

		//! Constructor from std::wstring
		/**
			A new object is created and all the characters of std::string
			are copied <b>WITHOUT</b> a null character at the end.
		@remarks
			The size of the binary_data depends on the size of wchar_t on
			the current machine. If the size of wchar_t is 2 bytes then it
			will have
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		explicit binary_data(const wstring & str);

		//! Constructor from a single byte
		explicit binary_data(const byte & b);

		//! Constructor from a byte array
		/**
			Data will be copied at new object, thus original data can be
			erased after the creation of object.
		@param _p_data Pointer to data array.
		@param _sz_data Size of array in bytes.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		binary_data(const void * _p_data, size_t _sz_data);

		//! Constructor that fills buffer with a repeated byte
		/**
			It will fill the new object with the same byte as many
			times as the user defines.
		@param bt_repeated Byte that will be repeated.
		@param s_times How many times the byte will be repeat. This will be the size of new buffer too.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		binary_data(const byte & bt_repeated, size_t s_times);

		//! Add operator
		/**
			It will create a new object that will have first the
			data of this object and then the data of the right object.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		binary_data operator+(const binary_data &r) const;

		//! Add operator (one byte)
		/**
			It will create a new object that will have this object's
			data and the end the byte that we added.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		binary_data operator+(const byte &r)const;

		//! Self-add operator (push action)
		/**
			This is similar to <b>push</b> action on a stack. The
			right operand's data will be copied at the end of this
			data block.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		binary_data & operator+=(const binary_data &r);

		//! Self-add operator for one byte (push action)
		/**
			The byte will be copied at the end of this data block.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		binary_data & operator+=(const byte &r);

		//! Access element
		/**
			It will return the byte that correspond in the index
			given by user.
		@throw ExceptionNotFound When requested element is not in the boundries of
			current data block's size.
		*/
		const byte & operator[](size_t offset) const;

		//! Access elemt
		byte & operator[](size_t offset);

		//! Equal comparison operator
		/**
			It will return true if the two binary_data objects
			have the same size and same data.
		*/
		bool operator==(const binary_data & r) const throw();

		//! InEqual comparison operator
		/**
			It will return false if the two binary_data objects
			have the same size and same data.
		*/
		bool operator!=(const binary_data & r) const throw();

		//! Less comparison
		bool operator<(const binary_data & r) const throw();

		//! @}

		//! Get const pointer to data
		/**
			It will return the pointer to internal buffer.
		@see size()
		*/
		const byte * get_data_ptr() const throw();


		//! Get size of data
		/**
			Returns the size of data that this object holds.
		@remarks This is not the size of the allocated space
			this is the size of data. binary_data may have allocated
			more space for reasons of performance.
		*/
		inline size_t size() const throw()
		{   return s_data;   }

		//! Cast these data to a std::string
		/**
			It will create and return a std::string object
			from the data that holds.
		*/
		string to_string() const;

		//! Cast these data to a std::wstring
		/**
			It will create and return a std::wstring object
			from the data that holds.
		*/
		wstring to_wstring() const;

		//! Get data until a specific offset
		/**
			It will cut this object from the start until
			a specific offset and will return a new binary_data
			object containing the sliced data.
		@param offset The offset until data will be copied.
		@throw ExceptionNotFound If desired offset is outside boundries
			of current data.
		@see get_from
		*/
		binary_data get_until(const size_t & offset) const throw();

		//! Get data from a specific offset until the end
		/**
			It will cut this object from the specified offset
			until the end of data and return a new binary_data
			object containing the sliced data
		@param offset The offset from which it will start copying data.
		@throw ExceptionNotFound If desired offset is outside boundries
			of current data.
		@see get_until
		*/
		binary_data get_from(const size_t & offset) const throw();

		//! Find a pattern in the data block and return its offset
		/**
			It will try to match the specified pattern and at the
			first succesfull matching, starting from the begining
			of data, it will return its offset
		@param pattern Pattern of data to search inside this object.
		@param offset The offset to start searching from.
		@return The offset of the matched data, or binary_data::npos if pattern couldn't
			be found.
		@throw ExceptionWrongArgument If the pattern is an empty binary_data object.
		*/
		size_t find(const binary_data & pattern, size_t offset = 0) const;

		//! Slice data from a specific offset, with specific size
		/**
			It will copy the selected part at a new binary_data object
			and return it.
		@param offset The starting offset of the subpart.
		@param sz The size of the subpart
			it is outside boundries of current data.
		*/
		binary_data sub_data(size_t offset, size_t sz = npos) const throw();

		//! Clear data.
		void clear();

		//! Check if it is an empty object.
		inline bool empty() const throw()
		{	return (s_data == 0);	}
	};  // !binary_data class
};  // !oonet namespace

#endif // OONET_BINARY_DATA_HPP_INCLUDED
