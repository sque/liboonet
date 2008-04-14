#ifndef TESTS_ESSENTIALS_H_INCLUDED
#define TESTS_ESSENTIALS_H_INCLUDED

#include <iostream>
#include <memory.h>
#include <oonet/oonet.hpp>
#include "Test.h"

using namespace oonet;

// Constant bytes
const oonet::byte c_m = (oonet::byte) 'm';
const oonet::byte c_a = (oonet::byte) 'a';
const oonet::byte c_null = (oonet::byte) '\0';

extern void RegisterTest(Test * pTest);
#endif // TESTS_ESSENTIALS_H_INCLUDED
