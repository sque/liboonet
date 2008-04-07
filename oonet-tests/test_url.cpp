#include "test_url.hpp"
#include "http/url.hpp"

namespace oonet
{
	TestUrl theTestUrl;

	bool TestUrl::TestUrlParamCtor::OnExecute()
	{	http::UrlParam a;

		if (a.Value != "")
			return false;

		if (a.Name != "")
			return false;

		return true;
	}

	bool TestUrl::TestUrlParamParseCtor::OnExecute()
	{
		// Test some parsing
		http::UrlParam a("b=124");
		if (a.Name != "b")
			return false;
		if (a.Value != "124")
			return false;

		http::UrlParam b("250402kfoe=sdfgklsjdflgkjsdfg90sdfug09sdfugoj");
		if (b.Name != "250402kfoe")
			return false;
		if (b.Value != "sdfgklsjdflgkjsdfg90sdfug09sdfugoj")
			return false;

		// No value
		http::UrlParam c("dsfklgjsdkflgjsdf");
		if (c.Name != "dsfklgjsdkflgjsdf")
			return false;
		if (c.Value != "")
			return false;

		// Embended =
		http::UrlParam d("dsfklgjsdkflgjsdf=123=123");
		if (d.Name != "dsfklgjsdkflgjsdf")
			return false;
		if (d.Value != "123=123")
			return false;

		return true;
	}

	bool TestUrl::TestUrlParamCopyCtor::OnExecute()
	{	http::UrlParam a("kaka=lola");
		http::UrlParam b(a);

		if (b.Name != "kaka")
			return false;
		if (b.Value != "lola")
			return false;
		return true;
	}

	bool TestUrl::TestUrlParamCopyOperator::OnExecute()
	{	http::UrlParam a("kaka=lola");
		http::UrlParam b;

		b = a;
		if (b.Name != "kaka")
			return false;
		if (b.Value != "lola")
			return false;
		return true;
	}

	bool TestUrl::TestUrlParamParse::OnExecute()
	{	http::UrlParam a;

		// Test 100k parsings
		for(long i = 0;i < 100000; i++)
			a.parse("fofo=lola");

		if (a.Name != "fofo")
			return false;
		if (a.Value != "lola")
			return false;
		return true;
	}

	bool TestUrl::TestUrlCtor::OnExecute()
	{	http::Url a;

		if ((string)a != "")
			return false;
		return true;
	}

	bool TestUrl::TestUrlCtorString::OnExecute()
	{	http::Url a = string("http://www.google.com");

		if ((string)a != "http://www.google.com")
			return false;

		return true;
	}

	bool TestUrl::TestCopyCtor::OnExecute()
	{	http::Url a = string("http://www.gogla.gr");
		http::Url b(a);

		if ((string)b != "http://www.gogla.gr")
			return false;

		return true;
	}

	bool TestUrl::TestCopyOperatorUrl::OnExecute()
	{	http::Url a = string("http://www.gogla.gr");
		http::Url b;
		b = a;

		if ((string)b != "http://www.gogla.gr")
			return false;

		return true;
	}

	bool TestUrl::TestCopyOperatorString::OnExecute()
	{	string a = string("http://www.gogla.gr");
		http::Url b;
		b = a;

		if ((string)b != "http://www.gogla.gr")
			return false;

		return true;
	}

	bool TestUrl::TestSplit3Wrong1::OnExecute()
	{	http::Url b = string("http:/lolalosadfadsf");
		string scheme, host, resource;
		b.split(scheme, host, resource);
		return false;
	}

	bool TestUrl::TestSplit3Wrong2::OnExecute()
	{	http::Url b = string("http//lolalosadfadsf");
		string scheme, host, resource;
		b.split(scheme, host, resource);
		return false;
	}

	bool TestUrl::TestSplit3Speed::OnExecute()
	{	http::Url b = string("http://www.google.com:43/sadf.sf?asdfasd%");
		string scheme, host, resource;

		for(long i = 0;i < 10000;i++)
			b.split(scheme, host, resource);

		if (scheme != "http")
			return false;
		if (host != "www.google.com:43")
			return false;
		if (resource != "/sadf.sf?asdfasd%")
			return false;
		return true;
	}

	bool TestUrl::TestSplit3Quality::OnExecute()
	{	http::Url b;
		string scheme, host, resource;

		b = "http://www.google.com:43/sadf.sf?asdfasd%";
		b.split(scheme, host, resource);
		if (scheme != "http")
			return false;
		if (host != "www.google.com:43")
			return false;
		if (resource != "/sadf.sf?asdfasd%")
			return false;

		b = "http://:www.goo:gle.com:43//////";
		b.split(scheme, host, resource);
		if (scheme != "http")
			return false;
		if (host != ":www.goo:gle.com:43")
			return false;
		if (resource != "//////")
			return false;

		b = "http://";
		b.split(scheme, host, resource);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (resource != "")
			return false;

		b = "http:///";
		b.split(scheme, host, resource);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (resource != "/")
			return false;
		return true;
	}

