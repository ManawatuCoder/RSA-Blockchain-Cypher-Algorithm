#include <iostream>
#include <string.h>
#include <cmath>
#include <random>
#include <boost/algorithm/string.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>


using namespace std;
using namespace boost::multiprecision;

cpp_int modinv(cpp_int e, cpp_int z);

int somethingelse()
{
    cout << "Hello, World!" << endl;
    return 0;
}

void testStuff(){
    long p, q, e, d, n, z;
    p = 257; q = 293; n = 75301; z = 24; e = 529; d = 24305;
}


long repeatSquare(long x, long e, long n) {
    int y=1;//initialize y to 1, very important
    while (e > 0) {
        if (( e % 2 ) == 0) {
            x = (x*x) % n;
            e = e/2;
        }
        else {
            y = (x*y) % n;
            e = e-1;
        }
    }
    return y; //the result is stored in y
}


cpp_int RSAEncrypt(cpp_int m, cpp_int e, cpp_int n){
    return powm(m, e, n);
}

cpp_int RSADecrypt(cpp_int c, cpp_int d, cpp_int n){
    return powm(c, d, n);
}


std::string nonceify(const char *input, int NONCE, cpp_int PUB_KEY1, cpp_int PUB_KEY2){
    std::string result = "";
    int randNum = 0;
    int length = strlen(input);

    for (int i = 0; i < length; i++){
        randNum = input[i] ^ NONCE;
        NONCE = RSAEncrypt(cpp_int(randNum), PUB_KEY1, PUB_KEY2).convert_to<int>();
        result += std::to_string(NONCE) + " ";
    }
    return result;
}

// Pointless function to generate CA keys
vector<cpp_int> getCAkeys(){
    return generate_rsa_key(961749037, 961749157, true);
}


cpp_int euclidean_algo(cpp_int x, cpp_int y) {
    cpp_int remainder = 0;

    while (true) {
        remainder = x % y;
        if (remainder == 0) {
            break;
        }
        x = y;
        y = remainder;
    }

    return y;
}

cpp_int extended_euclidean_algo(cpp_int e, cpp_int z) {
    std::vector<cpp_int> x = std::vector<cpp_int>();
    std::vector<cpp_int> y = std::vector<cpp_int>();
    std::vector<cpp_int> w = std::vector<cpp_int>();
    std::vector<cpp_int> k = std::vector<cpp_int>();
    // initialize

    x.emplace_back(1);
    y.emplace_back(0);

    x.emplace_back(0);
    y.emplace_back(1);

    w.emplace_back(z);
    w.emplace_back(e);

    k.emplace_back(0);

    int i = 1;
    while (w.back() != 1) {
        k.emplace_back(w.at(i-1) / w.at(i));
        i++;
        x.emplace_back(x.at(i-2) - (k.at(i-1)*x.at(i-1)));
        y.emplace_back(y.at(i-2) - (k.at(i-1)*y.at(i-1)));
        w.emplace_back(w.at(i-2) - (k.at(i-1)*w.at(i-1)));
    }
    if (y.back() < 0) {
        return y.back() + z;
    }
    return y.back();
}

// Just another name for the extended Euclidean algorithm
cpp_int modinv(cpp_int e, cpp_int z) {
    cpp_int a = z, b = e, x = 0, y = 1;

    while (b != 0) {
        cpp_int q = a / b, r = a % b;
        a = b; b = r;
        cpp_int tmp = x;
        x = y;
        y = tmp - q * y;
    }

    if (a != 1) throw std::invalid_argument("No modular inverse exists");

    return (x < 0) ? x + z : x;
}

std::string deNonceify(const char *input, int NONCE, cpp_int PRIV_KEY, cpp_int PUB_KEY_N){
    std::string result = "";
    int decryptedVal = 0;
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token){
        cpp_int cipherVal(token);
        decryptedVal = RSADecrypt(cipherVal, PRIV_KEY, PUB_KEY_N).convert_to<int>();
        char originalChar = static_cast<char>(decryptedVal ^ NONCE);
        NONCE = cipherVal.convert_to<int>();
        result += originalChar;
    }
    return result;
}

