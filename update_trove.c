#include "trove.h"

bool check_wipe() {
    int cnt = 0;
    for (int i=0;i<nfiles;i++) {
        for (int j=0;j<npaths;j++) {
            if (strcmp(files[i].pathname, paths[j].filepath) == 0) {
                cnt++;
            }
        }
    }
    if (cnt==npaths) {
        return true;
    }
    else {
        return false;
    }
}

void remove_element(int index) {
    for (int i=index;i<nwords;i++) {
        wordstruc[i] = wordstruc[i+1];
    }
    wordstruc = realloc(wordstruc, (nwords - 1) * sizeof(WORDS) );
    CHECK_ALLOC(wordstruc);
    nwords--;
}

void check_words(int i) {

    for (int j=0;j<nwords;j++) {
        if (strcmp(files[i].pathname, wordstruc[j].filepath) == 0) {
            if (nwords == 1) {
                wordstruc = NULL;
            }
            else {
                remove_element(j);
                if ( (j==0) && (wordstruc==NULL)) {
                    break;
                }
                else {
                    j--;
                }
            }
        }
    }
}

void update_trove(int op) {

    if ( (check_wipe()) && (op == 1) ) {
        FILE *fp;
        fp  = fopen (filenm, "w");
        fclose(fp);
    }
    else if ( (check_wipe()) && (op == 2) ) {
        FILE *fp;
        fp  = fopen (filenm, "w");
        write_trove();
        fclose(fp);
    }
    else {
        for (int i=0;i<nfiles;i++) {
            check_words(i);
            if (wordstruc == NULL) {
                break;
            }
        }
        FILE *fp;
        fp  = fopen (filenm, "w");
        write_trove();
        fclose(fp);
    }
}