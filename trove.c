#include "trove.h"

FILES *files  = NULL;
int nfiles  = 0;

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
            char *fullpath = realpath(optarg, NULL);
            CHECK_ALLOC(fullpath);
            filenm  =  strdup(fullpath);
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
/**
//  SCAN EVERY DIRECTORY REQUESTED ON THE COMMAND-LINE
    if (fflag) {
	scan_directory(filenm);

    list_all_files();

    }
    **/
    if ( (bflag&&rflag&&uflag) | (bflag&&rflag) | (bflag&&uflag) | (uflag&&rflag) | (rflag&&lflag) ) {
        usage();
    }
    else if (fflag && !bflag && !rflag && !uflag && (argc == 1)) {
        printf("first invocation on cli supplied word: %s, in %s.\n", argv[0], filenm);
    }
    else if (!fflag && !bflag && !rflag && !uflag && (argc == 1)) {
        printf("first invocation on cli supplied word: %s, in %s.\n", argv[0], filenm);
    }
    else if (bflag) {
        printf("second invocation, building trovefile [%s], with words of length %i, from: \n", filenm, length);
        for (int i=0;i<argc;i++) {
            scan_directory(argv[i]);
        }
        list_all_files();
    }
    else if (rflag) {
        printf("second invocation, remove files from {%s} that are found: \n", filenm);
        for (int i=0;i<argc;i++) {
            printf("-: %s\n", argv[i]);
        }
    }
    else if (uflag) {
        printf("second invocation, update [%s], with words of length %i, from: \n", filenm, length);
        for (int i=0;i<argc;i++) {
            printf("-: %s\n", argv[i]);
        }
    }
    else {
        //usage();
        printf(" ");
    }


    return 0;
}