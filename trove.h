#define _POSIX_C_SOURCE     200809L
#define _DEFAULT_SOURCE
#include  <stdio.h>
#include  <stdbool.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include  <sys/param.h>
#include  <time.h>
#include  <string.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/wait.h>

// FILES STRUCTURE
typedef struct {
    char        *pathname;
} FILES;

// WORDS STRUCTURE
typedef struct {
    char        *word;
    char        *filepath;
} WORDS;

// TROVE-PATHS STRUCTURE
typedef struct {
    char        *filepath;
} T_PATHS;

// SEARCH STRUCTURE
typedef struct {
    char        *filepath;
} SEARCH;

// DECLARE GLOBAL PREPROCESSOR CONSTANTS
#define	OPTLIST		"bruf:l:"
#define	CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }
#define DEFAULT_TROVE_FILE "/tmp/trove"
#define DEFAULT_LENGTH 4

// DECLARE GLOBAL FUNCTIONS
extern void list_all_files();
extern void scan_directory(char *);
extern void read_file(char *, int);
extern void write_trove();
extern void read_trove(char *);
extern void update_trove(int);
extern void collect_trove_paths();
extern void trim_line(char *);
extern bool check_wipe();
extern void search_trove(char *word);
extern void check_within();
extern void compress();
extern void read_compressed();

// DECLARE GLOBAL VARIABLES
extern FILES           *files;
extern int             nfiles;
extern WORDS       *wordstruc;
extern int             nwords;
extern T_PATHS         *paths;
extern int             npaths;
extern SEARCH          *search;
extern int            nsearch;
extern int                opt;
extern char           *filenm;
extern bool             bflag;
extern bool             rflag;
extern bool             uflag;
extern bool             fflag;
extern bool             lflag;