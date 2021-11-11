#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>


using namespace std;


int main(int argc, char *argv[]) {
  int n1, m1, n2, m2, aux;
  vector<vector<int>> matrix1, matrix2, result;
  
  
  // Preenche matrizes antes de multiplicar
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

  //Multiplica matrizes
  auto begin = chrono::high_resolution_clock::now();  
  for (int i = 0; i < n1; i++) {
    result.push_back(vector<int>());
    for (int j = 0; j < m2; j++) {
      result[i].push_back(0);
      for (int k = 0; k < m1; k++) {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  auto end = chrono::high_resolution_clock::now();
  auto totalTime = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
  
  cout << "Tempo de execução: " << totalTime << "ms" << endl;

  //Salva resultado em arquivo
  file.open("data/result_sequencial.txt", fstream::out);
  file << n1 << ' ' << m2 << endl;
  
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < m2; j++) {
      file << 'c' << i+1 << j+1 << ' ' << result[i][j] << endl;
    }
  }

  file << totalTime;

  file.close();

  return 0;
}