#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <math.h>
#include <chrono>
#include <algorithm>

using namespace std;

/** Inicialização **/
struct listMatriz {
   vector<vector<int>> puzzle;
};


bool algoritmoGuloso(vector<vector<int>> matriz);
bool buscaEmProfundidade(vector<vector<int>> matriz);

bool matrizVisitada(int matrizInt);
vector<listMatriz> retornaFilhos(vector<vector<int>> matriz);
int converteMatrizInt(vector<vector<int>> matriz);
void printMatriz(vector<vector<int>> matriz);

/** Variável global de visitados **/
vector<long double> puzzleslVisitadas;

void clearVisitados(){ puzzleslVisitadas.clear();}
void addVisitados(vector<vector<int>> matriz){ puzzleslVisitadas.push_back(converteMatrizInt(matriz));}

/** Representa a forma final do puzzle convertido em inteiro **/
constexpr int puzzleFinal{ 123456780 };


int main (){

    auto startTime = chrono::steady_clock::now();

    
    //puzzleslVisitadas.reserve(100000);
    vector<vector<int>> puzzleEntrada =  { {1,2,3}, {4,6,0}, {7,5,8} }; 
    //buscaEmProfundidade(puzzleEntrada);
    clearVisitados();
    algoritmoGuloso(puzzleEntrada);

    auto endTime = chrono::steady_clock::now();
    auto diff = endTime - startTime;


    cout << "\n Tempo gasto : "<<chrono::duration <double, milli> (diff).count() << " ms \n";
    
    cin.get();
}

int calculaN(vector<vector<int>> matriz){
    int n[9][2];
    n[0][0] = 2; n[0][1] = 2;
    n[1][0] = 0; n[1][1] = 0;
    n[2][0] = 0; n[2][1] = 1;
    n[3][0] = 0; n[3][1] = 2;
    n[4][0] = 1; n[4][1] = 0;
    n[5][0] = 1; n[5][1] = 1;
    n[6][0] = 1; n[6][1] = 2;
    n[7][0] = 2; n[7][1] = 0;
    n[8][0] = 2; n[8][1] = 1;

    int sum = 0;
    for(int i = 0; i < 3; ++i){
        for(int x = 0; x < 3; ++x){
            int num = matriz[i][x];
            sum += fabs(n[num][0] - i) + fabs(n[num][1] - x);
        }   
    }
    return sum;
}


bool algoritmoGuloso(vector<vector<int>> matriz){
    addVisitados(matriz);
    printMatriz(matriz);
    if(converteMatrizInt(matriz) == puzzleFinal){
        cout<<"\n RESOLVIDO";
        return true;
    }else{
        vector<listMatriz> filhosMatriz = retornaFilhos(matriz);
        int sizeFilhos = filhosMatriz.size();

        int filhosNaoVisitados = 0;
        int indiceMenorN, n = 1000;
        for(int i = 0; i < sizeFilhos; i++){
            if(!matrizVisitada(converteMatrizInt(filhosMatriz[i].puzzle))){
                filhosNaoVisitados++;

                int n0 = calculaN(filhosMatriz[i].puzzle);

                if(n0 <= n){
                    indiceMenorN = i;
                    n = n0;
                }
            }
        }

        if(filhosNaoVisitados == 0){
            return false;
        }else{
            return algoritmoGuloso(filhosMatriz[indiceMenorN].puzzle);
        }
        return false;
    }
}

/** Retorna true caso a matriz esteja no vetor de visitados **/
bool matrizVisitada(int matrizInt){
    int i,retorno = false;
    for(i=0; i<puzzleslVisitadas.size();i++){
        if(puzzleslVisitadas[i] == matrizInt){
            retorno = true;
            break;
        }
    }
    return retorno;
}

/** Realiza o processamento, chamadas recursivas **/
bool buscaEmProfundidade(vector<vector<int>> matriz){
    addVisitados(matriz);
    printMatriz(matriz);
    if(converteMatrizInt(matriz) == puzzleFinal){
        cout<<"\n RESOLVIDO";
        return true;
    }else{
        vector<listMatriz> filhosMatriz = retornaFilhos(matriz);
        int sizeFilhos = filhosMatriz.size(), i;
        for(i = 0; i < sizeFilhos; i++){
            if(!matrizVisitada(converteMatrizInt(filhosMatriz[i].puzzle)))
                 if(buscaEmProfundidade(filhosMatriz[i].puzzle))
                     return true;
        }
        return false;
    }
}


