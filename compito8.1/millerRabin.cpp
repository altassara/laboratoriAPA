#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

//restituisce true se primo, false altrimenti
bool mcPrimalityTest(int n){
    int s = 0;
    int q = n - 1;

    while(q % 2 == 0){
        s++;
        q = q / 2;
    }

    int a = 2 + rand() % (n - 4);

    long long x = mod_exp(a, q, n);
    x = x % n;

    if(x == 1 || x == n - 1){
        return true;
    }

    while(s - 1 > 0){
        x = pow(x, 2);
        x = x % n;
        if (x == n - 1){
            return true;
        }

        s--;
    }

    return false;

}

int main() {

    srand(time(NULL));

    int n = 561;

    //apri il file result.txt e scrivici sopra
    ofstream file("result.txt");

    for(int i = 0; i < 100; i++){
        file << mcPrimalityTest(n) << endl;
    }

    file.close();

    return 0;
}