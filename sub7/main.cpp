// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2019

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
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
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
int main() {
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
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

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

#include <unordered_map>

#define BINLENGTH 512
#define WIDTH 255
#define BINDEPTH 55000
#define MAXELEMENTS 1010000

#include "fn_map.hpp"
#include "ln_map.hpp"

int arr_SSN[MAXELEMENTS];
int ssn_bin1[BINLENGTH][BINDEPTH];
int ssn_bin2[BINLENGTH][BINDEPTH];
int ssn_depth1[BINLENGTH];
int ssn_depth2[BINLENGTH];

int sortIndex[MAXELEMENTS];
Data* arr_pointers[MAXELEMENTS];
Data* dump[MAXELEMENTS];
Data* swapTmp;
int dump_depth = 0;
int arr_pointers_depth = 0;
Data* data_bin1[BINLENGTH][BINDEPTH];
Data* data_bin2[BINLENGTH][BINDEPTH];


int ssnStoi(const string& t) {
    return ( ((t[0]-'0')*100000000) + ((t[1]-'0')*10000000) + ((t[2]-'0')*1000000) + ((t[4]-'0')*100000) + ((t[5]-'0')*10000) + ((t[7]-'0')*1000) + ((t[8]-'0')*100) + ((t[9]-'0')*10) + ((t[10]-'0')*1) );
}

int cmpFN = 0;
int cmpLN = 0;
bool anySwaps = false;


#define BUBBLETHRESH 3
#include "combo.hpp"
#include "combo-ssn.hpp"
#include "radix.hpp"

string radixUsage = "           ";
#include "radix-str.hpp"

int listType = 3; //T3 unless proven otherwise
bool check_flag = true;
string stringComparator = "           ";
int whereTheBreaksAre = 1;



void sortDataList(list<Data *> &l) {
    int depth = 0;
    int index = 0;
    
    string* prevLN =  &( (*l.begin())->lastName );
    string* prevFN =  &( (*l.begin())->firstName );
    
    if(l.size() < 200000) {
        listType = 1;
        check_flag = false;
    }    
    else if((*l.begin())->lastName == (*prev(l.end()))->lastName && (*l.begin())->firstName == (*prev(l.end()))->firstName) {
        listType = 4;
        check_flag = false;
    }
    
    
    for(auto it = l.begin(); it != l.end(); ++it) {
        arr_pointers[index] = *it;
        if(whereTheBreaksAre < 5) {
            arr_SSN[index] = ssnStoi((*it)->ssn);
        }
        index++;
        if(check_flag == true && *prevLN > (*it)->lastName) {
        //we realize the list is out of order. It's T2.
            listType = 2;
            check_flag = false; //we don't need to run through this check again once we know.
        }
        //else if(check_flag == true && listType != 4 && *prevFN >= (*it)->firstName) { }
        
        else if(check_flag == true && (*prevFN < (*it)->firstName || *prevLN < (*it)->lastName)) {
            sortIndex[whereTheBreaksAre++] = index - 2; //cout << index - 2 << "\n"; //keep a count of where the first names and last names change
        }
        
        if(check_flag == true) { //we only need to do this if still unsure of list type /if we are T3
            prevLN = &((*it)->lastName);
            prevFN = &((*it)->firstName);
        }
    }
    
    if(listType == 1) {
        radixSort(index);
        radixSortFN(0, index);
        radixSortLN(0, index); //this one is okay, roughly 0.15 

//        for(int i = 0; i < 501; i++) {
//            ssn_depth1[i] += ssn_depth1[i-1];
//            //cout << i << " " << ssn_depth1[i] << endl;
//        }
//        radixSortFN(0, ssn_depth1[0]);
//        for(int i = 1; i < 500; i++) {
//            radixSortFN(ssn_depth1[i-1], ssn_depth1[i]);
//        }
        //comboSortNames(0, index - 1); //at this size, radix sort of text is likely to be slower?
    }
    
    else if(listType == 2) {
        radixSort(index); //roughly 0.16 on laptop 0.11 on cpu
        //comboSortNames(0, index - 1); //previously using this one; pretty slow.
        //comboSortSSN(0, index - 1); //bad. slow for long lists.
        radixSortFN(0, index);
        radixSortLN(0, index); //this one is okay, roughly 0.15 

//        for(int i = 0; i < 501; i++) {
//            ssn_depth1[i] += ssn_depth1[i-1];
//            //cout << i << " " << ssn_depth1[i] << endl;
//        }
//        radixSortFN(0, ssn_depth1[0]);
//        for(int i = 1; i < 500; i++) {
//            radixSortFN(ssn_depth1[i-1], ssn_depth1[i]);
//        } 
    }
    
    else if(listType == 3) {
        //an attempt at a high speed radix sort was made. 0.87 seconds! Keep the combo sort here
        sortIndex[whereTheBreaksAre++] = index - 1;
        comboSortSSN(sortIndex[0], sortIndex[1]);
        for(int i = 2; i < whereTheBreaksAre; i++) {
            comboSortSSN(sortIndex[i-1] + 1, sortIndex[i]);
        }
        
    /* //trash performance for Sample 3 - too many iterations and things set
    sortIndex[whereTheBreaksAre++] = index - 1;
    radixSortSSN(0, sortIndex[1]);
        for(int i = 2; i < whereTheBreaksAre; i++) {
            radixSortSSN(sortIndex[i-1] + 1, sortIndex[i]);
        }
    */
    
    }
    else if(listType == 4) {
        radixSort(index);
    }

    index = 0;
    for(auto it2 = l.begin(); it2 != l.end(); ++it2) {
        *it2 = arr_pointers[index++];
    }
}
