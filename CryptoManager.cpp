#include <iostream>
#include <string.h>
#include <cmath>
#include <boost/algorithm/string.hpp>
#include <boost/multiprecision/cpp_int.hpp>


using namespace std;
using namespace boost::multiprecision;

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

