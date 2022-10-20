#include "trove.h"

void search_trove(char *word) {
    for (int i=0;i<nwords;i++) {
        if (strcmp(word, wordstruc[i].word) == 0) {
            search = realloc(search, (nsearch+1)*sizeof(SEARCH));
            CHECK_ALLOC(search);

            search[nsearch].filepath = strdup(wordstruc[i].filepath);
            CHECK_ALLOC(search[nsearch].filepath);
            nsearch++;
        }
    }
    if (nsearch==0) {
        exit(EXIT_FAILURE);
    }
    else {
        for (int i=0;i<nsearch;i++) {
            printf("%s\n", search[i].filepath);
        }
    }
}