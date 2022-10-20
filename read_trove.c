#include "trove.h"

bool is_Unique(char * file) {
    for (int i=0;i<npaths;i++) {
        if (strcmp(file, paths[i].filepath) == 0) {
            return false;
        }
    }
    return true;
}

void trim_line(char *line)
{
    int i = 0;
    while(line[i] != '\0') {

        if( line[i] == '\r' || line[i] == '\n' ) {
            line[i] = '\0';
            break;          
        }
        i = i+1;            
    }
}

void read_trove(char *file) {

    FILE *ptr;
    char   line[BUFSIZ];
    ptr = fopen(file, "r");
    CHECK_ALLOC(ptr);

    char word_temp[1000];
    char path_temp[1000];

    word_temp[0] = '\0';
    path_temp[0] = '\0';

    char space = ' ';

    while( fgets(line, sizeof line, ptr) != NULL ) {  
        trim_line(line);
        int space_cnt = 0;
        for (int i=0;i<strlen(line);i++) {
            if (space_cnt == 0) {
                if (strncmp(&line[i], &space, 1) != 0) {
                    strncat(word_temp, &line[i], 1);
                }
                else {
                    space_cnt++;
                }
            }
            else {
                strncat(path_temp, &line[i], 1);
            }
        }

        wordstruc = realloc(wordstruc, (nwords+1)*sizeof(WORDS));
        CHECK_ALLOC(wordstruc);


        wordstruc[nwords].word = strdup(word_temp);
        CHECK_ALLOC(wordstruc[nwords].word);
        wordstruc[nwords].filepath = strdup(path_temp);
        CHECK_ALLOC(wordstruc[nwords].filepath);
        nwords++;

        if (is_Unique(path_temp)) {
            paths = realloc(paths, (npaths+1)*sizeof(T_PATHS));
            CHECK_ALLOC(paths);
            paths[npaths].filepath = strdup(path_temp);
            CHECK_ALLOC(paths[npaths].filepath);
            npaths++;
        }

        word_temp[0] = '\0';
        path_temp[0] = '\0';
    }
}