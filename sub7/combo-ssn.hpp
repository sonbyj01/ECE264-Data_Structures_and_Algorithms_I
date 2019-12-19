void swapSSN(const int& a, const int& b) {
    swapTmp = arr_pointers[a];
    arr_pointers[a] = arr_pointers[b];
    arr_pointers[b] = swapTmp;
}

void bubbleSortSSN(const int& left, const int& right) {

    for(int i = 0; i < right - left; i++) {
        for(int j = left; j < right - i; j++) {
            if(arr_pointers[j]->ssn > arr_pointers[j+1]->ssn) {
                swapTmp = arr_pointers[j];
                arr_pointers[j] = arr_pointers[j+1];
                arr_pointers[j+1] = swapTmp;
            }
        }
    }
}

void insertionSortSSN(const int& left, const int& right) 
{   
    int i, j; 
    for (i = left; i < right + 1; i++) { 
        swapTmp = arr_pointers[i]; 
        j = i - 1; 
  
        /* Move elements of arr_pointers[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && arr_pointers[j]->ssn > swapTmp->ssn) { 
            arr_pointers[j + 1] = arr_pointers[j]; 
            j = j - 1; 
        } 
        arr_pointers[j + 1] = swapTmp; 
    } 
}

void mergeSSN(const int& start, const int& mid, const int& end) {
    
    // crawlers for both intervals and for dump
    int i = start, j = mid+1, k = 0;

    // traverse both arrays and in each iteration add smaller of both elements in dump 
    while(i <= mid && j <= end) {
        if(arr_pointers[i]->ssn <= arr_pointers[j]->ssn) {
            dump[k] = arr_pointers[i];
            k += 1; i += 1;
        }
        else {
            dump[k] = arr_pointers[j];
            k += 1; j += 1;
        }
    }

    // add elements left in the first interval 
    while(i <= mid) {
        dump[k] = arr_pointers[i];
        k += 1; i += 1;
    }

    // add elements left in the second interval 
    while(j <= end) {
        dump[k] = arr_pointers[j];
        k += 1; j += 1;
    }

    // copy dump to original interval
    for(i = start; i <= end; i += 1) {
        arr_pointers[i] = dump[i - start];
    }
    //memset(dump, 0, sizeof(dump));

}
void comboSortSSN(const int& start, const int& end) {
    
    if(end - start <= BUBBLETHRESH) {
        anySwaps = false; //make sure we don't have any leftovers from elsewhere
        for(int i = 0; i < end - start; i++) {
            for(int j = start; j < end - i; j++) {
                if(arr_pointers[j]->ssn > arr_pointers[j+1]->ssn) {
                    swapTmp = arr_pointers[j];
                    arr_pointers[j] = arr_pointers[j+1];
                    arr_pointers[j+1] = swapTmp;
                    anySwaps = true;
                }
            }
        }
        return;
    }
    if(start < end) {
        int mid = (start + end) / 2;
        comboSortSSN(start, mid);
        comboSortSSN(mid+1, end);
        mergeSSN(start, mid, end);
    }
}
