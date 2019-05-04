/* 
Iniciando o Projeto LEAD - Modulação de dados

Código para leitura de um arquivo de dados extraídos de um sensor (potênciometro), realizando um(a):
Modulação dos dados extraídos
Média móvel dos dados
Filtro passa baixa dos dados
e por fim, armazenamento dos dados filtrados em um outro arquivo

VERSÃO 2.0 - Código modular, passando os argumentos por ponteiro
TODO: Considerar a condição inicial = 0 
TODO2: Perda de precisão ao reescrever no arquivo de armazenamento
*/

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

// Lê o arquivo e cria um vetor X e Y
// X contém o 1o número de cada linha e Y o segundo número de cada linha

void readFile (const char* file, vector<double> &vX, vector<double> &vY) {
    
    double x, y;
    ifstream inputFile(file);
    
    while (inputFile >> x >> y) {
        vX.push_back(x);
        vY.push_back(y);
    }
    for (int i(0); i < vX.size(); i++) {
        cout << vX[i] << ", " << vY[i] << endl;
    }
}

// Escreve os dados no arquivo de armazenamento

void writeFile(const char* file, vector<double> &vX, vector<double> &vY){
    
    ofstream outputFile;
    outputFile.open(file);

    for (int i(0); i < vX.size(); i++){
        outputFile << vX[i] << " " << vY[i] << endl;
    }
    outputFile.close();
}
  
// Modula os dados por um fator constante k

void Modulation(int k, vector<double> &vY) {
    for (int i(0); i < vY.size(); i++) {
        vY[i] = k*vY[i];
    }
}

void movingAverage(vector<double> &vY, float period){
    
    double moving_average = 0.0;

    for (int i(0); i <= (vY.size()-period); i++) {
        float sum = 0.0;
        for (int j = i; j < (i + period); j++){
            sum += vY[j];
        }
        moving_average = sum / period;    
        vY.push_back(moving_average);
    }    
}

int main() {
    
    vector<double> vX, vY;
    
    readFile("sensor.log",vX, vY);
    Modulation(2, vY);
    movingAverage(vY, 3);
    writeFile("modulation.log", vX, vY);
    writeFile("mean.log", vX, vY);
    return 0;
}



