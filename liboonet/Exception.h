#ifndef OONET_EXCEPTION_H_DEFINED
#define OONET_EXCEPTION_H_DEFINED

#include "OONet.h"

namespace OONet
{
	// Exception Definitions
	#define OONET_THROW_EXCEPTION(exception, desc) \
		throw (exception (__FILE__, __LINE__, desc ))

	#define OONET_DECLARE_EXCEPTION(name) \
		class name : public Exception { \
		public : name (const string _file, long _line, const string _desc) \
		: Exception(_file, _line, _desc, #name) {} }

	#define OONET_ASSERT(exp) \
		if ( !(exp) ) OONET_THROW_EXCEPTION(OONet::ExceptionAssertationFailed, "An assertation failed!");

	//! OONet's exceptions base class
	/**
		The base class of exceptions used in oonet. The
		Exception is inherited from std::exception so
		that exceptions are catchable from generic catchers
		outside oonet.
	*/
	class Exception : public std::exception
	{
	private:
		//! The file where the error was generated.
		string File;

		//! The line at the file where the error was generated.
		long Line;

		//! The description of Exception
		string Desc;

		//! The exception type
		string ExceptionType;
	public:

		//! Default constructor
		/**
		@param _file The filename where exception was raised.
		@param _line The line of source file where exception was raised.
		@param _desc A description of exception.
		@param _type The type of exception
		*/
		inline Exception(const string & _file,
			long _line,
			const string & _desc,
			const string & _type = "Exception"
			)
			: File(_file),
			Line(_line),
			Desc(_desc),
			ExceptionType(_type)
		{}

		//! Destructor
		inline virtual ~Exception(void) throw(){}

		//! Copy constructor
		inline Exception(const Exception & r)
		{	operator=(r);	}

		//! Copy operator
		Exception & operator=(const Exception & r);

		//! Get description of exception
		inline const string & getDescription() const
		{	return Desc;	}

		//! Get line of source file where exception was raised
		inline long getLine(void) const
		{	return Line;	}

		//! Get name of source file where exception was raised
		inline const string & getFile(void) const
		{	return File;	}

		//! Get the type of exception
		inline const string & getType(void) const
		{	return ExceptionType;	}

		//! Create a brief report of exception in HTML format
		string getHTMLReport(void) const;

		//! Create a brief report in raw text format
		string getReport(void) const;
	};

	//////////////////////////////////////////////////
	// Standard Exceptions Definitions
	//! Exception when something couldn't be found.
	OONET_DECLARE_EXCEPTION(ExceptionNotFound);
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
};	// OONet namespace

#endif // !OONET_EXCEPTION_H_DEFINED
