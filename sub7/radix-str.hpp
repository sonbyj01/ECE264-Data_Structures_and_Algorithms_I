void radixSortLN(int left, int right) {
    int x;
    int index = 0;
    for(int i = left; i < right; i++) {
        x = lastNames[arr_pointers[i]->lastName];
        data_bin1[x][ ssn_depth1[x]++ ] = arr_pointers[i];
    }
    
    //into bin2
//    for(int i = 0; i < BINLENGTH; i++) {
//        for(int j = 0; j < ssn_depth1[i]; j++) {
//            x = lastNames[ data_bin1[i][j]->lastName ];
//            data_bin2[x][ ssn_depth2[x]++ ] = data_bin1[i][j];
//        }
//    }
    for(int k = 0; k < BINLENGTH; k++) {
        for(int m = 0; m < ssn_depth1[k]; m++) {
            arr_pointers[index++] = data_bin1[k][m];
        }
    //ssn_depth1[k] = 0;
    }

        //ssn_depth1[i] = 0;
}

//double timeDiff = 0;

void radixSortFN(int left, int right) {
    int x;
    //clock_t t1 = clock();

    for(int i = left; i < right; i++) {
        x = firstNames[arr_pointers[i]->firstName];
        data_bin2[x][ ssn_depth2[x]++ ] = arr_pointers[i];
        
    }
    
//    for(int i = 0; i < BINLENGTH; i++) {
//        for(int j = 0; j < ssn_depth1[i]; j++) {
//            x = (ssn_bin1[i][j] >> 24) & WIDTH;
//            ssn_bin2[x][ ssn_depth2[x] ] = ssn_bin1[i][j];
//            data_bin2[x][ ssn_depth2[x]++ ] = data_bin1[i][j];
//        }
//        ssn_depth1[i] = 0;
//    }
    
    int index = left;
    
    for(int i = 0; i < BINLENGTH; i++) {
        //cout << ssn_depth2[i] << " ";
        for(int j = 0; j < ssn_depth2[i]; j++) {
            arr_pointers[index++] = data_bin2[i][j];
        }
        //ssn_depth2[i] = 0;
        
    }
    //clock_t t2 = clock();
    //timeDiff += ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    //cout << index << endl;
}
