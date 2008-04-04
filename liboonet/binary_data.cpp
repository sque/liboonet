/**
@file BinaryData.cpp
@brief Implementation of the BinaryData class.
*/
#include "./binary_data.hpp"

#include <math.h>

namespace oonet
{
	///////////////////////////////////////////////
	// Constants
	const BinaryData BinaryData::EMPTY = BinaryData();
	const size_t BinaryData::npos = 0xFFFFFFFF;

	// Allocates space to fit specific amount
	void BinaryData::_scale_mem(size_t MemBlock, bool preservData)
	{	size_t newSz;

		// Check if we fit (Upper boundry) (Lowest boundry no need to calculate for shrinking) (Half of buff)
		if ((MemBlock <= sBuff) && ((sBuff == 1024) || (MemBlock >= sBuff/2)))
			return;

		// Calculate new size
		newSz = ((MemBlock) / 1024) + 1;
		newSz *= 1024;

		// Allocate mem
		Byte * ptemp;   // Temporary pointer
		try
		{
			if (pData != &dummyByte)
				// Reallocate
				ptemp = (Byte *)realloc(pData, newSz);
			else
				// Allocate
				ptemp = new Byte[newSz];
			pData = ptemp;
		}catch(std::bad_alloc & b_alloc)
		{	b_alloc = b_alloc;
			ptemp = NULL;
		}

		// In any case check it... (realloc doesn't throw exceptions)
		if (ptemp == NULL)
			// Throw our's exception
			OONET_THROW_EXCEPTION(ExceptionBadAllocation, "Cannot allocate memory for BinaryData");


		// Save new size of buffer
		sBuff = newSz;

		// Return pointer
		return;
	}


	// Simple constructor
	BinaryData::BinaryData():
        sBuff(0),
		pData(&dummyByte)
	{
		sData = 0;
	}

	// Copy constuctor
	BinaryData::BinaryData(const BinaryData &r):
		sBuff(0),
		pData(&dummyByte)
	{
		// Scale memmory to fit new data
		_scale_mem(r.sData);

		// Copy new ones
		sData = r.sData;
		memcpy(pData, r.pData, sData);
	}

	//Construtor from binary pointer
	BinaryData::BinaryData(const void * p_data, size_t sz_data) throw(Exception):
		sBuff(0),
		pData(&dummyByte)
	{
		OONET_ASSERT(p_data != NULL);

		// Scale memory to fit data
		_scale_mem(sz_data);
		sData = sz_data;

		// Copy data
		memcpy(pData, p_data, sz_data);

	}

	// Constructor from a single Byte
	BinaryData::BinaryData(const Byte b):
		sBuff(0),
		pData(&dummyByte)
	{
		// Calculate space
		sData = sizeof(Byte);

		// Allocate space
		_scale_mem(sData);

		// Copy data
		*pData = b;
	}

	// Constructor from a byte replication
	BinaryData::BinaryData(const Byte mByte, size_t bTimes) throw(Exception):
		sBuff(0),
		pData(&dummyByte)
	{
		// Scale memory to fit new data
		_scale_mem(bTimes);
		sData = bTimes;

		// Fill data with a byte
		memset(pData , mByte, sData);
	}

	// Constructor from Ansi String
	BinaryData::BinaryData(const string & str) throw(Exception):
		sBuff(0),
		pData(&dummyByte)
	{
		// Count data and scale buffer
		sData = str.size() * sizeof(string::value_type);
		_scale_mem(sData);

		// Copy data
		memcpy(pData, str.c_str(), sData);
	}

	// Constructor from Unicode String
	BinaryData::BinaryData(const wstring & str) throw(Exception):
		sBuff(0),
		pData(&dummyByte)
	{
		// Count data and scale buffer
		sData = str.size() * sizeof(wstring::value_type);
		_scale_mem(sData);

		// Copy data
		memcpy(pData, str.c_str(), sData);
	}

	// Destructor
	BinaryData::~BinaryData()
	{
		// Free allocated space
		if (pData != &dummyByte)
			delete [] pData;
	}

	// Copy action
	BinaryData &BinaryData::operator=(const BinaryData &r) throw(Exception)
	{
		// Scale memmory
		_scale_mem(r.sData);

		// Copy data from the right operand
		sData = r.sData;
		memcpy(pData, r.pData, sData);
		return *this;
	}

