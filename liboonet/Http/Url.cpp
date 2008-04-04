/**
@file Url.cpp
@brief Implementation of HTTP::UrlParam and HTTP::Url class
*/
#include "./Url.h"

namespace oonet
{
	namespace HTTP
	{
		// Constructor
		UrlParam::UrlParam()
		{}

		// Constructor from string
		UrlParam::UrlParam(const string & parse_str)
		{	parse(parse_str);	}

		// Parse string
		void UrlParam::parse(const string & parse_str)
		{	size_t off_equal;

			// Initialize data
			Value = Name = "";

			// Parse string
			if ((off_equal = parse_str.find('=')) != string::npos)
			{
				Name = parse_str.substr(0, off_equal);
				Value = parse_str.substr(off_equal + 1, string::npos);
			}
			else
				Name = parse_str;
		}

		// Copy constuctor
		UrlParam::UrlParam(const UrlParam & r)
			:Name(r.Name),
			Value(r.Value)
		{}

		// Copy operator
		UrlParam & UrlParam::operator=(const UrlParam & r)
		{
			Name = r.Name;
			Value = r.Value;
			return *this;
		}

		// Destructor
		UrlParam::~UrlParam()
		{}

		Url::Url(void)
		{
		}

		Url::~Url(void)
		{
		}

		// Split url in major pieces
		void Url::split(string & scheme, string & hostport, string & resource) const
		{	string tmp_host, full_host;
			size_t Offset1;

			// Check size
			if (full_url.size() == 0)
				OONET_THROW_EXCEPTION(ExceptionWrongUrl, "Cannot parse an empty url..");

			// Initialize data
			scheme = hostport = resource = "";

			// Check if there is scheme
			if (full_url[0] != '/')
			{
				// Scheme
				Offset1 = full_url.find("://");	// lest find scheme ending
				if (Offset1 == string::npos)
					OONET_THROW_EXCEPTION(ExceptionWrongUrl, string("Cannot parse url: ") + full_url);

				scheme = full_url.substr(0, Offset1);
				tmp_host = full_url.substr(Offset1 + 3, string::npos);

				// Find hostport
				Offset1 = tmp_host.find("/");
				hostport = tmp_host.substr(0, Offset1);

				// Resource
				if (Offset1 == string::npos)
					resource = "";
				else
					resource = tmp_host.substr(Offset1, string::npos);
			}
			else
				resource = full_url;
		}

		// Split url in major pieces but split port too
		void Url::split(string & scheme, string & host, string & port, string & resource) const
		{	string hostport;
			size_t Offset1;

			// Split in major parts
			split(scheme, hostport, resource);

			// Initialize data
			host = port = "";

			// Split host/port
			Offset1 = hostport.find(':');
			if (Offset1 == string::npos)
			{
				host = hostport;
			}
			else
			{
				host = hostport.substr(0,Offset1);
				port = hostport.substr(Offset1 + 1, string::npos);
			}
		}

		// Split url
		void Url::split(string & scheme, string & host, string & port, string & path, ParameterList & params) const
		{	string full_params, resource;
			size_t Offset1;

			// Initialize data
			resource = "";
			params.clear();

			// Split in major parts
			split(scheme, host, port, resource);


			// Split path and params
			Offset1 = resource.find('?');
			if (Offset1 == string::npos)
				path = resource;
			else
			{
				path = resource.substr(0, Offset1);
				full_params = resource.substr(Offset1 + 1, string::npos);

				// Split params
				_split_params(full_params, params);

			}
		}

		// Tool to split params of the url
		void Url::_split_params(const string &par_string, ParameterList & param_list) const
		{	size_t off_start, off_end;
			string ParamLiteral;

			// Initialize data
			off_start = string::npos;

			do{
				off_start ++;
				off_end = par_string.find('&', off_start);
				// Omit empty parameters
				if ((ParamLiteral = par_string.substr(off_start, off_end)) == "")
					continue;
				param_list.push_back(UrlParam(ParamLiteral));
			}
			while((off_start = par_string.find('&', off_end)) != string::npos);
		}
	};	// !HTTP namespace
};	// !oonet namespace
