void bubbleSortNames(const int& left, const int& right) {

    for(int i = 0; i < right - left; i++) {
            for(int j = left; j < right - i; j++) {
                cmpLN = strcmp((arr_pointers[j]->lastName).c_str(), (arr_pointers[j+1]->lastName).c_str());
                cmpFN = strcmp((arr_pointers[j]->firstName).c_str(), (arr_pointers[j+1]->firstName).c_str());
                if(cmpLN > 0) {
                    swapTmp = arr_pointers[j];
                    arr_pointers[j] = arr_pointers[j+1];
                    arr_pointers[j+1] = swapTmp;
                }
                else if(cmpLN == 0 && cmpFN > 0) {
                    swapTmp = arr_pointers[j];
                    arr_pointers[j] = arr_pointers[j+1];
                    arr_pointers[j+1] = swapTmp;
                }
            }
        }
//        return;
    }
//}

void mergeNames(const int& start, const int& mid, const int& end) {
    
    // crawlers for both intervals and for dump
    int i = start, j = mid+1, k = 0;

    // traverse both arrays and in each iteration add smaller of both elements in dump 
    while(i <= mid && j <= end) {
        cmpLN = strcmp((arr_pointers[i]->lastName).c_str(), (arr_pointers[j]->lastName).c_str());
        cmpFN = strcmp((arr_pointers[i]->firstName).c_str(), (arr_pointers[j]->firstName).c_str());
        if(cmpLN < 0) {
            dump[k] = arr_pointers[i];
            k += 1; i += 1;
        }
        else if(cmpLN == 0 && cmpFN <= 0) {
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

void comboSortNames(const int& start, const int& end) {
    
    if(end - start <= BUBBLETHRESH) {
        anySwaps = false; //make sure we don't have any leftovers from elsewhere
        for(int i = 0; i < end - start; i++) {
            for(int j = start; j < end - i; j++) {
                cmpLN = strcmp((arr_pointers[j]->lastName).c_str(), (arr_pointers[j+1]->lastName).c_str());
                cmpFN = strcmp((arr_pointers[j]->firstName).c_str(), (arr_pointers[j+1]->firstName).c_str());
                if(cmpLN > 0) {
                    swapTmp = arr_pointers[j];
                    arr_pointers[j] = arr_pointers[j+1];
                    arr_pointers[j+1] = swapTmp;
                    anySwaps = true;
                }
                else if(cmpLN == 0 && cmpFN > 0) {
                    swapTmp = arr_pointers[j];
                    arr_pointers[j] = arr_pointers[j+1];
                    arr_pointers[j+1] = swapTmp;
                    anySwaps = true;
                }
            }
            if(anySwaps = false) {
                break;
            }
        }
        return;
    }
    if(start < end) {
        int mid = (start + end) / 2;
        comboSortNames(start, mid);
        comboSortNames(mid+1, end);
        mergeNames(start, mid, end);
    }
}