	bool BinaryData::operator!=(const BinaryData &r) const
	{   return  (! ((*this) == r));    }

	// Access elemnt operation
	Byte BinaryData::operator[](size_t offset) const throw(Exception)
	{
		if (offset > sData)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");
		return pData[offset];
	}
	// Add action
	BinaryData BinaryData::operator+(const BinaryData &r) const throw(Exception)
	{
		// Create a temp
		BinaryData temp = *this;

		// Add the right assignment
		temp +=r;

		// return the result
		return temp;
	}

	// Add action (one byte)
	BinaryData BinaryData::operator+(const Byte &r)const throw(Exception)
	{
		// Create a temp
		BinaryData temp = *this;

		// Add the right assignment
		temp += r;

		// return result
		return temp;
	}

	// Push action
	BinaryData &BinaryData::operator+=(const BinaryData &r) throw(Exception)
	{
		// Scale memory to fit all data
		_scale_mem(sData + r.sData);

		// Copy new data at the end
		memcpy(pData + sData, r.pData, r.sData);

		// Add size
		sData += r.sData;

		return *this;
	}

	// Push action (one byte)
	BinaryData & BinaryData::operator+=(const Byte &r) throw(Exception)
	{
		// Scale memory to fit all data
		_scale_mem(sData + 1);

		// Add byte at end of buffer
		*(pData + sData) = r;

		// Increase buffer
		sData ++;

		return (*this);
	}

	// Comparison action
	bool BinaryData::operator==(const BinaryData &r) const
	{
		// Check sizes
		if (sData != r.sData)
			return false;

		// Compare data
		if (0 != memcmp(pData, r.pData, sData))
			return false;

		// Else everything is ok
		return true;
	}


	// Get Ansi String object
	string BinaryData::toString() const
	{
		return string((char *)pData, sData);
	}

	// Get Winde String object
	wstring BinaryData::toWString() const
	{	// Calculate size
		float wstring_size = (float)sData;
		wstring_size /= sizeof(wchar_t);
		wstring_size = floor(wstring_size);
		return wstring((wchar_t *)pData, (wstring::size_type)wstring_size);
	}

	// Get starting packet until that size
	BinaryData BinaryData::getUntil(const size_t & offset) const throw(ExceptionNotFound)
	{
		// If requested is more than available, then throw
		if (offset > sData)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");

		return BinaryData(pData, offset);
	}

	// Get the rest of packet from a specific offset
	BinaryData BinaryData::getFrom(const size_t & offset) const throw(ExceptionNotFound)
	{
		// If requested is more than available, then return empty
		if (offset > sData)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset is bigger than the actual size of datablock");

		return BinaryData(pData + offset, sData - offset);
	}

	// Slice data from a point, till some size
	BinaryData BinaryData::slice(size_t offset, size_t sz) const
	{
		if (offset + sz > sData)
			OONET_THROW_EXCEPTION(ExceptionNotFound, "Offset and size can't work in the size of this data");

		return BinaryData(pData + offset, sz);
	}
	// Find a pattern in the data block
	size_t BinaryData::find(const BinaryData & pattern) const
	{	Byte  * p, * pEnd, firstChar;

		// Check if there are data
		if (pattern.sData == 0)
			OONET_THROW_EXCEPTION(ExceptionWrongArgument, "Pattern is empty! Cannot search for something that does not exists");

        // Check if data fits in search
        if (pattern.sData > sData)
            return npos;

		// Initialize values
		pEnd = pData + sData - pattern.sData + 1;
		firstChar = *pattern.pData;

		// Search for pattern - general optimized (The class is general, so we cant optimize it more specificly)
		p = pData;
		while((p =(Byte *) memchr(p, firstChar, pEnd - p)))
		{
			if (0 == memcmp(p, pattern.pData, pattern.sData) )
				return (p - pData);
			p++;
		}

		// Not found
		return npos;
	}

	// Clear
	void BinaryData::clear()
	{
		// Scale the memory to zero size
		_scale_mem(0);

		// Empty data
		sData = 0;
	}
};	// !oonet namespace
