# Trabalho 1 - Processos e threads

#Como compilar
ˋˋˋ
g++ -Wall -o auxiliar.o src/auxiliar.cpp
g++ -Wall -o sequencial.o src/auxiliar.cpp
g++ -Wall -o processos.o src/auxiliar.cpp
g++ -Wall -o threads.o src/auxiliar.cpp -pthread
ˋˋˋ

#Como executar
ˋˋˋ
./auxiliar.o <n1> <m1> <n2> <m2>
./sequencial.o <arquivo_1> <arquivo_2>
./processos.o <arquivo_1> <arquivo_2> <p>
./processos.o <arquivo_1> <arquivo_2> <p>
ˋˋˋ
