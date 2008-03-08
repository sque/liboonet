#ifndef SLIB_HTTP_URL_H_DEFINED
#define SLIB_HTTP_URL_H_DEFINED
#include "../platform.h"
#include "../Exception.h"

#include <vector>
using std::vector;

namespace Slib
{
	namespace HTTP
	{
		//! Class for managing a url parameter
		/**
			It is just a tuple of name-value strings. It also
			provides the ability to parse a string and split it
			to name-param
		*/
		class UrlParam
		{
		public:
			//! Constructor
			UrlParam();

			//! Construct and parse a string
			/**
				String will be parsed and member variables UrlParam::Name,
				UrlParam::Value will be populated with the appropriate values.
			@param parse_str [IN] The string that will be parsed at construction time
			@see parse()
			*/
			explicit UrlParam(const string & parse_str);

			//! Copy constuctor
			UrlParam(const UrlParam & r);

			//! Copy operator
			UrlParam & operator=(const UrlParam & r);

			//! Destructor
			~UrlParam();

			//! Parse a string of url format e.g myname=myvalue
			/**
			@param parse_str [IN] The string in url format that will be parsed.

				After parsing the UrlParam::Name and UrlParam::Value
				will be populated with the name and value of parameter.
			*/
			void parse(const string & parse_str);

			//! The name of url parameter
			string Name;
			//! The value of url parameter
			string Value;
		};	// UrlParam class

		//! Class for parsing url strings
		/**
			It can parse an http/ftp url and split it in smaller
			parts. There are 3 levels of spliting that can be performed.\n
			<i>e.g. http://www.google.com:8080/search.php?file=a&lan=en</i>
			@li Scheme - Host - Resource
				The result will be:\n
				<b>Scheme:</b> <i>http</i>\n
				<b>Host:</b> <i>www.google.com:8080</i>\n
				<b>Resource:</b> <i>/search.php?file=a&lan=en</i>\n
			@li Scheme - Host - Port - Resource
				The result will be:\n
				<b>Scheme:</b> <i>http</i>\n
				<b>Host:</b> <i>www.google.com</i>\n
				<b>Port:</b> <i>8080</i>\n
				<b>Resource:</b> <i>/search.php?file=a&lan=en</i>\n
			@li Scheme - Host - Port - Path - Parameters List
				The result will be:\n
				<b>Scheme:</b> <i>http</i>\n
				<b>Host:</b> <i>www.google.com</i>\n
				<b>Port:</b> <i>8080</i>\n
				<b>Path:</b> <i>/search.php</i>\n
				<b>Parameters List:</b> <i>file=a&lan=en</i>\n
		*/
		class Url
		{
		public:
			//! Exception raised when the url was not properly formated.
			SLIB_DECLARE_EXCEPTION(ExceptionWrongUrl);

			//! Parameter List definition
			typedef vector<UrlParam> ParameterList;

			//! Default constructor
			/**
				Url will be empty
			*/
			Url(void);

			//! Construct from string
			/**
				Url will be copied internally and used
				in future operations.
			*/
			inline Url(const string & url_str)
			{	full_url = url_str;	}

			//! Copy constructor
			inline Url(const Url &r)
			{	full_url = r.full_url;	}

			//! Destructor
			virtual ~Url(void);

			//! Copy operator
			inline Url & operator=(const Url &r)
			{	full_url = r.full_url;
				return *this;
			}

			//! Assign a string
			/**
				A new url will be stored to be used
				at future operations.
			*/
			inline Url & operator=(const string & url_str)
			{	full_url = url_str;
				return *this;
			}

			//! Cast to string
			inline operator const string & () const
			{	return full_url;	}

			//! Split url in 3 major pieces
			/**
				The url will be splitted in 3 major pieces <b>Scheme</b>, <b>Host Port</b> and <b>Resource</b>
			@param scheme [OUT] The string to store the scheme that url referes.
			@param hostport [OUT] The string to store the host n port tha resource resides.
			@param resource [OUT] The string to save the resource path.
			@throw ExceptionWrongUrl If the url has not the proper format.
			*/
			void split(string & scheme, string & hostport, string & resource) const;

			//! Split url in 4 major pieces
			/**
				The url will be splitted in 3 major pieces <b>Scheme</b>, <b>Host</b>, <b>Port</b> and <b>Resource</b>
			@param scheme [OUT] The string to store the scheme that url referes.
			@param host [OUT] The string to store the host tha resource resides.
			@param port [OUT] The string to store the port that server host listens.
			@param resource [OUT] The string to save the resource path.
			@throw ExceptionWrongUrl If the url has not the proper format.
			*/
			void split (string & scheme, string & host, string & port, string & resource) const;

			//! Split url in 4 major pieces
			/**
				The url will be splitted in 3 major pieces <b>Scheme</b>, <b>Host</b>, <b>Port</b>, <b>Path</b> and  <b>Parameters List</b>
			@param scheme [OUT] The string to store the scheme that url referes.
			@param host [OUT] The string to store the host tha resource resides.
			@param port [OUT] The string to store the port that server host listens.
			@param path [OUT] The string to save the resource path.
			@param params [OUT] The string to save the resource's parameters.
			@throw ExceptionWrongUrl If the url has not the proper format.
			*/
			void split(string & scheme, string & host, string & port, string & path, ParameterList & params) const;

		protected:
			string full_url;	//!< The full url

		private:
			//! Tool to split the parameters of the url in a list
			/**
				Input must not have the leading '?' character and parameters must be splitted
				using the & sign.
			*/
			void _split_params(const string & par_string, ParameterList & param_list) const;

		}; // Url class
	};	// HTTP namespace
};	// Slib namespace
#endif // SLIB_HTTP_URL_H_DEFINED
