#include "trove.h"

FILES *files  = NULL;
int nfiles  = 0;

WORDS *wordstruc = NULL;
int nwords = 0;

T_PATHS *paths = NULL;
int npaths = 0;

int  opt;

char *progname;

bool bflag = false;
bool rflag = false;
bool uflag = false;

bool lflag = false;
int length = DEFAULT_LENGTH;

bool fflag = false;
char *filenm = DEFAULT_TROVE_FILE;

void usage() {
    fprintf(stderr, "Usage: %s [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist\n------\nUsage: %s  [-f trovefile]  word\n", progname, progname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

    progname = argv[0];

    opterr	= 0;
    while((opt = getopt(argc, argv, OPTLIST)) != -1)   {  
//  ACCEPT A STRING ARGUMENT
    if(opt == 'b') {
            bflag = !bflag;
        }
    else if(opt == 'r') {
            rflag = !rflag;
        }
    else if(opt == 'u') {
            uflag = !uflag;
        }
    else if(opt == 'l') {
            length = atoi(optarg);
            lflag = !lflag;
        }
	else if(opt == 'f') {
            filenm  =  strdup(optarg);
            fflag = !fflag;
        }
//  OOPS - AN UNKNOWN ARGUMENT
        else {
            argc = -1;
        }
    }

    if(argc <= 0) {    //  display program's usage/help   
        usage();
    }
    argc  -= optind;
    argv  += optind;

    if ( (bflag&&rflag&&uflag) | (bflag&&rflag) | (bflag&&uflag) | (uflag&&rflag) | (rflag&&lflag) ) {
        usage();
    }
    else if (fflag && !bflag && !rflag && !uflag && (argc == 1)) {
        printf("first invocation on cli supplied word: %s, in %s.\n", argv[0], filenm);
    }
    else if (bflag) {
        printf("second invocation, building trovefile [%s], with words of length %i, from: \n", filenm, length);
        FILE *fp;
        fp = fopen(filenm, "w");
        fclose(fp);
        char *fullpath = realpath(filenm, NULL);
        CHECK_ALLOC(fullpath);
        filenm = strdup(fullpath);

        for (int i=0;i<argc;i++) {
            scan_directory(argv[i]);
            for (int n=0 ; n<nfiles ; ++n) {
                read_file(files[n].pathname, length);
            }
        }
        write_trove();
    }
    else if (rflag) {
        printf("second invocation, remove files from {%s} that are found: \n", filenm);
        for (int i=0;i<argc;i++) {
            scan_directory(argv[i]);
        }
        read_trove(filenm);
        if (check_wipe()) {
            FILE *fp;
            fp  = fopen (filenm, "w");
            fclose(fp);
        }
        else {   
            update_trove(1);
        }
    }
    else if (uflag) {
        printf("second invocation, update [%s], with words of length %i, from: \n", filenm, length);
        for (int i=0;i<argc;i++) {
            scan_directory(argv[i]);
        }
        read_trove(filenm);
        if (check_wipe()) {
            write_trove();
        }
        else {
            update_trove(2);
            for (int n=0 ; n<nfiles ; ++n) {
                read_file(files[n].pathname, length);
            }
            write_trove();
        }
    }
    else {
        //usage();
        printf(" ");
    }


    return 0;
}