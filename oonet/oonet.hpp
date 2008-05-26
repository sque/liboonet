/*
	Name:			Object Oriented Network Library
	Author:			SqUe emeil: squarious_(at)_gmail_(dot)_com
	Description:	Started as S-Library providing various stuff and ended as network library.

					A library for talking with network in object oriented style. Using all the
					programmatic techniques that C++ provides in a simple, clean, and cross-platform way.
					It works with almost no external dependency on Windows, GNU/Linux and OSX
	Date:			28 / 8 /2003
	Website:		http://launchpad.net/liboonet
	Version:		0.1
	Revision:		10 Mar 2008

	" TERMS OF USE "
	READ THIS BEFORE YOU USE THIS LIBRARY

	This library is FREEWARE; you can redistribute it, include it
	at your owns projects, but you can not modify it or sell it.
	This library doesn't prohibit the sale of a software that
	includes it. The author of this library is not bounded to
	distribute the source of this library, and if in someway you
	found the source of this library you can not modify it or
	redistibute it without the individual permission of the author
	of this library. Free is concerned to be only the use of the library,
	and nothing else than the use of this library (like technichal support).

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	Any loss of data that this library may be responsible, the
	only one that can be accused is the user (the man that included this
	library in his program) and never the author of this library.

	IF YOU HAVE ANY PROBLEM WITH THE ABOVE "TERMS OF USE". PLEASE ERASE
	IT FROM YOUR PRIVATE STORAGE MEDIA AND NEVER REDISTRIBUTE INDIVIDUALLY
	OR EMBEDDED IN YOUR OWN SOFTWARE.

	THIS LIBRARY IS ALWAYS ACCOMPANIED WITH THIS "TERMS OF USE". IF
	YOU THINK THAT THIS "TERMS OF USE" IS CORRUPTED PLEASE CONTACT
	THE AUTHOR TO GIVE YOU ANOTHER COPY.

	The author of this library in a NEWER VERSION of this library, than this
	that you now have, CAN CHANGE THIS "TERMS OF USE"; he may also stop
	distributing it as a freeware library and MAKE IT COMMERCIAL, and his
	is NOT BOUNDED TO INFORM ANYONE, that already use a previous version, ABOUT
	THIS CHANGE. The future change of the "Terms of Use" DOES NOT AFFECT
	THIS COPY THAT YOU NOW HAVE, under the term that this copy that you
	have is NOT CORRUPTED.

	FROM THE MOMENT THAT YOU USE THIS LIBRARY YOU AGREE TO THE
	ABOVE "TERMS OF USE".

*/
#if !defined(__OONET_H_INCLUDED__)
#define __OONET_H_INCLUDED__

#ifndef __cplusplus
	#error liboonet requires C++ compilation (use a .cpp suffix)
#endif // __cplusplus

/************************************/
// Library version
#define OONET_VERSION_MAJOR 0
#define OONET_VERSION_MINOR 2
#define OONET_VERSION_MICRO 0
#define OONET_VERSION_PHRASE "beta-2"

/************************************/
// Examine OS
#define OONET_OS_WIN32	1
#define OONET_OS_LINUX	2
#define OONET_OS_UNKNOWN 3

#if defined(WIN32)
	#define OONET_OS	OONET_OS_WIN32
#elif defined(linux)
	#define OONET_OS	OONET_OS_LINUX
#else
	#define	OONET_OS	OONET_OS_UNKNOWN
	#error Unsupported or unknown OS!
#endif

/************************************/
// Unicode - Ansi Abstraction Layer
#define OONET_CHAR_NARROW 1
#define OONET_CHAR_WIDE   2
#if (defined(UNICODE) || defined(_UNICODE))
	#define OONET_CHAR OONET_CHAR_WIDE
#else
	#define OONET_CHAR OONET_CHAR_NARROW
#endif

/************************************
 * Include needed libraries
 */
 // Standard Libraries
#include <stdio.h>
#include <string>
#include <exception>
#include <ctype.h>
#include <time.h>

// Win32 libraries
#if (OONET_OS == OONET_OS_WIN32)
	#include <winsock2.h>
	#include <windows.h>
	#include <process.h>
	#include <tchar.h>
// Linux
#elif (OONET_OS == OONET_OS_LINUX)
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <pthread.h>
	#include <signal.h>
	#include <errno.h>
    #include <semaphore.h>
	#include <wchar.h>
#endif // !OONET_OS

/************************************
 * OS independant -> OS specific macros
 */
