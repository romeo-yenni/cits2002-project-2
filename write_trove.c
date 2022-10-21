#include "trove.h"

void write_trove() {

    // buf[0] = '\0';

    FILE *fp;
    fp  = fopen (filenm, "w");

    for (int i=0;i<nwords;i++) {
        // THINK OF SOMETHING LATER....
        char line[BUFSIZ];
        line[0] = '\0';

        sprintf(line, "%s %s\n", wordstruc[i].word, wordstruc[i].filepath);

        fputs(line, fp);

        // strcat(buf, line);

    }

    fclose(fp);
    // compress(buf);
}