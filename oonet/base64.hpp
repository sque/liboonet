#ifndef OONET_BASE64_HPP_INCLUDED
#define OONET_BASE64_HPP_INCLUDED

#include "./oonet.hpp"
#include "./binary_data.hpp"

namespace oonet
{
	//! Base64 is a handy tool for Base64 encodings/decondings.
	/**
		It provides encoding/decoding with base64 encoding. It uses
		the default base64 table, but it is possible to provide a custom
		base64 table.
	*/
	class base64
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
		base64();

		//! Constructor with custom encoding table
		/**
			This constructor is used if you want to create an object
			that will do encoding/decoding with custom base64 table.
		@param b64table A string that must have 64 letters, that will be used as
			encoding/decoding table.
		*/
		explicit base64(const string & b64table);

		//! Destructor
		virtual ~base64();

		//! Encodes a binary block and returns it encoded in base64 format.
		/**
		@param in The input data block which will be encoded in base64.
		@return A string containing the data block encoded in base64 format.
		*/
		string encode(const binary_data & in);

		//! Decodes a base64 string and returns binary data
		/**
		@param b64_encoded A string that contains the base64 encoded data block
		@return The data block decoded.
		*/
		binary_data decode(const string & b64_encoded);

	};	// !Base64 class

};	// !oonet namespace
#endif // !OONET_BASE64_HPP_INCLUDED
