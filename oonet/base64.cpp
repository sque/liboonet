/**
@file base64.cpp
@brief Implementation of the base64 class.
*/

#include "./base64.hpp"
#include <string.h>

namespace oonet
{
	// Constructor
	base64::base64()
	{
		// Init translation table
		strcpy(Table,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=");
	}

	// Constructor with custom encoding table
	base64::base64(const string & b64table)
	{
		// Init translation table
		strcpy(Table, b64table.c_str());
	}

	// Destructor
	base64::~base64()
	{
	}


	// Encodes a buffer & returns a pointer to a string with encoded data
	string base64::encode(const binary_data & r)
	{
		size_t i, j, iEnc=0;
		TBase64 base64;
		string b64string;
		const char * pBuff = (const char *)r.get_data_ptr();
		char * EncBuff;		// A buffer with encoded string
		size_t sBuff = r.size();

		// Allocate memory for encoded data
		if ((EncBuff = new char[(sBuff*4/3)+4]) == NULL)
			return NULL;

		for(i = 0;i < sBuff ;i += 3)
		{
			if ((sBuff - i) >= 3)
			{
				for(j = 0;j <3; j++) base64.bin[j] = pBuff[i+j];  // Load 3 bytes to mask
				base64.base[0] = (base64.bin[0] & 0xFC) >> 2;
				base64.base[1] = ((base64.bin[0] & 0x03) << 4) | ((base64.bin[1] & 0xF0) >> 4);
				base64.base[2] = ((base64.bin[1] & 0x0F) << 2) | ((base64.bin[2] & 0xC0) >> 6);
				base64.base[3] = base64.bin[2] & 0x3F;

			}
			else if ((sBuff - i) == 2)
			{
				for(j = 0;j <2; j++) base64.bin[j] = pBuff[i+j];   // Loads the 2 last bytes
				base64.bin[3] = 0;								  // Zeroses last one
				base64.base[0] = (base64.bin[0] & 0xFC) >> 2;
				base64.base[1] = ((base64.bin[0] & 0x03) << 4) | ((base64.bin[1] & 0xF0) >> 4);
				base64.base[2] = ((base64.bin[1] & 0x0F) << 2) | ((base64.bin[2] & 0xC0) >> 6);
				base64.base[3] = 64;
			}
			else if ((sBuff - i) == 1)
			{
				base64.bin[0] = pBuff[i];						  // Loads the 1st byte
				for(j = 1;j <3; j++) base64.bin[j] = 0;		      // Zeroses last 2

				base64.base[0] = (base64.bin[0] & 0xFC) >> 2;
				base64.base[1] = ((base64.bin[0] & 0x03) << 4) | ((base64.bin[1] & 0xF0) >> 4);
				base64.base[2] = 64;
				base64.base[3] = 64;
			}
			for(j = 0;j < 4;j ++)								// Read 4 bytes from mask through translation table
				EncBuff[iEnc+j] = Table[base64.base[j]];
			iEnc += 4;
		}
		// Terminate String
		EncBuff[iEnc] = 0;
		b64string = EncBuff;
		delete [] EncBuff;

		// Return b64 string
		return b64string;
	}

	int base64::base64_decode_value(char value_in)
	{
		static const char decoding[] = {62,-1,-1,-1,63,52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-2,-1,-1,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
		static const char decoding_size = sizeof(decoding);
		value_in -= 43;
		if (value_in < 0 || value_in > decoding_size) return -1;
		return decoding[(int)value_in];
	}

	// Decodes a string
	binary_data base64::decode(const string & b64string)
	{
		// Enumeration of states
		enum
		{	step_a, step_b, step_c, step_d	};

		// Initialize values
		char * DecBuff;
		binary_data DecodedData;
		const char * pB64Buff = b64string.c_str();
		size_t B64Size = b64string.size();
		size_t SizeDecBuff;

		// Allocate enough memory
		DecBuff = new char[strlen(pB64Buff) /3 * 4];
		SizeDecBuff = 0;

		/*************************************************
		  * B64 decode Taken from libb64.sf.net project
		  **/
		const char * codechar = pB64Buff;
		char * plainchar = DecBuff;
		char fragment;
		int step = step_a;
		*plainchar = 0;

		switch (step)
		{
			while (1)
			{
		case step_a:
				do {
					if (codechar == pB64Buff + B64Size)
					{
						step = step_a;
						SizeDecBuff = (size_t)(plainchar - DecBuff);
						goto b64dec_finalize;
					}
					fragment = (char)base64_decode_value(*codechar++);
				} while (fragment < 0);
				*plainchar    = (fragment & 0x03f) << 2;
		case step_b:
				do {
					if (codechar == pB64Buff + B64Size)
					{
						step = step_b;
						SizeDecBuff = (size_t)(plainchar - DecBuff);
						goto b64dec_finalize;
					}
					fragment = (char)base64_decode_value(*codechar++);
				} while (fragment < 0);
				*plainchar++ |= (fragment & 0x030) >> 4;
				*plainchar    = (fragment & 0x00f) << 4;
		case step_c:
				do {
					if (codechar == pB64Buff + B64Size)
					{
						step = step_c;
						SizeDecBuff = (size_t)(plainchar - DecBuff);
						goto b64dec_finalize;
					}
					fragment = (char)base64_decode_value(*codechar++);
				} while (fragment < 0);
				*plainchar++ |= (fragment & 0x03c) >> 2;
				*plainchar    = (fragment & 0x003) << 6;
		case step_d:
				do {
					if (codechar == pB64Buff + B64Size)
					{
						step = step_d;
						SizeDecBuff = (size_t)(plainchar - DecBuff);
						goto b64dec_finalize;
					}
					fragment = (char)base64_decode_value(*codechar++);
				} while (fragment < 0);
				*plainchar++   |= (fragment & 0x03f);
			}
		}

	b64dec_finalize:
		// Make binary object and relase buffer
		DecodedData = binary_data((byte *)DecBuff, SizeDecBuff);
		delete [] DecBuff;
		// Return object
		return DecodedData;
	}
};	// !oonet namespace
