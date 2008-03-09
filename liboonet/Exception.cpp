/**
@file Exception.cpp
@brief Implementation of the Exception class.
 */
#include "./Exception.h"

namespace Slib
{
	// Copy Operator
	Exception & Exception::operator=(const Exception & r)
	{
		File = r.File;
		Line = r.Line;
		Desc = r.Desc;
		ExceptionType = r.ExceptionType;
		return *this;
	}

	// Get a brief report
	string Exception::getHTMLReport(void) const
	{	char sLine[10] = "";
		string report;
		_snprintf(sLine, 10, "%lu", Line);

		report = "<font color=\"#330000\" size=\"5\" style=\"font-weight: bold\">Exception!</font><br>";
		report += File + " (";
		report += sLine;
		report += ")<br><b>";
		report += Desc + "</b>";

		return report;
	}

	// Get Small report
	string Exception::getReport(void) const
	{	char sLine[10] = "";
		string report;
		_snprintf(sLine, 10, "%lu", Line);

		report = ExceptionType + "!\n";
		report += File + " (";
		report += sLine;
		report += ")\n";
		report += Desc + "\n";

		return report;
	}


};	//! Slib namespace

