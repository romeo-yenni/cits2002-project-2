#include "trove.h"

void write_trove() {

    FILE *fp;
    fp  = fopen (filenm, "w");

    for (int i=0;i<nwords;i++) {
        // THINK OF SOMETHING LATER....
        char line[1000];
        line[0] = '\0';

        sprintf(line, "%s %s\n", wordstruc[i].word, wordstruc[i].filepath);

        fputs(line, fp);
    }

    fclose(fp);

}