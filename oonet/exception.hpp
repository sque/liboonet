#ifndef OONET_EXCEPTION_HPP_INCLUDED
#define OONET_EXCEPTION_HPP_INCLUDED

#include "./oonet.hpp"

namespace oonet
{
	// Exception Definitions
	#define OONET_THROW_EXCEPTION(exc, desc) \
	throw (exc (__FILE__, __LINE__, desc ))

	#define OONET_DECLARE_EXCEPTION(name) \
		class name : public oonet::exception { \
		public : name (const string & _file, long _line, const string & _desc) \
		: exception(_file, _line, _desc, #name) {} }

	#define OONET_ASSERT(exp) \
		if ( !(exp) ) OONET_THROW_EXCEPTION(oonet::ExceptionAssertationFailed, "An assertation failed!");

	//! OONet's exceptions base class
	/**
		The base class of exceptions used in oonet. The
		Exception is inherited from std::exception so
		that exceptions are catchable from generic catchers
		outside oonet.
	*/
	class exception : public std::exception
	{
	private:
		//! The file where the error was generated.
		string m_file;

		//! The line at the file where the error was generated.
		long m_line;

		//! The description of Exception
		string m_desc;

		//! The exception type
		string m_type;
	public:

		//! Default constructor
		/**
		@param _file The filename where exception was raised.
		@param _line The line of source file where exception was raised.
		@param _desc A description of exception.
		@param _type The type of exception
		*/
		inline exception(const string & _file,
			long _line,
			const string & _desc,
			const string & _type = "Exception"
			)
			: m_file(_file),
			m_line(_line),
			m_desc(_desc),
			m_type(_type)
		{}

		//! Destructor
		inline virtual ~exception(void) throw(){}

		//! Copy constructor
		inline exception(const exception & r)
		{	operator=(r);	}

		//! Copy operator
		exception & operator=(const exception & r);

		//! Get description of exception
		inline const string & get_description() const
		{	return m_desc;	}

		//! Get line of source file where exception was raised
		inline long get_line(void) const
		{	return m_line;	}

		//! Get name of source file where exception was raised
		inline const string & get_file(void) const
		{	return m_file;	}

		//! Get the type of exception
		inline const string & get_type(void) const
		{	return m_type;	}

		//! Create a brief report of exception in HTML format
		string get_html_report(void) const;

		//! Create a brief report in raw text format
		string get_report(void) const;
	};

	//////////////////////////////////////////////////
	// Standard Exceptions Definitions
	//! Exception when something couldn't be found.
	OONET_DECLARE_EXCEPTION(ExceptionNotFound);
	//! Exception raised when mutex locking failed
	OONET_DECLARE_EXCEPTION(ExceptionLockError);
	//! Exception raised when access to a resource was denied.
	OONET_DECLARE_EXCEPTION(ExceptionAccessDenied);
	//! Exception raised when an entry or object already exist in a container.
	OONET_DECLARE_EXCEPTION(ExceptionAlreadyExists);
	//! Exception raised when an argument of function didn't have the excpected format.
	OONET_DECLARE_EXCEPTION(ExceptionWrongArgument);
	//! Exception raised when a memory allocation failed
	OONET_DECLARE_EXCEPTION(ExceptionBadAllocation);
	//! Exception raised when the pending operation reached time out period.
	OONET_DECLARE_EXCEPTION(ExceptionTimeOut);
	//! Exception raised when an assertation failed
	OONET_DECLARE_EXCEPTION(ExceptionAssertationFailed);
	//! Exception raised when the specified feature isn't implemented yet.
	OONET_DECLARE_EXCEPTION(ExceptionUnimplemented);
	//! Exception raised when the function encountered a system error
	OONET_DECLARE_EXCEPTION(ExceptionSystemError);
	//! Exception raised when requested string convertion is unsupported.
	OONET_DECLARE_EXCEPTION(ExceptionConvertionUnsupported);
	//! Exception raised when a specific feature is missing in current platform.
	OONET_DECLARE_EXCEPTION(ExceptionNotSupported);
	//! Exception raised when the specified operation was interupted.
    OONET_DECLARE_EXCEPTION(ExceptionInterrupted);
    //! Exception raised when the resource is busy by another thread.
	OONET_DECLARE_EXCEPTION(ExceptionResourceBusy);
	//! Exception raised when the specified request, may be served later.
	OONET_DECLARE_EXCEPTION(ExceptionTryAgain);
	//! Exception raised when asked to connect while already connected
	OONET_DECLARE_EXCEPTION(ExceptionAlreadyConnected);
	//! Exception raised when asked to perform a transmit but there is no connection yet.
	OONET_DECLARE_EXCEPTION(ExceptionNotConnected);
};	// oonet namespace

#endif // !OONET_EXCEPTION_HPP_INCLUDED
