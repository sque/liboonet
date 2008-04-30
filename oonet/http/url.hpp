#ifndef OONET_HTTP_URL_HPP_INCLUDED
#define OONET_HTTP_URL_HPP_INCLUDED

#include "../oonet.hpp"

#include <vector>

namespace oonet
{
	namespace http
	{
		class url;

		//! Exception raised when the url was not properly formated.
		OONET_DECLARE_EXCEPTION(ExceptionWrongUrl);

		//! STL Compatible url parameters class
		class url_params
		{
		public:

			friend class url;	//! url will populate list

			//! Parse a parameters string
			void parse(const string & _params_str);

			//! Type definition of value type
			typedef std::pair<string, string> value_type;

			//! Type definition of internal list
			typedef std::vector< value_type > list_type;

			//! Type definition of iterator
			typedef list_type::iterator iterator;

			//! Type definition of const iterator
			typedef list_type::const_iterator const_iterator;

			//! Type definition of reference
			typedef list_type::reference reference;

			//! Type definition of const reference
			typedef list_type::const_reference const_reference;
		protected:

			string m_param_string;
			list_type m_parameters;

		public:

			//! Default constructor
			url_params()
			{}

			//! Construct and parse string
			explicit url_params(const string & _str)
				:m_param_string(_str)
			{
				parse(_str);
			}

			//! Copy constructor
			url_params(const url_params & r)
				:m_param_string(r.m_param_string),
				m_parameters(r.m_parameters)
			{}

			//! Copy operator
			url_params & operator=(const url_params & r)
			{	m_param_string = r.m_param_string;
				m_parameters = r.m_parameters;
				return *this;
			}

			//! Get a direct const reference to the list
			const list_type & list() const
			{	return m_parameters;	}

			//! find the 1st occurance of a parameter by name
			const_iterator find(const string & _name) const;

			//! Check if there is a parameter
			inline bool exist(const string & _name)
			{	return (end() != find(_name));	}

			//! begin()
			inline const_iterator begin() const
			{	return m_parameters.begin();	}

			//! end()
			inline const_iterator end() const
			{	return m_parameters.end();	}

			inline const string & full() const
			{	return m_param_string;	}

			inline void clear()
			{	m_parameters.clear();
				m_param_string.clear();
			}

		};	// !url_params class

		//! Class for parsing url strings
		/**
			It can parse an http/ftp url and split it in smaller
			parts.
		*/
		class url
		{
		private:
			// Internal implementation of parsing
			void _second_level_parse();

		protected:

			string m_url;			//!< Full url string
			string m_scheme;		//!< Extracted scheme from url string
			string m_host_port;		//!< Extracted host port from url string
			string m_host;			//!< Extracted host from url string
			string m_port;			//!< Extracted port from url string
			string m_resource;		//!< Extracted resource of url string
			string m_path;			//!< Extracted path from url string
			url_params m_params;	//!< Extracted parameters from url string

			//! Parse a url and populate variables
			virtual void _parse(const string & _url);

		public:

			//! Default constructor
			url(){}

			//! Construct and parse a string
			explicit url(const string & _full_url)
				:m_url(_full_url)
			{	_parse(_full_url);	}

			//! Copy constructor
			url(const url & r)
				:m_url(r.m_url),
				m_scheme(r.m_scheme),
				m_host_port(r.m_host_port),
				m_host(r.m_host),
				m_port(r.m_port),
				m_resource(r.m_resource),
				m_path(r.m_path),
				m_params(r.m_params)
			{}

			//! Copy operator
			url & operator=(const url & r)
			{
				m_url = r.m_url;
				m_scheme = r.m_scheme;
				m_host_port = r.m_host_port;
				m_host = r.m_host;
				m_port = r.m_port;
				m_resource = r.m_resource;
				m_path = r.m_path;
				m_params = r.m_params;
				return *this;
			}

			//! Get extracted scheme
			const string & scheme() const
			{	return m_scheme;	}

			//! Get extracted host + port
			const string & host_port() const
			{	return m_host_port;	}

			//! Get extracted host
			const string & host() const
			{	return  m_host;	}

			//! Get extracted port
			const string & port() const
			{	return  m_port;	}

			//! Get extracted resource (path+parameters)
			const string & resource() const
			{	return m_resource;	}

			//! Get extracted path
			const string & path() const
			{	return m_path;	}

			//! Get extracted parameters
			const url_params & parameters() const
			{	return m_params;	}

			//! Get original url string that we parsed
			const string & full() const
			{	return m_url;	}

		}; // !url class
	};	// !http namespace
};	// !oonet namespace
#endif // !OONET_HTTP_URL_HPP_INCLUDED
