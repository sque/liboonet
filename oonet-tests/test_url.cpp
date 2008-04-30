#include "test_url.hpp"
#include <oonet/http/url.hpp>

namespace oonet
{
	TestUrl theTestUrl;

	bool TestUrl::TestUrlParamCtor::OnExecute()
	{	http::url_params a;

		if (!a.list().empty())
			return false;

		if (!a.full().empty())
			return false;

		return true;
	}

	bool TestUrl::TestUrlParamParseCtor::OnExecute()
	{
		// Test some parsing
		http::url_params a("b=124");
		if (a.full() != "b=124")
			return false;
		if (a.list().size() != 1)
			return false;
		if (a.begin()->first != "b")
			return false;
		if (a.begin()->second != "124")
			return false;


		http::url_params b("250402kfoe=sdfgklsjdflgkjsdfg90sdfug09sdfugoj");
		if (b.full() != "250402kfoe=sdfgklsjdflgkjsdfg90sdfug09sdfugoj")
			return false;
		if (b.list().size() != 1)
			return false;
		if (b.begin()->first != "250402kfoe")
			return false;
		if (b.begin()->second != "sdfgklsjdflgkjsdfg90sdfug09sdfugoj")
			return false;

		// No value
		http::url_params c("dsfklgjsdkflgjsdf");
		if (c.full() != "dsfklgjsdkflgjsdf")
			return false;
		if (c.list().size() != 1)
			return false;
		if (c.begin()->first != "dsfklgjsdkflgjsdf")
			return false;
		if (c.begin()->second != "")
			return false;

		// Embended =
		http::url_params d("dsfklgjsdkflgjsdf=123=123");
		if (d.full() != "dsfklgjsdkflgjsdf=123=123")
			return false;
		if (d.list().size() != 1)
			return false;
		if (d.begin()->first != "dsfklgjsdkflgjsdf")
			return false;
		if (d.begin()->second != "123=123")
			return false;

		return true;
	}

	bool TestUrl::TestUrlParamCopyCtor::OnExecute()
	{	http::url_params a("kaka=lola");
		http::url_params b(a);

		if (b.list().size() != 1)
			return false;
		if (b.begin()->first != "kaka")
			return false;
		if (b.begin()->second != "lola")
			return false;
		return true;
	}

	bool TestUrl::TestUrlParamCopyOperator::OnExecute()
	{	http::url_params a("kaka=lola");
		http::url_params b;

		b = a;
		if (b.list().size() != 1)
			return false;
		if (b.begin()->first != "kaka")
			return false;
		if (b.begin()->second != "lola")
			return false;
		return true;
	}

	bool TestUrl::TestUrlParamParse::OnExecute()
	{	http::url_params a;

		// Test 100k parsings
		for(long i = 0;i < 100000; i++)
			a.parse("fofo=lola");

		if (a.list().size() != 1)
			return false;
		if (a.begin()->first != "fofo")
			return false;
		if (a.begin()->second != "lola")
			return false;		return true;
	}

	bool TestUrl::TestUrlCtor::OnExecute()
	{	http::url a;

		if (a.full() != "")
			return false;
		if (a.host_port() != "")
			return false;
		if (a.host() != "")
			return false;
		if (a.port() != "")
			return false;
		if (a.resource() != "")
			return false;
		if (a.path() != "")
			return false;
		if (a.parameters().full() != "")
			return false;
		return true;
	}

	bool TestUrl::TestUrlCtorString::OnExecute()
	{	http::url a = http::url("http://www.gogla.gr/test1?par=1&par2=3");

		if (a.full() != "http://www.gogla.gr/test1?par=1&par2=3")
			return false;
		if (a.scheme() != "http")
			return false;
		if (a.host_port() != "www.gogla.gr")
			return false;
		if (a.host() != "www.gogla.gr")
			return false;
		if (a.port() != "")
			return false;
		if (a.resource() != "/test1?par=1&par2=3")
			return false;
		if (a.path() != "/test1")
			return false;
		if (a.parameters().list().size() != 2)
			return false;
		return true;
	}

	bool TestUrl::TestCopyCtor::OnExecute()
	{	http::url b = http::url("http://www.gogla.gr/test1?par=1&par2=3");
		http::url a(b);

		if (a.full() != "http://www.gogla.gr/test1?par=1&par2=3")
			return false;
		if (a.scheme() != "http")
			return false;
		if (a.host_port() != "www.gogla.gr")
			return false;
		if (a.host() != "www.gogla.gr")
			return false;
		if (a.port() != "")
			return false;
		if (a.resource() != "/test1?par=1&par2=3")
			return false;
		if (a.path() != "/test1")
			return false;
		if (a.parameters().list().size() != 2)
			return false;
		return true;
	}

	bool TestUrl::TestCopyOperatorUrl::OnExecute()
	{	http::url b = http::url("http://www.gogla.gr/test1?par=1&par2=3");
		http::url a;

		a = b;
		if (a.full() != "http://www.gogla.gr/test1?par=1&par2=3")
			return false;
		if (a.scheme() != "http")
			return false;
		if (a.host_port() != "www.gogla.gr")
			return false;
		if (a.host() != "www.gogla.gr")
			return false;
		if (a.port() != "")
			return false;
		if (a.resource() != "/test1?par=1&par2=3")
			return false;
		if (a.path() != "/test1")
			return false;
		if (a.parameters().list().size() != 2)
			return false;
		return true;
	}

	bool TestUrl::TestSplit3Wrong1::OnExecute()
	{	http::url b("http:/lolalosadfadsf");

		return false;
	}

