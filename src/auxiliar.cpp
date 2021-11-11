#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


int main(int argc, char *argv[]) {
  //Armazena dimensões
  int n1 = atoi(argv[1]);
  int m1 = atoi(argv[2]);
  int n2 = atoi(argv[3]);
  int m2 = atoi(argv[4]);

  // Gera elementos aleatórios
  vector<vector<int>> matrix1;

  srand((int) time(0));
  for (int i = 0; i < n1; i++) {
    matrix1.push_back(vector<int>());
    for (int j = 0; j < m1; j++) {
      matrix1[i].push_back(rand() % 10 + 1);
    }
  }

  vector<vector<int>> matrix2;

  for (int i = 0; i < n2; i++) {
    matrix2.push_back(vector<int>());
    for (int j = 0; j < m2; j++) {
      matrix2[i].push_back(rand() % 10 + 1);
    }
  }
  
  //Armazena matrizes nos arquivos
  fstream file;
  file.open("data/m1.txt", fstream::out);
  file << n1 << ' ' << m1 << endl;

  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < m1; j++) {
      file << matrix1[i][j] << (j < m1 - 1 ? ' ' : '\n');
    }
  }

  file.close();

  file.open("data/m2.txt", fstream::out);
  file << n2 << ' ' << m2 << endl;

  for (int i = 0; i < n2; i++) {
    for (int j = 0; j < m2; j++) {
      file << matrix2[i][j] << (j < m2 - 1 ? ' ' : '\n');
    }
  }

  file.close();

  return 0;
}