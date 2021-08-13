/*
Экспериментальное определение степени ассоциативности кэш-памяти.

gcc main.cpp -o main -lstdc++ -msse2 -O1 -Wall -Wextra -Werror

*/
#include <iostream>
#include <fstream>
#include <x86intrin.h>

using namespace std;
#define OFFSET (1024 * 1024 * 16) / sizeof(int); // 16mb - размер смещения между ячейками
#define FRAGMENTS 64; // количество ячеек
#define CELLS 4; // количество ячеек за одно смещение


uint64_t rdtsc() {
    return __rdtsc();
}


int algorithm(int fragments) {
    uint64_t start = 0;
    uint64_t end = 0;
    
    uint64_t sum = 0;
    uint64_t count = 0;
    
    int offset = OFFSET;
    int cells = CELLS;
    
    int* n = new int[offset * fragments];

//array init
{
        int k = 0;
        int off = 0;
        while (k < fragments) {
            for (int i = 0; i < cells; i++) {
                if (k + 1 != fragments) {
                    n[off + i] = off + offset + i;
                }
                else {
                    n[off + i] = i;
                }
            }
            off += offset;
            k++;
            }
}
// measure of time
{
    int k = 0;
    for (int p = 0; p < cells; p++) {
        k = p;
        do {
            start = rdtsc();
            k = n[k];
            end = rdtsc();
            sum += end - start;
            count++;
        } while (k != p);
    }
    return sum / count;
    }
}
int main()
{

ofstream out;
out.open("res.txt");

int frag = FRAGMENTS;
for (int i = 1; i <= frag; i++ ){
    int aver =  algorithm(i); 
    cout << "average time for "<< i << " fragments is --> " << aver << endl;
    out << aver << endl;
}
out.close();


return 0;
}