	bool TestUrl::TestSplit4Wrong1::OnExecute()
	{	http::Url b = string("http:://lolal:/osadfadsf");
		string scheme, host, port, resource;
		b.split(scheme, host, port, resource);
		printf("scheme %s, host %s, port %s, resource %s\n", scheme.c_str(), host.c_str(), port.c_str(), resource.c_str());
		return false;
	}

	bool TestUrl::TestSplit4Quality::OnExecute()
	{	http::Url b;
		string scheme, host, port, resource;

		b = "http://asdfasD:12/";
		b.split(scheme, host, port, resource);
		if (scheme != "http")
			return false;
		if (host != "asdfasD")
			return false;
		if (port != "12")
			return false;
		if (resource != "/")
			return false;

		b = "http://asdfa:sD:12/";
		b.split(scheme, host, port, resource);
		if (scheme != "http")
			return false;
		if (host != "asdfa")
			return false;
		if (port != "sD:12")
			return false;
		if (resource != "/")
			return false;


		b = "http://www/12:32";
		b.split(scheme, host, port, resource);
		if (scheme != "http")
			return false;
		if (host != "www")
			return false;
		if (port != "")
			return false;
		if (resource != "/12:32")
			return false;

		b = "http://";
		b.split(scheme, host, port, resource);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (port != "")
			return false;
		if (resource != "")
			return false;

		b = "http:///";
		b.split(scheme, host, port, resource);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (port != "")
			return false;
		if (resource != "/")
			return false;

		b = "http:///:";
		b.split(scheme, host, port, resource);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (port != "")
			return false;
		if (resource != "/:")
			return false;

		return true;
	}

	bool TestUrl::TestSplit4Speed::OnExecute()
	{	http::Url b = string("http://www.google.com:43/sadf.sf?asdfasd%");
		string scheme, host, port, resource;

		for(long i = 0;i < 10000;i++)
			b.split(scheme, host, port, resource);

		if (scheme != "http")
			return false;
		if (host != "www.google.com")
			return false;
		if (port != "43")
			return false;
		if (resource != "/sadf.sf?asdfasd%")
			return false;
		return true;
	}

	bool TestUrl::TestSplit5Wrong1::OnExecute()
	{	http::Url b = string("http///lolal:/osadfadsf?");
		string scheme, host, port, resource;
		http::Url::ParameterList params;

		b.split(scheme, host, port, resource, params);
		return false;
	}

	bool TestUrl::TestSplit5Quality::OnExecute()
	{	http::Url b;
		string scheme, host, port, resource;
		http::Url::ParameterList params;


		b = "http://?";
		b.split(scheme, host, port, resource, params);
		if (scheme != "http")
			return false;
		if (host != "?")
			return false;
		if (port != "")
			return false;
		if (resource != "")
			return false;
		if (params.size() != 0)
			return false;

		b = "http:///?";
		b.split(scheme, host, port, resource, params);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (port != "")
			return false;
		if (resource != "/")
			return false;
		if (params.size() != 0)
			return false;

 		b = "http:///?a";
		b.split(scheme, host, port, resource, params);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (port != "")
			return false;
		if (resource != "/")
			return false;
		if (params.size() != 1)
			return false;
		if (params[0].Name != "a")
			return false;
		if (params[0].Value != "")
			return false;

		b = "http:///??a";
		b.split(scheme, host, port, resource, params);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (port != "")
			return false;
		if (resource != "/")
			return false;
		if (params.size() != 1)
			return false;
		if (params[0].Name != "?a")
			return false;
		if (params[0].Value != "")
			return false;

		b = "http:///?&a";
		b.split(scheme, host, port, resource, params);
		if (scheme != "http")
			return false;
		if (host != "")
			return false;
		if (port != "")
			return false;
		if (resource != "/")
			return false;
		if (params.size() != 1)
			return false;
		if (params[0].Name != "a")
			return false;
		if (params[0].Value != "")
			return false;

		return true;
	}

	bool TestUrl::TestSplit5Speed::OnExecute()
	{	http::Url b = string("http://www.google.com:43/sadf.sf?asdfasd%");
		string scheme, host, port, resource;
		http::Url::ParameterList params;
		for(long i = 0;i < 10000;i++)
			b.split(scheme, host, port, resource, params);

		if (scheme != "http")
			return false;
		if (host != "www.google.com")
			return false;
		if (port != "43")
			return false;
		if (resource != "/sadf.sf")
			return false;
		if (params.size() != 1)
			return false;
		if (params[0].Name != "asdfasd%")
			return false;
		if (params[0].Value != "")
			return false;
		return true;
	}
};	// !oonet namespace
