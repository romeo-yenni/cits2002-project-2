//  NICOLAS GOPCEVIC - 22982458
//  HARRY ADLER      - 21968333

// FILE COMPRESSION HAS BEEN IMPLEMENTED WHEREAS READING OF COMPRESSED FILES HAS NOT
// ALL FEATURES WORKING WHEN USING AN UNCOMPRESSED TROVE-FILE

// ON LINE 99 THE COMPRESS FUNCTION HAS BEEN COMMENTED 
// TO TEST COMPRESSION NEED TO UNCOMMENT COMPRESS() AND COMMENT LINE 17 OF WRITE_TROVE.C

#include "trove.h"

FILES *files  = NULL;
int nfiles  = 0;

WORDS *wordstruc = NULL;
int nwords = 0;

T_PATHS *paths = NULL;
int npaths = 0;

SEARCH *search = NULL;
int nsearch = 0;

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
        read_trove(filenm);
        search_trove(argv[0]);
    }
    else if (!fflag && !bflag && !rflag && !uflag && (argc == 1)) {
        read_trove(filenm);
        search_trove(argv[0]);
    }
    else if (bflag) {

        for (int i=0;i<argc;i++) {
            scan_directory(argv[i]);
            for (int n=0 ; n<nfiles ; ++n) {
                read_file(files[n].pathname, length);
            }
        }
        write_trove();
        // compress();
    }
    else if (rflag) {
        for (int i=0;i<argc;i++) {
            scan_directory(argv[i]);
        }
        read_trove(filenm);
        check_within();
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
        usage();
    }
    return 0;
}