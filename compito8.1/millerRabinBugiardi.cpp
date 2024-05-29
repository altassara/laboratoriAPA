#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

//restituisce true se probabilmente primo, false altrimenti
bool mcPrimalityTest(int n, int a){
    int s = 0;
    int q = n - 1;

    while(q % 2 == 0){
        s++;
        q = q / 2;
    }

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

    vector<int> n = {561, 1105, 1729, 2465, 2821, 6601, 8911};
    vector<string> files = {"result561.txt", "result1105.txt", "result1729.txt", "result2465.txt", "result2821.txt", "result6601.txt", "result8911.txt"};

    for(int i = 0; i < n.size(); i++){
        ofstream file(files[i]);
        for(int j = 2; j < n[i] - 1; j++){
            if(mcPrimalityTest(n[i], j)){
                file << j << "; ";
            }
        }
        file.close();
    }


    return 0;
}