/** Retorna os filhos possíveis para cada casa onde o zero esteja **/
vector<listMatriz> retornaFilhos(vector<vector<int>> matriz){
    vector<listMatriz> filhosMatriz;
    int aux = 0;
    vector<vector<int>> auxMatriz;
    /** auxMatriz é usada para alterações de configuração da matriz original **/
    /** Primeira linha de cada if **/
    auxMatriz = matriz;

    /** Ordem Horário **/
    if(matriz[0][0] == 0){
        auxMatriz[0][0] = auxMatriz[0][1];
        auxMatriz[0][1] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[0][0] = auxMatriz[1][0];
        auxMatriz[1][0] = 0;
        filhosMatriz.push_back({auxMatriz});


    }else if(matriz[0][1] == 0){
        auxMatriz[0][1] = auxMatriz[0][2];
        auxMatriz[0][2] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[0][1] = auxMatriz[1][1];
        auxMatriz[1][1] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[0][1] = auxMatriz[0][0];
        auxMatriz[0][0] = 0;
        filhosMatriz.push_back({auxMatriz});

    }else if(matriz[0][2] == 0){
        auxMatriz[0][2] = auxMatriz[1][2];
        auxMatriz[1][2] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[0][2] = auxMatriz[0][1];
        auxMatriz[0][1] = 0;
        filhosMatriz.push_back({auxMatriz});


    }else if(matriz[1][0] == 0){
        auxMatriz[1][0] = auxMatriz[0][0];
        auxMatriz[0][0] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[1][0] = auxMatriz[1][1];
        auxMatriz[1][1] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[1][0] = auxMatriz[2][0];
        auxMatriz[2][0] = 0;
        filhosMatriz.push_back({auxMatriz});

    }else if(matriz[1][1] == 0){
        auxMatriz[1][1] = auxMatriz[0][1];
        auxMatriz[0][1] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[1][1] = auxMatriz[1][2];
        auxMatriz[1][2] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[1][1] = auxMatriz[2][1];
        auxMatriz[2][1] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[1][1] = auxMatriz[1][0];
        auxMatriz[1][0] = 0;
        filhosMatriz.push_back({auxMatriz});

    }else if(matriz[1][2] == 0){
        auxMatriz[1][2] = auxMatriz[0][2];
        auxMatriz[0][2] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[1][2] = auxMatriz[2][2];
        auxMatriz[2][2] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[1][2] = auxMatriz[1][1];
        auxMatriz[1][1] = 0;
        filhosMatriz.push_back({auxMatriz});

    }else if(matriz[2][0] == 0){
        auxMatriz[2][0] = auxMatriz[1][0];
        auxMatriz[1][0] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[2][0] = auxMatriz[2][1];
        auxMatriz[2][1] = 0;
        filhosMatriz.push_back({auxMatriz});

    }else if(matriz[2][1] == 0){
        auxMatriz[2][1] = auxMatriz[1][1];
        auxMatriz[1][1] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[2][1] = auxMatriz[2][2];
        auxMatriz[2][2] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[2][1] = auxMatriz[2][0];
        auxMatriz[2][0] = 0;
        filhosMatriz.push_back({auxMatriz});

    }else {
        //[2][2]
        auxMatriz[2][2] = auxMatriz[1][2];
        auxMatriz[1][2] = 0;
        filhosMatriz.push_back({auxMatriz});

        auxMatriz = matriz;
        auxMatriz[2][2] = auxMatriz[2][1];
        auxMatriz[2][1] = 0;
        filhosMatriz.push_back({auxMatriz});
    }

    return filhosMatriz;

}

/** Converte uma matriz para um inteiro. Obs: 0 no início é removido **/
int converteMatrizInt(vector<vector<int>> matriz){
    stringstream saida;
    int i,j,retorno;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            saida << matriz [i][j];

    saida >> retorno;
    return retorno;
}

/** Printa matriz na tela **/
void printMatriz(vector<vector<int>> matriz){
    int i,j;
    cout<<"\n.___________.\n";
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            cout<<"| "<<matriz[i][j]<<" ";
        }
        cout<<"|\n";
    }
    cout<<"*-----------*";
    cout<<"\n";
    cout<<"\n Números de matrizes :"<<puzzleslVisitadas.size()<<"\n";
}