/* 
Iniciando o Projeto LEAD - Modulação de dados

Código para leitura de um arquivo de dados extraídos de um sensor (potênciometro), realizando um(a):
Modulação dos dados extraídos
Média móvel dos dados
Filtro passa baixa dos dados
e por fim, armazenamento dos dados filtrados em um outro arquivo

VERSÃO 3.2 - Código modular, passando os argumentos por ponteiro. Modulação e Média móveis já implementadas
TODO: Finalizar o filtro 
*/

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

// Lê o arquivo e cria um vetor X e Y
// X contém o primeiro número de cada linha e Y o segundo número de cada linha

void readFile (const char* file, vector<double> &vX, vector<double> &vY) {
    
    double x, y;
    ifstream inputFile(file);
    
    while (inputFile >> x >> y) {
        vX.push_back(x);
        vY.push_back(y);
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
  
// Modulação dos dados por um fator constante k

vector<double> Modulation(vector<double> &vY, int k) {
    
    for (int i(0); i < vY.size(); i++) {
        vY[i] = k*vY[i];
    }
    return vY;
}

// Média móvel em uma janela arbitrária "period" nos dados, considerando CI nula.

vector<double> MovingAverage(vector<double> &vY, float period){
    
    double moving_average = 0.0;

    vector<double> CI(period-1,0);
    vY.insert(vY.begin(), CI.begin(), CI.end()); // Inserindo o 0 no inicio do vetor, para considerar CI nula.

    for (int i(0); i <= (vY.size()-period); i++) {
        float sum = 0.0;
        for (int j = i; j < (i + period); j++){
            sum += vY[j];
        }
        moving_average = sum / period;    
        vY[i] = moving_average;
    
    }
    return vY;    
}

// Filtro passa-baixa, com cte do tempo = tau e periodo = T

vector<double> LowPassFilter (vector<double> &vY, float tau, float T, vector<double> &LPF){

    float alpha = T / (2*tau + T);
    float beta = (T-2*tau)/(T+2*tau);

    LPF[0] = alpha*vY[0]; // O primeiro termo depende apenas da entrada inicial

    for (int k = 1; k < vY.size(); k++) {
        LPF[k] = (alpha * (vY[k] - vY[k-1]) - beta * LPF[k-1]);
    }
    return LPF; 
}

int main() {
    
    vector<double> vX, vY;
    readFile("sensor.log", vX, vY);
    
    vector<double> LPF(vY.size(),0);
    //Modulation(vY, 2);
    //writeFile("modulation.log", vX, vY);
    //MovingAverage(vY, 20);
    //writeFile("mean.log", vX, vY);
    LowPassFilter(vY, 0.1, 0.02, LPF);
    writeFile("lowpass.log", vX, LPF);

    return 0;
}



