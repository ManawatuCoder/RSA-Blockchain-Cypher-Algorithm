#ifndef SOMETHINGELSE_H
#define SOMETHINGELSE_H

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using namespace std;

// Function declaration
int somethingelse();
cpp_int RSAEncrypt(cpp_int m, cpp_int e, cpp_int n);
cpp_int RSADecrypt(cpp_int c, cpp_int d, cpp_int n);
cpp_int modinv(cpp_int e, cpp_int z);
cpp_int extended_euclidean_algo(cpp_int e, cpp_int z);
vector<cpp_int> generate_rsa_key(cpp_int p, cpp_int q, bool CA = false);
vector<cpp_int> getCAkeys();
std::string nonceify(const char *input, cpp_int NONCE, cpp_int PUB_KEY1, cpp_int PUB_KEY2);
std::string deNonceify(const char *input, cpp_int NONCE, cpp_int PRIV_KEY, cpp_int PUB_KEY_N);

#endif // SOMETHINGELSE_H