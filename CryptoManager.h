#ifndef SOMETHINGELSE_H
#define SOMETHINGELSE_H

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

// Function declaration
int somethingelse();
cpp_int RSAEncrypt(cpp_int m, cpp_int e, cpp_int n);
cpp_int RSADecrypt(cpp_int c, cpp_int d, cpp_int n);

#endif // SOMETHINGELSE_H