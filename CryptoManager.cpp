#include <iostream>
#include <string.h>
#include <cmath>
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


int nonceify(char *input){
    input[0] = 'A';
    char randNum = '0';
    int NONCE = 1234;
    int PUB_KEY1 = 3;
    int PUB_KEY2 = 25777;
    int length = strlen(input);
    for (int i = 0; i < length; i++){
        randNum = input[i] ^ NONCE;
        NONCE = powm(randNum, PUB_KEY1, PUB_KEY2);
    }
    return randNum;
}


cpp_int RSAEncrypt(cpp_int m, cpp_int e, cpp_int n){
    return powm(m, e, n);
}

cpp_int RSADecrypt(cpp_int c, cpp_int d, cpp_int n){
    return powm(c, d, n);
}



vector<cpp_int> generate_rsa_key(cpp_int p, cpp_int q, bool CA = false) {
    cpp_int n = p * q;
    cpp_int z = (p - 1) * (q - 1);
    cpp_int e = 2;
    cpp_int d = 0;

    if(CA) e = 100000000;

    // Find e such that 1 < e < z and gcd(e, z) = 1
    for (; e < z; e++) {
        if (gcd(e, z) == 1) {
            break;
        }
    }

    // Find d
    // Extended Euclidean Algorithm to find d
    d = modinv(e, z);

    vector<cpp_int> keys;
    keys.push_back(n);
    keys.push_back(e);
    keys.push_back(d);

    // Print the keys
    for(int i=0; i<keys.size(); i++){
        std::cout << keys[i] << std::endl;
    }
    return keys;
}
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