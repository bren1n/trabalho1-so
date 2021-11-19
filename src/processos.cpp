#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <chrono>

using namespace std;

void getRow(const int rowIndex, const int columns, vector<int> *row, const vector<vector<int>> *matrix) {
  for (int j = 0; j < columns; j++) {
    int aux = (*matrix)[rowIndex][j];
    row->push_back(aux);
  }
}

void getColumn(const int columnIndex, const int rows, vector<int> *col, const vector<vector<int>> *matrix) {
  for (int i = 0; i < rows; i++) {
    int aux = (*matrix)[i][columnIndex];
    col->push_back(aux);
  }
}

int main(int argc, char *argv[]) {
  int n1, m1, n2, m2, aux, p = atoi(argv[3]), processQuantity;
  vector<vector<int>> matrix1, matrix2, result;
  
  fstream file;
  file.open(argv[1]);  

  file >> n1;
  file >> m1;

  for (int i = 0; i < n1; i++) {
    matrix1.push_back(vector<int>());
    for (int j = 0; j < m1; j++) {
      file >> aux;
      matrix1[i].push_back(aux);
    }
  }

  file.close();

  file.open(argv[2]);  

  file >> n2;
  file >> m2;

  for (int i = 0; i < n2; i++) {
    matrix2.push_back(vector<int>());
    for (int j = 0; j < m2; j++) {
      file >> aux;
      matrix2[i].push_back(aux);
    }
  }

  file.close();

  processQuantity = ceil(double(n1*m2)/double(p));

  for (int i = 0; i < processQuantity; i++) {
    pid_t pid = fork();

    if (pid < 0) {
      cerr << "Erro ao criar o processo" << endl;
      exit(-1);
    } else if (pid == 0) {
      vector <int> row, column;
      vector <string> result;
      int x = 0;

      stringstream fileResult;
      fileResult << "data/process/result_process" << i + 1 << ".txt";

      file.open(fileResult.str(), fstream::out);

      auto begin = chrono::high_resolution_clock::now();

      int rowIndex = int(p*i/m2);
      int columnIndex = (p*i)%m2;

      while (x < p) {
        int multiplicationResult = 0; 
        stringstream resultLine;

        getRow(rowIndex, m1, &row, &matrix1);
        getColumn(columnIndex, n2, &column, &matrix2);

        for (int k = 0; k < m1; k++) {
          multiplicationResult += row[k] * column[k];
        }

        cout << "Resultado: " << multiplicationResult  << " / Processo: " << getpid() << endl;
        
        resultLine << "c" << rowIndex + 1 << columnIndex + 1 << " " << multiplicationResult << endl;
        result.push_back(resultLine.str());

        row.clear();
        column.clear();

        columnIndex++;

        if (columnIndex >= m2) {
          rowIndex++;
          columnIndex = int(p*i/m2);

          if (rowIndex >= n1) {
            break;
          }
        }
        x++;
      }
      
      auto end = chrono::high_resolution_clock::now();
      auto totalTime = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

      file << n1 << ' ' << m2 << endl;
      for (size_t k = 0; k < result.size(); k++) {
        file << result[k];
      }
      file << totalTime << endl;

      exit(0);
    }
  }
  for (int i = 0; i < processQuantity; i++) { 
    wait(NULL);
  }
  
  return 0;
}