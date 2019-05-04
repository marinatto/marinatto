/* 
Iniciando o Projeto LEAD - Modulação de dados

Código para leitura de um arquivo de dados extraídos de um sensor do tipo potênciometro
Modulação dos dados extraídos
Armazenamento dos dados modulados em um outro arquivo

VERSÃO 1.1 - Código totalmente modular, passando arquivos e vetores por ponteiros
TODO: Perda de precisão ao reescrever no arquivo de armazenamento
*/

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

// Lê o arquivo e cria um vetor X e Y
// X contém o 1o número de cada linha e Y o segundo número de cada linha

void readFile (const char* file, vector<double> &vX, vector<double> &vY){
    
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

void Modulation(int k, vector<double> &vY){
  for (int i(0); i < vY.size(); i++) {
      vY[i] = k*vY[i];
}
}

int main() {
    
    vector<double> vX, vY;
    
    readFile("sensor.log",vX, vY);
    Modulation(2, vY);
    writeFile("modulation.log", vX, vY);
    return 0;
}