// MUTEX definition
#if (OONET_OS == OONET_OS_WIN32)
	#define MUTEX_HANDLE HANDLE					// Mutex handle
	#define SEMAPHORE_HANDLE HANDLE				// Semapore handle
	#define THREAD_HANDLE HANDLE				// Thread handle
	#define THREADTYPE _stdcall					// Thread call_type convention
	#define THREADPROC LPTHREAD_START_ROUTINE	// Thread routine format
	#define THREADPROC_RETURN DWORD				// Thread routin return type
	#define CLOSESOCKET ::closesocket			// Function to close a socket
	#define SOCKLEN int                         // The socklen used by getsockname
	#define SOCKET_HANDLE SOCKET				// The socket handle
#elif (OONET_OS == OONET_OS_LINUX)
	#define MUTEX_HANDLE pthread_mutex_t		// Mutex handle
	#define SOCKET_HANDLE int					// Socket handle
	#define DWORD unsigned long					// realy needed?
	#define SOCKADDR_IN sockaddr_in				// Sockaddress inet
	#define INVALID_SOCKET -1					// Invalid socket
	#define THREAD_HANDLE pthread_t				// Thread handle
	#define THREADTYPE							// Thread call_type convention
	typedef void * (* THREADPROC)(void *);		// Thread routine format
	#define THREADPROC_RETURN void *			// Thread proc return type
	#define CLOSESOCKET ::close					// Function to close socket
	#define SOCKLEN socklen_t                   // The socklen used by getsockname
	#define SEMAPHORE_HANDLE sem_t              // Semaphore handle
#endif

// Create TCHAR Macros and routines for systems that doens't exist
#ifndef _T
    // Text macros
    #if (OONET_CHAR == OONET_CHAR_WIDE)
        #define __ST(quote) L##quote
        #define TCHAR wchar_t
	#else
        #define __ST(quote) quote
        #define TCHAR char
    #endif
    #define _T(x) __ST(x)

    // TCHAR Functions
    #define _snprintf snprintf
	#if (OONET_CHAR == OONET_CHAR_WIDE)
        #define _tprintf wprintf
        #define _sntprintf wprintf
        #define _tmain wmain
    #else
        #define _tprintf printf
        #define _sntprintf snprintf
        #define _tmain main
    #endif
#endif  // !_T


// Externsive debug info on console output
/*#if defined(OONET_DEBUG_LEVEL_1)
    #define OONET_DEBUG_L1(x) _tprintf(_T(" DBGL2: %s"), x)
    #define OONET_DEBUG_L2(x)
#elif defined(OONET_DEBUG_LEVEL_2)
    #define OONET_DEBUG_L1(x) _tprintf(_T(" DBGL1: %s"), x)
    #define OONET_DEBUG_L2(x) _tprintf(_T(" DBGL2: %s"), x)
#else
    #define OONET_DEBUG_L1(x)
    #define OONET_DEBUG_L2(x)
#endif
*/

/*******************************
 * Configuration
 **/
#define OONET_RESOLVER_MAX_ADDRESSES  256	// Maximum addresses resolved by HostResolver
#define OONET_DEFAULT_HTTP_NEWLINE "\r\n"	// Type of new line added at new packets


/*******************************
 * Specific compiler options
 */
#if (OONET_OS == OONET_OS_WIN32) && defined(_MSC_VER)
	// C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
	#pragma warning( disable : 4290 )	// Disable warning

	// Linking directives
	#if defined(_DEBUG)
		#pragma comment(lib, "liboonetD.lib")
	#else
		#pragma comment(lib, "liboonet.lib")
	#endif // _DEBUG

    #if !defined(_MT)
        #error OONet requires multi-thread library to be loaded!.
    #endif// _MT

	////////////////////////////////
	// Force linking external libraries
	#pragma comment(lib, "ws2_32.lib")	// Winsock 2 library
#endif	// _MSC_VER

//! oonet namespace contains all the class imported by oonet library.
/**
	Everything in oonet library are well organized under this namespace.
	If you want to use anything, be sure to define usage of the namespace ;)
 */
namespace oonet
{
	/* Type Definitions */
	using std::wstring;	// Wide string
	using std::string;	// Ansii string

	typedef unsigned char byte;
	typedef unsigned short ushort;
	typedef unsigned long ulong;
	typedef unsigned char uchar;

	/* Version */
	ushort version_major();			//!< Major part of version e.g. "Y.x.x xxxxxxx" Y is major
	ushort version_minor();			//!< Minor part of version e.g. "x.Y.x xxxxxxx" Y is minor
	ushort version_micro();			//!< Micro part of version e.g. "x.x.Y xxxxxxx" Y is micro
	std::string version_phrase();	//!< Description phrase of this version e.g. "x.x.x YYYYYYYYY" Y is description phrase

	//! OONet's sub namespace to organize all multi-thread related classes
	namespace mt
	{
		//! A Constant representing infinity.
		const static ulong Infinity = -1;
	};

	//! OONet's sub namespace to organize all http internal implentation
	namespace http{};
};

// Standrad include classes
#include "./exception.hpp"

#endif // !__OONET_H_INCLUDED__
