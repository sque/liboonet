#ifndef TESTS_ESSENTIALS_H_INCLUDED
#define TESTS_ESSENTIALS_H_INCLUDED

#include <iostream>
#include <memory.h>
#include "oonet.hpp"
#include "Test.h"

using namespace oonet;

// Constant bytes
const byte c_m = (byte) 'm';
const byte c_a = (byte) 'a';
const byte c_null = (byte) NULL;

extern void RegisterTest(Test * pTest);
#endif // TESTS_ESSENTIALS_H_INCLUDED
