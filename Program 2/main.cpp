// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2019

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
    string lastName;
    string firstName;
    string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {
    ifstream input(filename);
    if (!input) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;

    // Load the data
    for (int i = 0; i < size; i++)
    {
        getline(input, line);
        stringstream ss2(line);
        Data *pData = new Data();
        ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
        l.push_back(pData);
    }

    input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename)
{

    ofstream output(filename);
    if (!output)
    {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // Write the size first
    int size = l.size();
    output << size << "\n";

    // Write the data
    for (auto pData : l)
    {
        output << pData->lastName << " "
               << pData->firstName << " "
               << pData->ssn << "\n";
    }

    output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main()
{
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    list<Data *> theList;
    loadDataList(theList, filename);

    cout << "Data loaded.\n";

    cout << "Executing sort...\n";
    clock_t t1 = clock();
    sortDataList(theList);
    clock_t t2 = clock();
    double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

    cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

    cout << "Enter name of output file: ";
    cin >> filename;
    writeDataList(theList, filename);

    return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

#include "const.h"

#define BUCKETS 512
#define DEPTH 55000
#define WIDTH 255   // ssn 2^6
#define MAXLENGTH 1010000

int ssn_array[MAXLENGTH];
int ssn_bucket1[BUCKETS][DEPTH];
int ssn_bucket2[BUCKETS][DEPTH];
int ssn_depth1[BUCKETS];
int ssn_depth2[BUCKETS];

Data* data_bucket1[BUCKETS][DEPTH];
Data* data_bucket2[BUCKETS][DEPTH];

Data* pointers_arr[MAXLENGTH];

Data* insertion_array[MAXLENGTH];

int dataSize = 0;

void insertionSort(list<Data *> &l);
int ssnStoi(const string& t);
void radixsort(int size);
void radixsortF(int size);
void radixsortL(int size);

void sortDataList(list<Data *> &l) 
{
    for (auto ele = l.begin(); ele != l.end(); ++ele) 
    {
        pointers_arr[dataSize] = *ele;
        ssn_array[dataSize++] = ssnStoi((*ele)->ssn);
    }
    
    if (pointers_arr[0]->firstName == pointers_arr[1]->firstName && pointers_arr[0]->firstName != pointers_arr[dataSize - 1]->firstName)    // T3
    {
        insertionSort(l);
    } else if (pointers_arr[0]->firstName == pointers_arr[dataSize - 1]->firstName && pointers_arr[0]->lastName == pointers_arr[dataSize - 1]->lastName) // T4
    {
        radixsort(dataSize);
    } else if (dataSize <= 101000)  // T1, T2
    {
        radixsort(dataSize);
        radixsortF(dataSize);
        radixsortL(dataSize);
    } else
    {
        radixsort(dataSize);
        radixsortF(dataSize);
        radixsortL(dataSize);
    } 

    dataSize = 0;
    for(auto ele = l.begin(); ele != l.end(); ++ele) 
    {
        *ele = pointers_arr[dataSize++];
    }
}

void insertionSort(list<Data *> &l)
{
    
    int startVal = 0;
    int i, j, pointers_arr, k=0;
    for(auto at : l) {
        insertion_array[k] = at;
        k++;
    }
    
    Data *key;
    for(i = 1; i < dataSize; i++)
    {
        if (insertion_array[i]->firstName != insertion_array[i-1]->firstName)
        startVal = i;
        key = insertion_array[i];
        j = i-1;
        
        while(j >= startVal && insertion_array[j]->ssn>key->ssn)
        {
            insertion_array[j+1] = insertion_array[j];
            j--;
        }
        insertion_array[j+1]=key;
    }
    auto it = l.begin();
    for (pointers_arr = 0; pointers_arr < dataSize; pointers_arr++)
    {
        *it=insertion_array[pointers_arr];
        it++;
    }
}

int ssnStoi(const string& t) {
    return ( ((t[0]-'0')*100000000) + ((t[1]-'0')*10000000) + ((t[2]-'0')*1000000) + ((t[4]-'0')*100000) + ((t[5]-'0')*10000) + ((t[7]-'0')*1000) + ((t[8]-'0')*100) + ((t[9]-'0')*10) + ((t[10]-'0')*1) );
}

void radixsort(int size)  // (n)umber of elements to sort
{
    int x;
    for (int i = 0; i < size; i++) 
    {
        x = ssn_array[i] & WIDTH;
        ssn_bucket1[x][ssn_depth1[x]] = ssn_array[i];
        data_bucket1[x][ssn_depth1[x]++] = pointers_arr[i];
    }

    for (int i = 0; i < BUCKETS; i++) 
    {
        for (int j = 0; j < ssn_depth1[i]; j++) 
        {
            x = (ssn_bucket1[i][j] >> 8) & WIDTH;
            ssn_bucket2[x][ssn_depth2[x]] = ssn_bucket1[i][j];
            data_bucket2[x][ssn_depth2[x]++] = data_bucket1[i][j];
        }
        ssn_depth1[i] = 0;
    }

    for (int i = 0; i < BUCKETS; i++) 
    {
        for (int j = 0; j < ssn_depth2[i]; j++) 
        {
            x = (ssn_bucket2[i][j] >> 16) & WIDTH;
            ssn_bucket1[x][ssn_depth1[x]] = ssn_bucket2[i][j];
            data_bucket1[x][ssn_depth1[x]++] = data_bucket2[i][j];
        }
        ssn_depth2[i] = 0;
    }
    
    for (int i = 0; i < BUCKETS; i++) 
    {
        for (int j = 0; j < ssn_depth1[i]; j++) 
        {
            x = (ssn_bucket1[i][j] >> 24) & WIDTH;
            ssn_bucket2[x][ssn_depth2[x]] = ssn_bucket1[i][j];
            data_bucket2[x][ssn_depth2[x]++] = data_bucket1[i][j];
        }
        ssn_depth1[i] = 0;
    }
    
    int ind = 0;
    for (int i = 0; i < BUCKETS; i++) 
    {
        for (int j = 0; j < ssn_depth2[i]; j++) 
        {
            pointers_arr[ind++] = data_bucket2[i][j];
        }
        ssn_depth2[i] = 0;
    }
}

void radixsortL(int size) 
{
    int x;
    int ind = 0;
    for (int i = 0; i < size; i++) 
    {
        x = lookLast[pointers_arr[i]->lastName];
        data_bucket1[x][ssn_depth1[x]++] = pointers_arr[i];
    }
    for (int k = 0; k < BUCKETS; k++) 
    {
        for (int m = 0; m < ssn_depth1[k]; m++) 
        {
            pointers_arr[ind++] = data_bucket1[k][m];
        }
    }
}

void radixsortF(int size) 
{
    int x;
    for(int i = 0; i < size; i++) 
    {
        x = lookFirst[pointers_arr[i]->firstName];
        data_bucket2[x][ssn_depth2[x]++] = pointers_arr[i];
    }
    int ind = 0;
    for (int i = 0; i < BUCKETS; i++) 
    {
        for (int j = 0; j < ssn_depth2[i]; j++) 
        {
            pointers_arr[ind++] = data_bucket2[i][j];
        }
    }
}