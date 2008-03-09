/*
	Name:		S-Library
	Author:		Paliouras Konstantinos; email:squarious@yahoo.com
	Description:General purpose library. All the things that you can't find somewhere else
	Date:		28 / 8 /2003
	Version:	0.3.0alpha
	Revision:	14 June 2007

	Copyright (C) 2003-2007  Paliouras Konstantinos

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
#if !defined(__SLIB_H_INCLUDED__)
#define __SLIB_H_INCLUDED__

#ifndef __cplusplus
	#error SLib requires C++ compilation (use a .cpp suffix)
#endif // __cplusplus

// Include platform specific
#include "platform.h"
#include "config.h"

#if defined(_MSC_VER)
	#if defined(_DEBUG)
		#if defined(_DLL)
			#pragma comment(lib, "SlibLD.lib")
		#else
			#pragma comment(lib, "SlibD.lib")
		#endif
	#else
		#if defined(_DLL)
			#pragma comment(lib, "SlibL.lib")
		#else
			#pragma comment(lib, "Slib.lib")
		#endif
	#endif // _DEBUG


    #if !defined(_MT)
        #error SLib requires multi-thread library to be loaded!.
    #endif// _MT

	////////////////////////////////
	// Force linking external libraries
	#pragma comment(lib, "ws2_32.lib")	// Winsock 2 library
#endif	// _MSC_VER

//! Slib namespace contains all the class imported by Slib library.
/**
	Everything in Slib library are well organized under this namespace.
	If you want to use anything, be sure to define the namespace ;)
 */
namespace Slib
{
	//! Slib's sub namespace to organize all multi-thread related classes
	namespace MT{};

	//! Slib's sub namespace to organize all http internal implentation
	namespace HTTP{};
};

// Standrad include classes
#include "Exception.h"
#include "StringConverter.h"

#endif // !__SLIB_H_INCLUDED__
