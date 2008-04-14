/**
@file exception.cpp
@brief Implementation of the exception class.
 */
#include "./exception.hpp"

namespace oonet
{
	// Copy Operator
	exception & exception::operator=(const exception & r)
	{
		m_file = r.m_file;
		m_line = r.m_line;
		m_desc = r.m_desc;
		m_type = r.m_type;
		return *this;
	}

	// Get a brief report
	string exception::get_html_report(void) const
	{	char _s_line[10] = "";
		string report;
		_snprintf(_s_line, 10, "%lu", m_line);

		report = "<font color=\"#330000\" size=\"5\" style=\"font-weight: bold\">Exception!</font><br>";
		report += m_file + " (";
		report += _s_line;
		report += ")<br><b>";
		report += m_desc + "</b>";

		return report;
	}

	// Get Small report
	string exception::get_report(void) const
	{	char _s_line[10] = "";
		string report;
		_snprintf(_s_line, 10, "%lu", m_line);

		report = m_type + "!\n";
		report += m_file + " (";
		report += _s_line;
		report += ")\n";
		report += m_desc + "\n";

		return report;
	}


};	// !oonet namespace

