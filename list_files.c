#include "trove.h"

// print out all files with full paths
void list_all_files(void) {
    for(int n=0 ; n<nfiles ; ++n) {
        printf( "%s\n", files[n].pathname );
    }
}


void scan_directory(char *dirname) {

    struct stat path_stat;
    stat(dirname, &path_stat);
    if ( S_ISREG(path_stat.st_mode) ) {

        char *fullpath = realpath(dirname, NULL);
        CHECK_ALLOC(fullpath);

        files                   = realloc(files, (nfiles+1)*sizeof(files[0]));
        CHECK_ALLOC(files);			

        files[nfiles].pathname  = strdup(fullpath);
        CHECK_ALLOC(files[nfiles].pathname);	
        ++nfiles;
    }
    else {

        DIR             *dirp;
        struct dirent   *dp;

        dirp       = opendir(dirname);
        if(dirp == NULL) {
            perror( dirname );
            exit(EXIT_FAILURE);
        }

        while((dp = readdir(dirp)) != NULL) {
        
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
                continue;
            }
        
            struct 		stat stat_info;
            char            pathname[MAXPATHLEN];
            
            sprintf(pathname, "%s/%s", dirname, dp->d_name);
            
            
            if(stat(pathname, &stat_info) != 0) {
                perror( pathname );
                exit(EXIT_FAILURE);
            }
            
            stat(pathname, &stat_info);
        
            if ( S_ISDIR(stat_info.st_mode) ) {
                scan_directory(pathname);
                continue;
            }
	

            files                   = realloc(files, (nfiles+1)*sizeof(files[0]));
            CHECK_ALLOC(files);		

            files[nfiles].pathname  = strdup(pathname);
            CHECK_ALLOC(files[nfiles].pathname);	

            ++nfiles;
        }

    closedir(dirp);
    }
}