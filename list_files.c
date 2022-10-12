#include "trove.h"

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