#include "./url.hpp"

namespace oonet
{
	namespace http
	{
		//! find the 1st occurance of a parameter by name
		url_params::const_iterator url_params::find(const string & _name)
		{	const_iterator c_it;

			for(c_it = begin();c_it != end(); c_it ++)
			{
				if (c_it->first == _name)
					return c_it;
			}

			return end();	// Not found
		}

		//! Parse a parameters string
		void url_params::parse(const string & _params_str)
		{	size_t off_start, off_end, off_equal;
			string _name, _value, _param;

			// Initialize data
			m_parameters.clear();
			off_start = - 1;

			do{
				off_start ++;
				off_end = _params_str.find('&', off_start);

				// Omit empty parameters
				if ((_param = _params_str.substr(off_start, off_end)) == "")
					continue;

				if ((off_equal = _param.find('=')) == string::npos)
					m_parameters.push_back(value_type(_param, ""));
				else
					m_parameters.push_back(value_type(_param.substr(0, off_equal), _param.substr(off_equal + 1)));


			}
			while((off_start =_params_str.find('&', off_end)) != string::npos);
		}

		// Parse a url and populate variables
		void url::_parse(const string & _url)
		{	size_t off_end_scheme, off_end_hostport;

			// Reset internal data
			m_scheme = m_host_port = m_host = m_port = m_path = m_resource = "";
			m_params.clear();

			// Check size
			if (_url.empty())
				OONET_THROW_EXCEPTION(ExceptionWrongUrl, "Cannot parse an empty url..");

			if (_url[0] == '/')
			{	// Relative resource url (it doesn't provide scheme host port) only resource
				m_resource = _url;
			}
			else	// Url in absolute format
			{
				// Find scheme end
				if ((off_end_scheme = _url.find("://")) == string::npos)
					OONET_THROW_EXCEPTION(ExceptionWrongUrl, string("Cannot parse url: ") + _url);

				// Get scheme
				m_scheme = _url.substr(0, off_end_scheme);

				// Find host port ending
				if ((off_end_hostport = _url.find("/", off_end_scheme + 3)) == string::npos)
				{
					// There is no resource in the url
					m_host_port = _url.substr(off_end_scheme + 3);
				}
				else
				{
					m_host_port = _url.substr(off_end_scheme + 3, off_end_hostport - off_end_scheme - 3);
					m_resource = _url.substr(off_end_hostport);
				}
			}

			// Do second level parsing
			_second_level_parse();
		}

		// Internal implementation of parsing
		void url::_second_level_parse()
		{	size_t off_preport_colon;
			size_t off_preparam_quest_mark;

			// Split host/port
			if ((off_preport_colon = m_host_port.find(':')) == string::npos)
			{
				m_host = m_host_port;
			}
			else
			{
				m_host = m_host_port.substr(0, off_preport_colon);
				m_port = m_host_port.substr(off_preport_colon + 1);
			}

			// Split path/parameters
			if ((off_preparam_quest_mark = m_resource.find('?')) == string::npos)
			{
				m_path = m_resource;
			}
			else
			{
				m_path = m_resource.substr(0, off_preparam_quest_mark);
				m_params.parse(m_resource.substr(off_preparam_quest_mark + 1));
			}
		}

	};	// !http namespace
};	// !oonet namespace
