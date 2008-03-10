/*
	Name:			Object Oriented Library
	Author:			Paliouras Konstantinos; emeil: squarious_(at)_gmail_(dot)_com
	Description:	Started as S-Library providing various stuff and ended as network library.

					A library for talking with network in object oriented style. Using all the
					programmatic techniques that C++ provides in a simple, clean, and cross-platform way.
					It works with almost no external dependency on Windows, GNU/Linux and OSX
	Date:			28 / 8 /2003
	Website:		https://launchpad.net/liboonet
	Version:		0.1
	Revision:		10 Mar 2008

	Copyright (C) 2003-2008  Paliouras Konstantinos

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

//! OONet namespace contains all the class imported by oonet library.
/**
	Everything in oonet library are well organized under this namespace.
	If you want to use anything, be sure to define usage of the namespace ;)
 */
namespace OONet
{
	//! OONet's sub namespace to organize all multi-thread related classes
	namespace MT{};

	//! OONet's sub namespace to organize all http internal implentation
	namespace HTTP{};
};

// Standrad include classes
#include "Exception.h"
#include "StringConverter.h"

#endif // !__OONET_H_INCLUDED__
