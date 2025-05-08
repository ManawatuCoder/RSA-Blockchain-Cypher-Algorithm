#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

int somethingelse()
{
    cout << "Hello, World!" << endl;
    return 0;
}

void testStuff(){
    long p, q, e, d, n, z;
    p = 257; q = 293; n = 75301; z = 24; e = 529; d = 24305;
}

int nonceify(char *input){
    input = "AAA/n";
    char randNum;
    int NONCE = 1234;
    int PUB_KEY1 = 3;
    int PUB_KEY2 = 25777;
    int length = strlen(input);
    for (int i = 0; i < length; i++){
        randNum = input[i] ^ NONCE;
        NONCE = repeatSquare(randNum, PUB_KEY1, PUB_KEY2);
    }
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


long RSAEncrypt(long m, long e, long n){
    int x = pow(m, e);
    return x % n;
}

long RSADecrypt(long c, long d, long n){
    int x = pow(c, d);
    return x % n;
}