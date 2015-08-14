#include "StringsAndDefines.h"

StringsAndDefines * StringsAndDefines::Instance()
{
	static StringsAndDefines instance;

	return &instance;
}


StringsAndDefines::StringsAndDefines()
{
}


StringsAndDefines::~StringsAndDefines()
{
}
