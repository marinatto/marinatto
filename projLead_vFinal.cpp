/* 
Iniciando o Projeto LEAD - Tratamento de Dados

-----------------------------------------------------------------------------------------------------

Código para leitura de um arquivo de dados extraídos de um sensor (potênciometro), realizando um(a):
Modulação dos dados extraídos
Média móvel dos dados
Filtro passa baixa dos dados
e por fim, armazenamento dos dados filtrados em um outro arquivo

-----------------------------------------------------------------------------------------------------

VERSÃO FINAL - Código modular, passando os argumentos por ponteiro. 
Modulação, Média Móvel e Filtro Passa-baixa implementados
*/

#include <fstream>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

// Lê o arquivo e cria um vetor X e Y
// X contém os números da primeira coluna e Y os números da segunda coluna.

void readFile (const char* file, vector<double> &vX, vector<double> &vY) {
    
    double x, y;
    ifstream inputFile(file);
    
    while (inputFile >> x >> y) {
        vX.push_back(x);
        vY.push_back(y);
    }
}

// Escreve os dados no arquivo de armazenamento, mantendo o padrão do arquivo lido.

void writeFile(const char* file, vector<double> &vX, vector<double> &vY){
    
    ofstream outputFile;
    outputFile.open(file);

    for (int i(0); i < vX.size(); i++){
        outputFile << vX[i] << " " << vY[i] << endl;
    }

    outputFile.close();
}
  
// Modulação dos dados por um fator constante k

vector<double> Modulation(vector<double> &vY_M, vector<double> &vY, int k) {
    
    for (int i(0); i < vY.size(); i++) {
        vY_M[i] = k*vY[i];
    }
    return vY_M;
}

// Média móvel em uma janela arbitrária "period" nos dados, considerando CI nula.

vector<double> MovingAverage(vector<double> &vY_AVG, float period){
    
    double moving_average = 0.0;

    vector<double> CI(period-1,0);
    vY_AVG.insert(vY_AVG.begin(), CI.begin(), CI.end()); // Inserindo o 0 no inicio do vetor, para considerar CI nula.

    for (int i(0); i <= (vY_AVG.size()-period); i++) {
        float sum = 0.0;
        for (int j = i; j < (i + period); j++){
            sum += vY_AVG[j];
        }
        moving_average = sum / period;    
        vY_AVG[i] = moving_average;
    
    }
    return vY_AVG;    
}

// Filtro passa-baixa, com cte do tempo = tau e periodo = T

vector<double> LowPassFilter (vector<double> &LPF, vector<double> &vY, float tau, float T) {

    float alpha = T / (2*tau + T);
    float beta = (T-2*tau)/(T+2*tau);

    LPF[0] = alpha*vY[0]; // O primeiro termo depende apenas da entrada inicial

    for (int k = 1; k < vY.size(); k++) {
        LPF[k] = (alpha * (vY[k] + vY[k-1]) - beta * LPF[k-1]);
    }
    return LPF; 
}

int main() {
    
    vector<double> vX, vY;
    readFile("sensor.log", vX, vY);

    //Vetores criados para armazenar os valores pós-processamento dos dados do sensor.
    
    vector<double> LPF(vX.size(),0);
    vector<double> vY_M(vX.size(),0);
    vector<double> vY_AVG = vY;

    //Chamando os processamentos e armazenando em log files.

    Modulation(vY_M, vY, 2);
    writeFile("modulation.log", vX, vY_M);
    MovingAverage(vY_AVG, 20);
    writeFile("mean.log", vX, vY_AVG);
    LowPassFilter(LPF, vY, 0.1, 0.02);
    writeFile("lowpass.log", vX, LPF);
   
    

    return 0;
}