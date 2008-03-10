/*************************************************************************
	Project: 	S-lib
	File:		platform.h
	Descr:		This file is an disambigution for OS-specific libraries
	Version:	0.3.x
	Revision:	17 September 2006
*/
#ifndef OONET_PLATFORM_H_DEFINED
#define OONET_PLATFORM_H_DEFINED

/************************************/
// Examine OS
#define OONET_OS_WIN32	1
#define OONET_OS_LINUX	2
#define OONET_OS_UNKNOWN 3
#define OONET_CHAR_NARROW 1
#define OONET_CHAR_WIDE   2

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

// WIN_32 libraries
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
#endif // !SLIB_OS_LINUX

/************************************
 * OS independant -> OS specific macros
 */
// MUTEX definition
#if (OONET_OS == OONET_OS_WIN32)
	#define MUTEX HANDLE						// Mutex handle
	#define SEMAPHORE HANDLE                    // Semapore handle
	#define THREAD HANDLE						// Thread handle
	#define THREADTYPE _stdcall					// Thread call_type convention
	#define THREADPROC LPTHREAD_START_ROUTINE	// Thread routine format
	#define THREADPROC_RETURN DWORD				// Thread routin return type
	#define CLOSESOCKET ::closesocket			// Function to close a socket
	#define SOCKLEN int                         // The socklen used by getsockname
#elif (OONET_OS == OONET_OS_LINUX)
	#define MUTEX pthread_mutex_t				// Mutex handle
	#define SOCKET int							// Socket handle
	#define DWORD unsigned long					// realy needed?
	#define SOCKADDR_IN sockaddr_in				// Sockaddress inet
	#define INVALID_SOCKET -1					// Invalid socket
	#define THREAD pthread_t					// Thread handle
	#define THREADTYPE							// Thread call_type convention
	typedef void * (* THREADPROC)(void *);		// Thread routine format
	#define THREADPROC_RETURN void *			// Thread proc return type
	#define CLOSESOCKET ::close					// Function to close socket
	#define SOCKLEN socklen_t                   // The socklen used by getsockname
	#define SEMAPHORE sem_t                     // Semaphore handle
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
#endif  //! _T


// Externsive debug info on console output
//#define SLIB_DEBUG_LEVEL_2
#if defined(OONET_DEBUG_LEVEL_1)
    #define OONET_DEBUG_L1(x) _tprintf(_T(" DBGL2: %s"), x)
    #define OONET_DEBUG_L2(x)
#elif defined(OONET_DEBUG_LEVEL_2)
    #define OONET_DEBUG_L1(x) _tprintf(_T(" DBGL1: %s"), x)
    #define OONET_DEBUG_L2(x) _tprintf(_T(" DBGL2: %s"), x)
#else
    #define OONET_DEBUG_L1(x)
    #define OONET_DEBUG_L2(x)
#endif

namespace OONet
{
	/* Type Definitions */
	using std::wstring;	// Wide string
	using std::string;	// Ansii string

	typedef unsigned char Byte;
	typedef unsigned short ushort;
	typedef unsigned long ulong;
	typedef unsigned char uchar;

	namespace MT
	{
		//! A Constant representing infinity.
		const static ulong Infinity = -1;
	};
};

/** Specific compiler options */
#if (OONET_OS == OONET_OS_WIN32) && defined(_MSC_VER)
	// C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
	#pragma warning( disable : 4290 )	// Disable warning
#endif
#endif //!  OONET_PLATFORM_H_DEFINED
