#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

#define RUN 1024
#define ROUND 10
//numero processi affidabili
#define N_PROCESSI 3

using namespace std;

int majCalc(vector<int>);
int tallyCalc(vector<int>);

int main() {

    srand(time(NULL));

    // righe sono i processi affidabili, colonne sono i bit ricevuti dai processi, l'ultima colonna è il malizioso
    vector<vector<int>> processi;
    
    //b[0] rappresenta la scelta del processo 0, b[1] del processo 1, b[2] del processo 2
    vector<int> b(3);

    //soglia
    int T = 3; 

    ofstream resultsFile;
    resultsFile.open("results.txt");

    for(int i = 0; i < RUN; i++){

        processi = {{1, 1, 0, 0},
                    {1, 1, 0, 0},
                    {1, 1, 0, 1}};

        int rounds = 0;

        bool bigBreak = false;

        while (rounds < ROUND){

            rounds++;

            int moneta = rand() % 2;

            for(int j = 0; j < N_PROCESSI; j++){
                int maj = majCalc(processi[j]);
                int tally = tallyCalc(processi[j]);

                if(tally >= T){
                    b[j] = maj;
                    if(moneta == maj){bigBreak = true;};
                }
                else{
                    b[j] = moneta;
                }
            }

            if(bigBreak) break;

            for(int i = 0; i < N_PROCESSI; i++){
                for(int j = 0; j < N_PROCESSI; j++){
                    processi[i][j] = b[j];
                }
            }
            for(int i = 0; i < N_PROCESSI; i++){
                processi[i][N_PROCESSI] = abs(1- b[i]);
            }

            //stampa la matrice
            /*
            for(int i = 0; i < N_PROCESSI; i++){
                for(int j = 0; j < N_PROCESSI + 1; j++){
                cout << processi[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            */

        }

        resultsFile << rounds << endl;
    
    }

    resultsFile.close();

    return 0;
}


int majCalc(vector<int> v){
    int zeri = 0;
    int uni = 0;

    for(int i = 0; i < v.size(); i++){
        if(v[i] == 0) zeri++;
        else uni++;
    }
    if(zeri > uni) return 0;
    
    return 1;
}

int tallyCalc(vector<int> v){
    int zeri = 0;
    int uni = 0;

    for(int i = 0; i < v.size(); i++){
        if(v[i] == 0) zeri++;
        else uni++;
    }
    if(zeri > uni) return zeri;

    return uni;
}