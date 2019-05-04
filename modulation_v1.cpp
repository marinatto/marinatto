/* 
Iniciando o Projeto LEAD - Modulação de dados

Código para leitura de um arquivo de dados extraídos de um sensor do tipo potênciometro
Modulação dos dados extraídos
Armazenamento dos dados modulados em um outro arquivo

VERSÃO 1 - Parcialmente modular
TODO: Passar arquivos e constantes por parâmetros 
TODO2: Perda de precisão ao reescrever no arquivo de armazenamento
*/

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

vector<double> vX, vY;

// Função criada para ler os arquivos

void readFile (){
    
    double x, y;
    ifstream inputFile("sensor.log");
    
    while (inputFile >> x >> y) {
        vX.push_back(x);
        vY.push_back(y);
    }
    for (int i(0); i < vX.size(); i++) {
      cout << vX[i] << ", " << vY[i] << endl;
    }
}
  
void Modulation(){
  for (int i(0); i < vX.size(); i++) {
      vY[i] = 2*vY[i];
}
}

void writeFile(){
    
    ofstream outputFile;
    outputFile.open("output.log");

    for (int i(0); i < vX.size(); i++){
        outputFile << vX[i] << " " << vY[i] << endl;
    }
    outputFile.close();
}

int main() {
    
    readFile();
    Modulation();
    writeFile();
    return 0;
}