	bool TestUrl::TestSplit3Wrong2::OnExecute()
	{	http::url b("http//lolalosadfadsf");

		return false;
	}

	bool TestUrl::TestSplit3Speed::OnExecute()
	{	http::url b;

		for(long i = 0;i < 10000;i++)
			b = http::url("http://www.google.com:43/sadf.sf?asdfasd%");

		if (b.scheme() != "http")
			return false;
		if (b.host_port() != "www.google.com:43")
			return false;
		if (b.resource() != "/sadf.sf?asdfasd%")
			return false;
		return true;
	}

	bool TestUrl::TestSplit3Quality::OnExecute()
	{	http::url b;
		string scheme, host, resource;

		b = http::url("http://www.google.com:43/sadf.sf?asdfasd%");
		if (b.scheme() != "http")
			return false;
		if (b.host_port() != "www.google.com:43")
			return false;
		if (b.resource() != "/sadf.sf?asdfasd%")
			return false;

		b = http::url("http://:www.goo:gle.com:43//////");
		if (b.scheme() != "http")
			return false;
		if (b.host_port() != ":www.goo:gle.com:43")
			return false;
		if (b.resource() != "//////")
			return false;

		b = http::url("http://");
		if (b.scheme() != "http")
			return false;
		if (b.host_port() != "")
			return false;
		if (b.resource() != "")
			return false;

		b = http::url("http:///");
		if (b.scheme() != "http")
			return false;
		if (b.host_port() != "")
			return false;
		if (b.resource() != "/")
			return false;
		return true;
	}

	bool TestUrl::TestSplit4Wrong1::OnExecute()
	{	http::url b("http:://lolal:/osadfadsf");

		return false;
	}

	bool TestUrl::TestSplit4Quality::OnExecute()
	{	http::url b;

		b = http::url("http://asdfasD:12/");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "asdfasD")
			return false;
		if (b.port() != "12")
			return false;
		if (b.resource() != "/")
			return false;

		b = http::url("http://asdfa:sD:12/");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "asdfa")
			return false;
		if (b.port() != "sD:12")
			return false;
		if (b.resource() != "/")
			return false;


		b = http::url("http://www/12:32");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "www")
			return false;
		if (b.port() != "")
			return false;
		if (b.resource() != "/12:32")
			return false;

		b = http::url("http://");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "")
			return false;
		if (b.port() != "")
			return false;
		if (b.resource() != "")
			return false;

		b = http::url("http:///");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "")
			return false;
		if (b.port() != "")
			return false;
		if (b.resource() != "/")
			return false;

		b = http::url("http:///:");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "")
			return false;
		if (b.port() != "")
			return false;
		if (b.resource() != "/:")
			return false;

		return true;
	}

	bool TestUrl::TestSplit4Speed::OnExecute()
	{	http::url b;

		for(long i = 0;i < 10000;i++)
			b = http::url("http://www.google.com:43/sadf.sf?asdfasd%");

		if (b.scheme() != "http")
			return false;
		if (b.host() != "www.google.com")
			return false;
		if (b.port() != "43")
			return false;
		if (b.resource() != "/sadf.sf?asdfasd%")
			return false;
		return true;
	}

	bool TestUrl::TestSplit5Wrong1::OnExecute()
	{	http::url b("http///lolal:/osadfadsf?");

		return false;
	}

	bool TestUrl::TestSplit5Quality::OnExecute()
	{	http::url b;

		b = http::url("http://?");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "?")
			return false;
		if (b.port() != "")
			return false;
		if (b.path() != "")
			return false;
		if (b.parameters().list().size() != 0)
			return false;

		b = http::url("http:///?");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "")
			return false;
		if (b.port() != "")
			return false;
		if (b.path() != "/")
			return false;
		if (b.parameters().list().size() != 0)
			return false;

 		b = http::url("http:///?a");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "")
			return false;
		if (b.port() != "")
			return false;
		if (b.path() != "/")
			return false;
		if (b.parameters().list().size() != 1)
			return false;
		if (b.parameters().list()[0].first != "a")
			return false;
		if (b.parameters().list()[0].second != "")
			return false;

		b = http::url("http:///??a");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "")
			return false;
		if (b.port() != "")
			return false;
		if (b.path() != "/")
			return false;
		if (b.parameters().list().size() != 1)
			return false;
		if (b.parameters().list()[0].first != "?a")
			return false;
		if (b.parameters().list()[0].second != "")
			return false;

		b = http::url("http:///?&a");
		if (b.scheme() != "http")
			return false;
		if (b.host() != "")
			return false;
		if (b.port() != "")
			return false;
		if (b.path() != "/")
			return false;
		if (b.parameters().list().size() != 1)
			return false;
		if (b.parameters().list()[0].first != "a")
			return false;
		if (b.parameters().list()[0].second != "")
			return false;

		return true;
	}

	bool TestUrl::TestSplit5Speed::OnExecute()
	{	http::url b;

		for(long i = 0;i < 10000;i++)
			b = http::url("http://www.google.com:43/sadf.sf?asdfasd%");

		if (b.scheme() != "http")
			return false;
		if (b.host() != "www.google.com")
			return false;
		if (b.port() != "43")
			return false;
		if (b.path() != "/sadf.sf")
			return false;
		if (b.parameters().list().size() != 1)
			return false;
		if (b.parameters().list()[0].first != "asdfasd%")
			return false;
		if (b.parameters().list()[0].second != "")
			return false;
		return true;
	}
};	// !oonet namespace
