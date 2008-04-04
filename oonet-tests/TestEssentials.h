#ifndef TESTS_ESSENTIALS_H_INCLUDED
#define TESTS_ESSENTIALS_H_INCLUDED

#include <iostream>
#include <memory.h>
#include "oonet.hpp"
#include "Test.h"

using namespace oonet;

// Constant bytes
const Byte c_m = (Byte) 'm';
const Byte c_a = (Byte) 'a';
const Byte c_null = (Byte) NULL;

extern void RegisterTest(Test * pTest);
#endif // TESTS_ESSENTIALS_H_INCLUDED
