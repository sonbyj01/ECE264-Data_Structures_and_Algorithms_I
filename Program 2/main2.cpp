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
    //cin >> filename;
    list<Data *> theList;
    loadDataList(theList, "sample2.txt");

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
#define BIN_LENGTH 600
#define DEPTH 110000

Data* insertion_array[1100000];
Data* bucket[BIN_LENGTH][DEPTH];
Data* bucket1[BIN_LENGTH][DEPTH];
Data* bucket2[BIN_LENGTH][DEPTH];
Data* bucket3[BIN_LENGTH][DEPTH];
Data* temp_array[1010000];   // array version of list

#include "const.h"

void insertionSort(list<Data *> &l);
void stdSort(list<Data *> &l);
void radixsort(list<Data *> &l);
void radixsortF(list<Data *> &l);
void radixsortL(list<Data *> &l);
bool cmp(const Data *a, const Data *b);
void reset_bucketc();

int ssnconvert(string &input, int c);
int bucketc[BIN_LENGTH] = {0};
int bucketc1[BIN_LENGTH] = {0};
int bucketc2[BIN_LENGTH] = {0};
int bucketc3[BIN_LENGTH] = {0};
int dataSize = 0;

void sortDataList(list<Data *> &l) 
{
    for (auto ele : l) 
    {
        temp_array[dataSize] = ele;
        dataSize++;
    }
    
    if (temp_array[0]->firstName == temp_array[1]->firstName && temp_array[0]->firstName != temp_array[dataSize - 1]->firstName)    // T3
    {
        insertionSort(l);
    } else if (temp_array[0]->firstName == temp_array[dataSize - 1]->firstName && temp_array[0]->lastName == temp_array[dataSize - 1]->lastName) // T4
    {
        radixsort(l);
        // auto op = l.begin();
        // for (int y = 0; y<l.size(); y++) 
        // {
        //     *op = p[y];
        //     op++;
        // }
    } else if (dataSize <= 101000)// T1, T2
    {
        radixsort(l);
        radixsortF(l);
        radixsortL(l);
    } else
    {
        stdSort(l);
    }
}

void stdSort(list<Data *> &l) 
{
    l.sort(cmp);
}

bool cmp(const Data *a, const Data *b) 
{
    if (a->lastName < b->lastName) return true;
    else if(a->lastName == b->lastName && a->firstName < b->firstName) return true;
    else if(a->lastName == b->lastName && a->firstName == b->firstName && a->ssn < b->ssn) return true;
    return false;
}
void insertionSort(list<Data *> &l)
{
    
    int startVal = 0;
    int i, j, temp_array, k=0;
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
    for (temp_array = 0; temp_array < dataSize; temp_array++)
    {
        *it=insertion_array[temp_array];
        it++;
    }
}

void radixsort(list<Data *> &l)
{
    int f2ssn;
    for (int i = 0; i < dataSize; i++)
    {
        f2ssn = ssnconvert((temp_array[i]->ssn), 5);
        bucket[bucketc[f2ssn]++][f2ssn] = temp_array[i];
    }
    auto op = l.begin();
    int j = 0;
    int k = 0;
    for (int i = 0; i < l.size(); i++)
    {
        if (k == bucketc[j])
        {
            k = 0;
            j++;
            i--;
        }
        else
        {
            temp_array[i] = bucket[k][j];
            k++;
        }
    }
    int fssn;
    for (int i = 0; i < dataSize; i++)
    {
        fssn = ssnconvert((temp_array[i]->ssn), 4);
        bucket1[bucketc1[fssn]++][fssn] = temp_array[i];
        //bucketc1[fssn] += 1;
    }
    op = l.begin();
    j = 0;
    k = 0;
    for (int i = 0; i < l.size(); i++)
    {
        if (k == bucketc1[j])
        {
            k = 0;
            j++;
            i--;
        }
        else
        {
            temp_array[i] = bucket1[k][j];
            *op = temp_array[i];
            k++;
            op++;
        }
    }
}

int ssnconvert(string &input, int c)
{
    if(c == 4)
    {
        return (input.at(0)-48)*1000+(input.at(1)- 48)*100+(input.at(2)- 48)*10+(input.at(4)- 48);
    }
    else if(c == 5)
    {
        return (input.at(5)- 48)*10000+(input.at(7)- 48)*1000+(input.at(8)- 48)*100+(input.at(9)- 48)*10+(input.at(10)- 48);
    }
    return (input.at(0) - 48) * 100000000 + (input.at(1) - 48) * 10000000 + (input.at(2) - 48) * 1000000 +
    (input.at(4) - 48) * 100000 + (input.at(5) - 48) * 10000 + (input.at(7) - 48) * 1000 +
    (input.at(8) - 48) * 100 + (input.at(9) - 48) * 10 + (input.at(10) - 48);
}

void radixsortF(list<Data *> &l)
{
    for (int i = 0; i < dataSize; i++)
    {
        int hash = lookFirst[temp_array[i]->firstName];
        cout << hash << ", " << bucketc2[hash] << temp_array[i]->firstName << endl;
        bucket2[bucketc2[hash]++][hash] = temp_array[i];
    }
    auto op = l.begin();
    int j = 0;
    int k = 0;
    for (int i = 0; i < l.size(); i++)
    {
        if (k == bucketc2[j])
        {
            k = 0;
            j++;
            i--;
        }
        else
        {
            temp_array[i] = bucket2[k][j];
            k++;
        }
    }
}

void radixsortL(list<Data *> &l)
{
    for (int i = 0; i < dataSize; i++)
    {
        int hash = lookLast[temp_array[i]->lastName];
        bucket3[bucketc3[hash]++][hash] = temp_array[i];
        //bucketc3[hash] += 1;
    }
    auto op = l.begin();
    int j = 0;
    int k = 0;
    for (int i = 0; i < l.size(); i++)
    {
        if (k == bucketc3[j])
        {
            k = 0;
            j++;
            i--;
        }
        else
        {
            temp_array[i] = bucket3[k][j];
            *op = temp_array[i];
            k++;
            op++;
        }
    }
}