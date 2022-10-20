#include "trove.h"

bool checkUnique(char *word, char *filename) {
    for (int i=0;i<nwords;i++) {
        if ( (strcmp(wordstruc[i].word, word) == 0) && (strcmp(wordstruc[i].filepath, filename) == 0) ) {
            return true;
        }
    }
    return false;
}

void read_file(char *filename, int length) {

    FILE *ptr;
    char ch;

    ptr = fopen(filename, "r");
    CHECK_ALLOC(ptr);
    
    // EASY METHOD -- THINK OF SOMETHING BETTER LATER
    char temp[1000];
    temp[0] = '\0';

    int word_size = 0;
    while (!feof(ptr)) {
        ch = fgetc(ptr);
        if (!isalnum(ch)) {
            if (word_size >= length) {
                if ( checkUnique(temp, filename) ) {
                    temp[0] = '\0';
                    word_size = 0;
                }
                else {
                    wordstruc = realloc(wordstruc, (nwords+1)*sizeof(WORDS));
                    CHECK_ALLOC(wordstruc);

                    wordstruc[nwords].word  = strdup(temp);
                    CHECK_ALLOC(wordstruc[nwords].word);

                    wordstruc[nwords].filepath = strdup(filename);
                    CHECK_ALLOC(wordstruc[nwords].filepath);

                    nwords++;
                }
                temp[0] = '\0';
                word_size = 0;
            }
            else {
                temp[0] = '\0';
                word_size = 0;
            }
        }
        else {
            strncat(temp, &ch, 1);
            word_size++;
        }
    }
    fclose(ptr);
}