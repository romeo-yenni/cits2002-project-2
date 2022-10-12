#include "trove.h"

FILES *files  = NULL;
int nfiles  = 0;

int main(int argc, char *argv[])
{
    if(argc > 1) {
//  SCAN EVERY DIRECTORY REQUESTED ON THE COMMAND-LINE
	for(int a=1 ; a<argc ; ++a) {
	    scan_directory(argv[a]);
	}

        list_all_files();
    }

    return 0;
}
