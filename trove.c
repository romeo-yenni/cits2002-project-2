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

//  AS DISCUSSED IN WORKSHOP-7 :
#define	CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

typedef struct {
    char        *pathname;
} FILES;

FILES           *files  = NULL;
int             nfiles  = 0;

// print out all files with full paths
void list_all_files(void) {
    for(int n=0 ; n<nfiles ; ++n) {
        printf( "%s\n", files[n].pathname );
    }
}

void scan_directory(char *dirname) {
    DIR             *dirp;
    struct dirent   *dp;

//  ENSURE THAT WE CAN OPEN (read-only) THE REQUIRED DIRECTORY
    dirp       = opendir(dirname);
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }

//  READ FROM THE REQUIRED DIRECTORY, UNTIL WE REACH ITS END
    while((dp = readdir(dirp)) != NULL) {
    
    	if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
    
	struct 		stat stat_info;
        char            pathname[MAXPATHLEN];
        
        sprintf(pathname, "%s/%s", dirname, dp->d_name);
        
        
//  DETERMINE ATTRIBUTES OF THIS DIRECTORY ENTRY
        if(stat(pathname, &stat_info) != 0) {
            perror( pathname );
            exit(EXIT_FAILURE);
        }
        
        stat(pathname, &stat_info);
	
	if ( S_ISDIR(stat_info.st_mode) ) {
		scan_directory(pathname);
		continue;
	}
	

//  EXTEND OUR ARRAY OF STRUCTURES BY ONE ELEMENT
	files                   = realloc(files, (nfiles+1)*sizeof(files[0]));
	CHECK_ALLOC(files);			// ensure allocation was OK

//  REMEMBER (COPY) THIS ELEMENT'S RELATIVE PATHNAME
	files[nfiles].pathname  = strdup(pathname);
	CHECK_ALLOC(files[nfiles].pathname);	// ensure allocation was OK

	++nfiles;
    }

//  CLOSE THE DIRECTORY
    closedir(dirp);
}

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
