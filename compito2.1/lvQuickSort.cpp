#include <iostream>
#include <cmath>
#include <time.h>
#include <fstream>

#define N 10000

#define RUNS 100000

using namespace std;

int lvQuickSort(int s[], int left, int right);
long long int valoreMedio(int comparisons[], int n);
long long int deviazioneStandard(int comparisons[], int n);
float chebyshev1(int val);
float chebyshev2(long long int med, long long int dev, int val);


int main() {

    int s[N];
    int comparisons[RUNS];

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        s[i] = rand() % N;
    }

    ofstream comparisonsFile;
    ofstream resultsFile;
    ofstream chebyshevFile;

    comparisonsFile.open("comparisons.txt");
    resultsFile.open("results.txt");
    chebyshevFile.open("chebyshev.txt");

    for(int i = 0; i < RUNS; i++) {
        comparisons[i] = lvQuickSort(s, 0, N - 1);
        comparisonsFile << comparisons[i] << endl;
    }

    long long int med = valoreMedio(comparisons, RUNS);
    long long int dev = deviazioneStandard(comparisons, RUNS);
    resultsFile << med << endl;
    resultsFile << dev << endl;

    float cheb1Double = chebyshev1(2);
    float cheb2Double = chebyshev2(med, dev, 2);

    float cheb1Triple = chebyshev1(3);
    float cheb2Triple = chebyshev2(med, dev, 3);

    cout << "Chebyshev 1 double: " << cheb1Double << endl;
    chebyshevFile << cheb1Double << endl;
    cout << "Chebyshev 2 double: " << cheb2Double << endl;
    chebyshevFile << cheb2Double << endl;

    cout << "Chebyshev 1 triple: " << cheb1Triple << endl;
    chebyshevFile << cheb1Triple << endl;
    cout << "Chebyshev 2 triple: " << cheb2Triple << endl;
    chebyshevFile << cheb2Triple << endl;

    chebyshevFile.close();
    resultsFile.close();
    comparisonsFile.close();

    return 0;
}

int lvQuickSort(int s[], int left, int right) {

    int confronti = 0;
    if (left >= right) return confronti;
    
    int i = left, j = right;
    int pivot = s[rand() % (right - left + 1) + left];

    while (i <= j) {
        while (s[i] < pivot){ confronti++; i++; };
        while (s[j] > pivot){ confronti++; j--; };
        if (i <= j) {
            std::swap(s[i], s[j]);
            i++;
            j--;
        }
    }

    confronti += lvQuickSort(s, left, j);
    confronti += lvQuickSort(s, i, right);

    return confronti;
}

long long int valoreMedio(int comparisons[], int n) {
    long long int med = 0;
    for (int i = 0; i < n; i++) {
        med += comparisons[i];
    }
    return med / n; // 1 / n * med;
}

long long int deviazioneStandard(int comparisons[], int n) {
    long long int var = 0;
    long long int med = valoreMedio(comparisons, n);
    for (int i = 0; i < n; i++) {
        var += pow(comparisons[i] - med, 2);
    }
    var = var / (n - 1);
    return sqrt(var);
}


float chebyshev1(int val) {
    return (1.0 / val);
}

float chebyshev2(long long int med, long long int dev, int val) {
    return pow(dev, 2) / ( pow(val - 1, 2) * pow(med, 2) );
}