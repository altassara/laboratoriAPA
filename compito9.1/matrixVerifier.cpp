#include <iostream>
#include <fstream> 
#include <vector>
#include <ctime>

#define DIM 10
#define RUNS 100

using namespace std;

int* prodottoMatriciVettore(int** mat, int n, int m, int* v, int lungVett) {
    if (n != lungVett) {
        cout << "Errore: dimensioni non compatibili" << endl;
        return nullptr;
    }

    int* r = new int[n];
    for (int i = 0; i < n; i++) {
        r[i] = 0;
        for (int j = 0; j < m; j++) {
            r[i] += mat[i][j] * v[j];
        }
    }
    return r;
}

int** prodottoMatriceMatrice(int** mat1, int n1, int m1, int** mat2, int n2, int m2) {
    if (m1 != n2) {
        cout << "Errore: dimensioni non compatibili" << endl;
        return nullptr;
    }

    int** r = new int*[n1];
    for (int i = 0; i < n1; i++) {
        r[i] = new int[m2];
        for (int j = 0; j < m2; j++) {
            r[i][j] = 0;
            for (int k = 0; k < m1; k++) {
                r[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return r;
}

int** generaMatr(int n, int m) {
    int** mat = new int*[n];
    for (int i = 0; i < n; i++) {
        mat[i] = new int[m];
        for (int j = 0; j < m; j++) {
            mat[i][j] = rand() % 5 - 2;
        }
    }
    return mat;
}

//restituisce 1 se sono probabilmente uguali, 0 altrimenti
bool mcMatrixMultiplicationVerifier(int** A, int** B, int** C, int n) {
    int* r = new int[n];
    for (int i = 0; i < n; i++) {
        r[i] = rand() % 2;
    }
    int* s = prodottoMatriciVettore(B, n, n, r, n);
    int* t = prodottoMatriciVettore(A, n, n, s, n);

    int* u = prodottoMatriciVettore(C, n, n, r, n);

    //confronto t e u
    for (int i = 0; i < n; i++) {
        if (t[i] != u[i]) {
            return false;
        }
    }

    return true;
}

int main() {

    srand(time(NULL));

    vector<string> files = {"resultK5.txt", "resultK10.txt", "resultK20.txt"};
    vector<int> k = {5, 10, 20};

    int** matrA = generaMatr(DIM, DIM);

    int** matrB = generaMatr(DIM, DIM);

    int** matrC = prodottoMatriceMatrice(matrA, DIM, DIM, matrB, DIM, DIM);

    matrC[rand() % DIM][rand() % DIM] += 1;

    for(int i = 0; i < k.size(); i++){

        ofstream file(files[i]);

        for(int j = 0; j < RUNS; j++){

            int** matrB = generaMatr(DIM, DIM);

            int** matrC = prodottoMatriceMatrice(matrA, DIM, DIM, matrB, DIM, DIM);

            matrC[rand() % DIM][rand() % DIM] += 1;

            int uguali = 0;
            int res;
            for (int z = 0; z < k[i]; z++) {
                if (res = mcMatrixMultiplicationVerifier(matrA, matrB, matrC, DIM)) {
                    uguali++;
                }
                //file << res << "; ";
            }
            //file << endl;
            int result = (uguali == k[i]) ? 1 : 0;
            file << result << endl;
        }
        file.close();
    }



    return 0;
}