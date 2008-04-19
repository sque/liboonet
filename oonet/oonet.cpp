
#include "./oonet.hpp"

namespace oonet
{

	// Version Major
	ushort version_major()
	{	return OONET_VERSION_MAJOR;	}

	// Version Minor
	ushort version_minor()
	{	return OONET_VERSION_MINOR;	}

	// Version Micro
	ushort version_micro()
	{	return OONET_VERSION_MICRO;	}

	// Version Phrase
	std::string version_phrase()
	{	return OONET_VERSION_PHRASE;	}
}; // !oonet namespace
