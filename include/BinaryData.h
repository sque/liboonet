#ifndef SLIB_BINARYDATA_H_INCLUDED
#define SLIB_BINARYDATA_H_INCLUDED

#include "platform.h"
#include "Exception.h"

namespace Slib
{
	//! Object representing data blocks
	/**
		Similar to std::string, this is a class for handling binary data.
		It supports all the basic operations as copying, comparing, expanding,
		shrinking as extra operations like searching inside them. It is highly
		optimized and is easy to use it. It can supports creating binary objects
		from std::string or std::wstring and converting back to them.
	*/
	class BinaryData
	{
	private:
		Byte dummyByte;	//!< An internal dummy byte when we dont have allocated mem
		size_t sBuff;	//!< Size of current allocated buffer

	protected:
		Byte * pData;	//!< Pointer to our data
		size_t sData;	//!< Size of data

		//! Scales the current internal memmory to fit new data
		/**
		@param FitMem The desired size of data that we want to fit, it maybe less or more.
		@param preservData If this flag is true, buffer is scaled and guarantees that previous data is still there.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		void _scale_mem(size_t FitMem, bool preservData = true);

	public:
		//! A constant empty BinaryData. Usefull for comparisons.
		static const BinaryData EMPTY;

		//! A constant which means <b>no position</b>
		/**
			It is used by functions that return size_t when operation didn't complete correctly
		*/
		static const size_t npos;

		//! Default constructor
		/**
			Creates an empty BinaryData object
		*/
		BinaryData();

		//! Copy constructor
		BinaryData(const BinaryData &r);

		//! Destructor
		virtual ~BinaryData();

		//! Constructor from std::string
		/**
			A new object is created and all the characters of std::string
			are copied <b>WITHOUT</b> a null character at the end.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		explicit BinaryData(const string & str) throw(Exception);

		//! Constructor from std::wstring
		/**
			A new object is created and all the characters of std::string
			are copied <b>WITHOUT</b> a null character at the end.
		@remarks
			The size of the BinaryData depends on the size of wchar_t on
			the current machine. If the size of wchar_t is 2 bytes then it
			will have
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		explicit BinaryData(const wstring & str) throw(Exception);

		//! Constructor from a single Byte
		explicit BinaryData(const Byte b);

		//! Constructor from a byte array
		/**
			Data will be copied at new object, thus original data can be
			erased after the creation of object.
		@param p_data Pointer to data array.
		@param sz_data Size of array in bytes.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		BinaryData(const void * p_data, size_t sz_data) throw(Exception);

		//! Constructor that fills buffer with a repeated byte
		/**
			It will fill the new object with the same byte as many
			times as the user defines.
		@param mByte Byte that will be repeated.
		@param bTimes How many times the byte will be repeat. This will
			be the size of new buffer too.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		BinaryData(const Byte mByte, size_t bTimes) throw(Exception);

		//! @name Operators
		//! @{

		//! Copy operator
		/**
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		BinaryData &operator=(const BinaryData &r) throw(Exception);

		//! Add operator
		/**
			It will create a new object that will have first the
			data of this object and then the data of the right object.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		BinaryData operator+(const BinaryData &r) const throw(Exception);

		//! Add operator (one byte)
		/**
			It will create a new object that will have this object's
			data and the end the Byte that we added.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		BinaryData operator+(const Byte &r)const throw(Exception);

		//! Self-add operator (push action)
		/**
			This is similar to <b>push</b> action on a stack. The
			right operand's data will be copied at the end of this
			data block.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		BinaryData &operator+=(const BinaryData &r) throw(Exception);

		//! Self-add operator for one byte (push action)
		/**
			The byte will be copied at the end of this data block.
		@throw ExceptionBadAllocation When allocation of new internal buffer is impossible for some reason.
		*/
		BinaryData &operator+=(const Byte &r) throw(Exception);

		//! Access element
		/**
			It will return the byte that correspond in the index
			given by user.
		@throw ExceptionNotFound When requested element is not in the boundries of
			current data block's size.
		*/
		Byte operator[](size_t offset) const throw(Exception);

		//! Equal comparison operator
		/**
			It will return true if the two BinaryData objects
			have the same size and same data.
		*/
		bool operator==(const BinaryData &r) const;

		//! InEqual comparison operator
		/**
			It will return false if the two BinaryData objects
			have the same size and same data.
		*/
		bool operator!=(const BinaryData &r) const;
		//! @}

		//! Get const pointer to data
		/**
			It will return the pointer to internal buffer.
		@see size()
		*/
		inline const Byte * getDataPtr() const
		{   return pData;   }

		//! Get size of data
		/**
			Returns the size of data that this object holds.
		@remarks This is not the size of the allocated space
			this is the size of data. BinaryData may have allocated
			more space for reasons of performance.
		*/
		inline size_t size() const
		{   return sData;   }

		//! Cast these data to a std::string
		/**
			It will create and return a std::string object
			from the data that holds.
		*/
		string toString() const;

		//! Cast these data to a std::wstring
		/**
			It will create and return a std::wstring object
			from the data that holds.
		*/
		wstring toWString() const;

		//! Get data until a specific offset
		/**
			It will cut this object from the start until
			a specific offset and will return a new BinaryData
			object containing the sliced data.
		@param offset The offset until data will be copied.
		@throw ExceptionNotFound If desired offset is outside boundries
			of current data.
		@see getFrom
		*/
		BinaryData getUntil(const size_t & offset) const throw(ExceptionNotFound);

		//! Get data from a specific offset until the end
		/**
			It will cut this object from the specified offset
			until the end of data and return a new BinaryData
			object containing the sliced data
		@param offset The offset from which it will start copying data.
		@throw ExceptionNotFound If desired offset is outside boundries
			of current data.
		@see getUntil
		*/
		BinaryData getFrom(const size_t & offset) const throw(ExceptionNotFound);

		//! Find a pattern in the data block and return its offset
		/**
			It will try to match the specified pattern and at the
			first succesfull matching, starting from the begining
			of data, it will return its offset
		@param pattern Pattern of data to search inside this object.
		@return The offset of the matched data, or BinaryData::npos if pattern couldn't
			be found.
		@throw ExceptionWrongArgument If the pattern is an empty BinaryData object.
		*/
		size_t find(const BinaryData & pattern) const;

		//! Slice data from a specific offset, with specific size
		/**
			It will copy the selected part at a new BinaryData object
			and return it.
		@param offset The starting offset of the subpart.
		@param sz The size of the subpart
		@throw ExceptionNotFound If the offset along with size results at a subpart that
			it is outside boundries of current data.
		*/
		BinaryData slice(size_t offset, size_t sz) const;

		//! Clear data.
		void clear();

		//! Check if it is an empty object.
		inline bool empty() const
		{	return (sData == 0);	}

	};  // !BinaryData class
};  // !Slib namespace

#endif // SLIB_BINARYDATA_H_INCLUDED
