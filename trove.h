#define _POSIX_C_SOURCE     200809L
#include  <stdio.h>
#include  <stdbool.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include  <sys/param.h>
#include  <time.h>
#include  <string.h>

#define	CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

extern void list_all_files();
extern void scan_directory(char *);

typedef struct {
    char        *pathname;
} FILES;

extern FILES           *files;
extern int             nfiles;
