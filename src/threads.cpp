#include <iostream>
#include <pthread.h>
#include <chrono>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;


typedef struct threadArgs {
  int i;
  int n1;
  int n2;
  int m1;
  int m2;
  int p;
  vector<vector<int>> matrix1;
  vector<vector<int>> matrix2;
} thargs_t;


void getRow(const int rowIndex, const int columns, vector<int> *row, const vector<vector<int>> *matrix) {
  for (int j = 0; j < columns; j++)
  {
    int aux = (*matrix)[rowIndex][j];
    row->push_back(aux);
  }
}

void getColumn(const int columnIndex, const int rows, vector<int> *col, const vector<vector<int>> *matrix) {
  for (int i = 0; i < rows; i++)
  {
    int aux = (*matrix)[i][columnIndex];
    col->push_back(aux);
  }
}

void *multiply(void *thArgs) {
  threadArgs *threadMain = ((thargs_t *)thArgs);

  stringstream fileResult;
  fstream file;

  fileResult << "data/thread/result_thread" << threadMain->i+1 << ".txt";

  file.open(fileResult.str(), fstream::out);

  auto begin = chrono::high_resolution_clock::now();

  vector<int> row, column;
  vector<string> result;
  int count = 0;

  int rowIndex = int(threadMain->p * threadMain->i / threadMain->m2);
  int columnIndex = (threadMain->p * threadMain->i) % threadMain->m2;

  while (count < threadMain->p)
  {
    stringstream resultRow;
    int multiplicationResult = 0;

    getRow(rowIndex, threadMain->m1, &row, &threadMain->matrix1);
    getColumn(columnIndex, threadMain->n2, &column, &threadMain->matrix2);

    for (int k = 0; k < threadMain->m1; k++)
    {
      multiplicationResult += row[k] * column[k];
    }

    resultRow << "c" << rowIndex + 1 << columnIndex + 1 << " " << multiplicationResult << endl;
    result.push_back(resultRow.str());

    row.clear();
    column.clear();

    columnIndex++;
    if (columnIndex >= threadMain->m2)
    {
      rowIndex++;
      columnIndex = int(threadMain->p * threadMain->i / threadMain->m2);
      if (rowIndex >= threadMain->n1)
      {
        break;
      }
    }
    count++;
  }

  auto end = chrono::high_resolution_clock::now();
  auto totalTime = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

  file << threadMain->n1 << ' ' << threadMain->m2 << endl;
  for (int k = 0; k < (int) result.size(); k++)
  {
    file << result[k];
  }
  file << totalTime << endl;

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
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

  pthread_t threads[processQuantity];
  thargs_t argsList[processQuantity];
  void *threadReturn;

  for (int i = 0; i < processQuantity; i++)
  {
    argsList[i].i = i;

    argsList[i].p = p;
    argsList[i].n1 = n1;
    argsList[i].n2 = n2;
    argsList[i].m1 = m1;
    argsList[i].m2 = m2;

    argsList[i].matrix1 = matrix1;
    argsList[i].matrix2 = matrix2;
    pthread_create(&threads[i], NULL, multiply, &argsList[i]);
  }

  for (int i = 0; i < processQuantity; i++)
  {
    pthread_join(threads[i], &threadReturn);
  }

  return 0;
}