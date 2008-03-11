#ifndef OONET_BASE64_H_DEFINED
#define OONET_BASE64_H_DEFINED

#include "OONet.h"
#include "BinaryData.h"

namespace OONet
{
	//! Base64 is a handy tool for Base64 encodings/decondings.
	/**
		It provides encoding/decoding with base64 encoding. It uses
		the default base64 table, but it is possible to provide a custom
		base64 table.
	*/
	class Base64
	{
	private:
		//! Translation Table (ASCII NEEDED!)
		struct TBase64
		{
			char bin[3];
			char base[4];
		};
		char Table[66];

		int base64_decode_value(char value_in);
	public:

		//! Default constructor
		/**
			For all encodings/decodings the default string table will be used.
		*/
		Base64();

		//! Constructor with custom encoding table
		/**
			This constructor is used if you want to create an object
			that will do encoding/decoding with custom base64 table.
		@param b64table A string that must have 64 letters, that will be used as
			encoding/decoding table.
		*/
		explicit Base64(const string & b64table);

		//! Destructor
		virtual ~Base64();

		//! Encodes a binary block and returns it encoded in base64 format.
		/**
		@param in The input data block which will be encoded in base64.
		@return A string containing the data block encoded in base64 format.
		*/
		string Encode(const BinaryData & in);

		//! Decodes a base64 string and returns binary data
		/**
		@param b64_encoded A string that contains the base64 encoded data block
		@return The data block decoded.
		*/
		BinaryData Decode(const string & b64_encoded);

	};	// !Base64 class

};	// !OONet namespace
#endif // !OONET_BASE64_H_DEFINED
