/* 
Iniciando o Projeto LEAD - Modulação de dados

Código para leitura de um arquivo de dados extraídos de um sensor (potênciometro), realizando um(a):
Modulação dos dados extraídos
Média móvel dos dados
Filtro passa baixa dos dados
e por fim, armazenamento dos dados filtrados em um outro arquivo

VERSÃO 3.0 - Código modular, passando os argumentos por ponteiro. Modulação e Média móveis já implementadas
TODO: Finalizar o filtro 
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
  
// Modulaçãp dos dados por um fator constante k

void Modulation(vector<double> &vY, int k) {
    
    for (int i(0); i < vY.size(); i++) {
        vY[i] = k*vY[i];
    }
}

// Média móvel em uma janela arbitrária "period" nos dados, considerando CI nula.

vector<double> MovingAverage(vector<double> &vY, float period){
    
    double moving_average = 0.0;

    vector<double> CI(1,0);
    vY.insert(vY.begin(), 0, 0); // Inserindo o 0 no inicio do vetor, para considerar CI nula.

    for (int i(0); i <= (vY.size()-period); i++) {
        float sum = 0.0;
        for (int j = i; j < (i + period); j++){
            sum += vY[j];
        }
        moving_average = sum / period;    
        vY[i] = moving_average;
    
    return vY;
    }    
}

// Filtro passa-baixa

vector<double> LowPassFilter (vector<double> &vY, double tau, double T){
    
    vector<double> LPF(vY.size(),0);
    
    double alpha = T / (2*tau + T);
    double beta = (T-2*tau)/(T+2*tau);

    for (int k = 1; k < vY.size(); k++) {
        LPF[k] = alpha * (vY[k] - vY[k-1]) - beta * LPF[k-1];
    }
    return LPF;
}

int main() {
    
    vector<double> vX, vY;
    
    readFile("sensor.log",vX, vY);
    Modulation(vY, 2);
    writeFile("modulation.log", vX, vY);
    MovingAverage(vY, 20);
    writeFile("mean.log", vX, vY);
    LowPassFilter(vY, 0.1, 0.02);
    writeFile("lowpass.log", vX, vY);

    return 0;
}



