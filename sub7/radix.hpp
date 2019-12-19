void radixSortSSN(int left, int right) {
    int x;
    for(int i = left; i <= right; i++) {
        //cout << arr_SSN[i] << endl;
        x = arr_SSN[i] & WIDTH;
        //cout << x << endl;
        ssn_bin1[x][ ssn_depth1[x] ] = arr_SSN[i];
        data_bin1[x][ ssn_depth1[x]++ ] = arr_pointers[i];
    }
    
    //into bin2
    for(int i = 0; i < BINLENGTH; i++) {
        for(int j = 0; j < ssn_depth1[i]; j++) {
            x = (ssn_bin1[i][j] >> 8) & WIDTH;
            ssn_bin2[x][ ssn_depth2[x] ] = ssn_bin1[i][j];
            data_bin2[x][ ssn_depth2[x]++ ] = data_bin1[i][j];
        }
        ssn_depth1[i] = 0;
    }
    
    //into bin1
    for(int i = 0; i < BINLENGTH; i++) {
        for(int j = 0; j < ssn_depth2[i]; j++) {
            x = (ssn_bin2[i][j] >> 16) & WIDTH;
            ssn_bin1[x][ ssn_depth1[x] ] = ssn_bin2[i][j];
            data_bin1[x][ ssn_depth1[x]++ ] = data_bin2[i][j];
        }
        ssn_depth2[i] = 0;
    }
    
    for(int i = 0; i < BINLENGTH; i++) {
        for(int j = 0; j < ssn_depth1[i]; j++) {
            x = (ssn_bin1[i][j] >> 24) & WIDTH;
            ssn_bin2[x][ ssn_depth2[x] ] = ssn_bin1[i][j];
            data_bin2[x][ ssn_depth2[x]++ ] = data_bin1[i][j];
        }
        ssn_depth1[i] = 0;
    }
    
    int index = left;
    
    for(int i = 0; i < BINLENGTH; i++) {
        for(int j = 0; j < ssn_depth2[i]; j++) {
            arr_pointers[index++] = data_bin2[i][j];
            //cout << arr_pointers[index++]->ssn << " ";
        }
        ssn_depth2[i] = 0;
        
    }
}

void radixSort(int n) {
    int x;
    for(int i = 0; i < n; i++) {
        //cout << arr[i] << endl;
        x = arr_SSN[i] & WIDTH;
        //cout << x << endl;
        ssn_bin1[x][ ssn_depth1[x] ] = arr_SSN[i];
        data_bin1[x][ ssn_depth1[x]++ ] = arr_pointers[i];
    }
    
    //into bin2
    for(int i = 0; i < BINLENGTH; i++) {
        for(int j = 0; j < ssn_depth1[i]; j++) {
            x = (ssn_bin1[i][j] >> 8) & WIDTH;
            ssn_bin2[x][ ssn_depth2[x] ] = ssn_bin1[i][j];
            data_bin2[x][ ssn_depth2[x]++ ] = data_bin1[i][j];
        }
        ssn_depth1[i] = 0;
    }
    
    //into bin1
    for(int i = 0; i < BINLENGTH; i++) {
        for(int j = 0; j < ssn_depth2[i]; j++) {
            x = (ssn_bin2[i][j] >> 16) & WIDTH;
            ssn_bin1[x][ ssn_depth1[x] ] = ssn_bin2[i][j];
            data_bin1[x][ ssn_depth1[x]++ ] = data_bin2[i][j];
        }
        ssn_depth2[i] = 0;
    }
    
    for(int i = 0; i < BINLENGTH; i++) {
        for(int j = 0; j < ssn_depth1[i]; j++) {
            x = (ssn_bin1[i][j] >> 24) & WIDTH;
            ssn_bin2[x][ ssn_depth2[x] ] = ssn_bin1[i][j];
            data_bin2[x][ ssn_depth2[x]++ ] = data_bin1[i][j];
        }
        ssn_depth1[i] = 0;
    }
    
    int index = 0;
    
    for(int i = 0; i < BINLENGTH; i++) {
        //cout << ssn_depth2[i] << " ";
        for(int j = 0; j < ssn_depth2[i]; j++) {
            arr_pointers[index++] = data_bin2[i][j];
        }
        ssn_depth2[i] = 0;
        
    }
}
