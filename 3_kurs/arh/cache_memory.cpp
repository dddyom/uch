/*
Влияние кэш-памяти на время обработки массивов
1. Исследование зависимости времени доступа к данным в памяти от их
объема.
2. Исследование зависимости времени доступа к данным в памяти от
порядка их обхода.

gcc cache_memory.cpp -o main -lstdc++ -Wall -Wextra -Werror

*/
#include <iostream>
#include <stdio.h>
#include <algorithm>


using namespace std;

typedef unsigned long long ull;


inline ull rdtsc() {

unsigned int lo, hi;

asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );

return ((ull)hi << 32) | lo;
}

int main()
{
    random();
    int N;
    cout << "Размер массива: ";
    cin >> N;
    int *arr=new int[N]; 
 
    for (int i=0; i<N; i++) arr[i]=rand()%200; //заполнение
{    
    ull t1 = rdtsc();
    for (int i=0; i<N; i++) cout << arr[i] << " "; 
    ull t2 = rdtsc();
    cout << endl;//вывод
    cout << "Time for one --> " << (t2 - t1) / N << endl; 
}
{   
    ull t1 = rdtsc();
    for (int i=N-1; i>=0; i--) cout << arr[i] << " ";
    ull t2 = rdtsc();
    cout << endl;//обратн
    cout << "Time for one --> " << (t2 - t1) / N << endl; 
}   
{    
    srand(time(NULL));                             
    random_shuffle(arr, arr+N);
    ull t1 = rdtsc();
    for (int i=0; i<N; i++) cout << arr[i] << " ";
    ull t2 = rdtsc();
    cout << endl;//случайн
    cout << "Time for one --> " << (t2 - t1) / N << endl; 
}    
    delete arr; 
    
    return 0;
}
