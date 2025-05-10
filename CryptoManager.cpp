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
vector<cpp_int> generate_rsa_key(cpp_int p, cpp_int q, bool CA = false);




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


std::string nonceify(const char *input, cpp_int NONCE, cpp_int PUB_KEY1, cpp_int PUB_KEY2){
    std::string result = "";
    cpp_int randNum = 0;
    cpp_int length = strlen(input);

    for (int i = 0; i < length; i++){
        randNum = input[i] ^ NONCE;
        NONCE = RSAEncrypt(cpp_int(randNum), PUB_KEY1, PUB_KEY2);
        result += NONCE.str() + " ";
        
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

std::string deNonceify(const char *input, cpp_int NONCE, cpp_int PRIV_KEY, cpp_int PUB_KEY_N){
    std::string result = "";
    cpp_int decryptedVal = 0;
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token){
        cpp_int cipherVal(token);
        decryptedVal = RSADecrypt(cipherVal, PRIV_KEY, PUB_KEY_N);
        char originalChar = static_cast<char>(decryptedVal ^ NONCE);
        NONCE = cipherVal;
        result += originalChar;
    }
    return result;
}

vector<cpp_int> generate_rsa_key(cpp_int p, cpp_int q, bool CA) {
    cpp_int e = 65537;
    if(CA) {
        e = 65537;
        p = cpp_int("9349179016167386125400483845309375997141");
        q = cpp_int("4435879947760023601434372271947629916619");
    }
    cpp_int n = p * q;
    cpp_int z = (p - 1) * (q - 1);
    cpp_int d = 0;

    cout << "Generating RSA keys..." << endl;

        #define RAND_MAX n
        std::srand(std::time(0)); // Seed the random number generator
        // Find e such that 1 < e < z and gcd(e, z) = 1
        for (; e < z; e++) {
            if (gcd(e, z) == 1) {
                break;
        //for (; e < z; e++) {
            while (gcd(e, z) != 1) {
                e = std::rand() % (z - 1) + 1; // Randomly generate e
            }
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

    std::cout << "N: " << keys[0] << std::endl;
    std::cout << "E: " << keys[1] << std::endl;
    std::cout << "D: " << keys[2] << std::endl;

    return keys;
}
