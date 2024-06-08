#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

vector<int> crivelloEratostene(int n){
    vector<int> primi;
    vector<bool> numeri(n+1, true);

    numeri[0] = numeri[1] = false;

    for(int i = 2; i <= n; i++){
        if(numeri[i]){
            for(int j = i * i; j <= n; j += i){
                numeri[j] = false;
            }
        }
    }
    for(int i = 2; i <= n; i++){
        if(numeri[i]){
            primi.push_back(i);
        }
    }

    return primi;
}
vector<int> primi = crivelloEratostene(400);

//restituisce true se probabilmente uguali, false se sono sicuramente diverse
bool mcStringEquality(int fileA, int fileB){

    int randomIndex = rand() % primi.size();
    int p = primi[randomIndex];

    int fA = fileA % p;
    int fB = fileB % p;

    if(fA == fB){
        return true;
    }

    return false;
}

int main() {

    srand(time(NULL));

    int fileA = 0b10010110110010011101;
    int fileB = 0b10010110100010011101;

    ofstream file("result.txt");

    for(int i = 0; i < 20; i++)
        file << mcStringEquality(fileA, fileB) << endl;

    cout << fileA << endl;
    cout << fileB << endl;
    cout << fileA - fileB << endl;
    file.close();

    return 0;
}