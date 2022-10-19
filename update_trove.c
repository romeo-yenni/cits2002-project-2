#include "trove.h"

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

void update_trove() {

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