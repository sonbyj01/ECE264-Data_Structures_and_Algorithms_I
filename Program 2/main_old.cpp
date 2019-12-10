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

Data* inputs[1100000];
Data* bucket[100000][500];
Data* p[1010000];

void insertionSort(list<Data *> &l);
void stdSort(list<Data *> &l);
void radixsort();

int ssnconvert(string input, int c);
int bucketc[100000] = {0};
int dataSize;

bool cmp(const Data *a, const Data *b);

void sortDataList(list<Data *> &l) 
{
    int i = 0;
    for (auto at : l) 
    {
        p[i] = at;
        i++;
    }
    dataSize = i;
    
    if (p[0]->firstName == p[1]->firstName && p[0]->firstName != p[dataSize - 1]->firstName)    // T3
    {
        insertionSort(l);
    } else if (p[0]->firstName == p[dataSize - 1]->firstName && p[0]->lastName == p[dataSize - 1]->lastName) // T4
    {
        radixsort();
        auto op = l.begin();
        for (int y = 0; y<l.size(); y++) 
        {
            *op = p[y];
            op++;
        }
    } else if (dataSize <= 101000) // T1
    {
        stdSort(l);
    } else // T2
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
    int i, j, p, k=0;
    for(auto at : l) {
        inputs[k] = at;
        k++;
    }
    
    Data *key;
    for(i = 1; i < dataSize; i++)
    {
        if (inputs[i]->firstName != inputs[i-1]->firstName)
        startVal = i;
        key = inputs[i];
        j = i-1;
        
        while(j >= startVal && inputs[j]->ssn>key->ssn)
        {
            inputs[j+1] = inputs[j];
            j--;
        }
        inputs[j+1]=key;
    }
    auto it = l.begin();
    for (p = 0; p < dataSize; p++)
    {
        *it=inputs[p];
        it++;
    }
}

void radixsort()
{
    int f2ssn;
    for (int i = 0; i < dataSize; i++)
    {
        f2ssn = ssnconvert((p[i]->ssn),5);
        bucket[f2ssn][bucketc[f2ssn]] = p[i];
        bucketc[f2ssn] += 1;
    }
    
    int j = 0;
    int k = 0;
    for (int i = 0; i < dataSize; i++)
    {
        if (k == bucketc[j])
        {
            k = 0;
            j++;
            i--;
        }
        else
        {
            p[i] = bucket[j][k];
            k++;
        }
    }
    
    for (int i = 0; i < 100000; i++)
    {
        bucketc[i] = 0;
    }
    int fssn;
    for (int i = 0; i < dataSize; i++)
    {
        fssn = ssnconvert((p[i]->ssn), 4);
        bucket[fssn][bucketc[fssn]] = p[i];
        bucketc[fssn] += 1;
    }
    j = 0;
    k = 0;
    for (int i = 0; i < dataSize; i++)
    {
        if (k == bucketc[j])
        {
            k = 0;
            j++;
            i--;
        }
        else
        {
            p[i] = bucket[j][k];
            k++;
        }
    }
}

int ssnconvert(string input, int c)
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