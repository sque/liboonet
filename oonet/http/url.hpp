#ifndef OONET_HTTP_URL_HPP_INCLUDED
#define OONET_HTTP_URL_HPP_INCLUDED

#include "../oonet.hpp"

#include <vector>

namespace oonet
{
	namespace http
	{
		//! Class for managing a url parameter
		/**
			It is just a tuple of name-value strings. It also
			provides the ability to parse a string and split it
			to name-param
		*/
		class url_param
		{
		public:
			//! Constructor
			url_param();

			//! Construct and parse a string
			/**
				String will be parsed and member variables UrlParam::Name,
				UrlParam::Value will be populated with the appropriate values.
			@param parse_str [IN] The string that will be parsed at construction time
			@see parse()
			*/
			explicit url_param(const string & parse_str);

			//! Copy constuctor
			url_param(const url_param & r);

			//! Copy operator
			url_param & operator=(const url_param & r);

			//! Destructor
			~url_param();

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
		class url
		{
		public:
			//! Exception raised when the url was not properly formated.
			OONET_DECLARE_EXCEPTION(ExceptionWrongUrl);

			//! Parameter List definition
			typedef std::vector<url_param> ParameterList;

			//! Default constructor
			/**
				Url will be empty
			*/
			url(void);

			//! Construct from string
			/**
				Url will be copied internally and used
				in future operations.
			*/
			inline url(const string & url_str)
			{	full_url = url_str;	}

			//! Copy constructor
			inline url(const url &r)
			{	full_url = r.full_url;	}

			//! Destructor
			virtual ~url(void);

			//! Copy operator
			inline url & operator=(const url &r)
			{	full_url = r.full_url;
				return *this;
			}

			//! Assign a string
			/**
				A new url will be stored to be used
				at future operations.
			*/
			inline url & operator=(const string & url_str)
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

		}; // !url class
	};	// !http namespace
};	// !oonet namespace
#endif // !OONET_HTTP_URL_HPP_INCLUDED
