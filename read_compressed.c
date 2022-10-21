#include "trove.h"

void read_compressed() {

    int fd[2];
    pid_t pid;
    // FILE *fdin;

    pipe(fd);

    // error handling
    if ((pid = fork()) == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // parent load file, write to pipe
    if (pid != 0){
        close(fd[0]);

        char buf[BUFSIZ];
        buf[0] = '\0';

        // FILE *fp;
        // fp  = fopen (filenm, "w");

        for (int i=0;i<nwords;i++) {
            // THINK OF SOMETHING LATER....
            char line[200];
            line[0] = '\0';

            sprintf(line, "%s %s\n", wordstruc[i].word, wordstruc[i].filepath);

            // fputs(line, fp);

            strcat(buf, line);
        }

        buf[strlen(buf)-1] = '\0';

        // printf("%s\n", buf);

        int   BufferSize = strlen(buf) + 1;

        /* Reserve memory for your readed buffer */
        char* readedBuffer = malloc(BufferSize);
        CHECK_ALLOC(readedBuffer);

        write(fd[1], buf, BufferSize);
        close(fd[1]);
    }
	// child process
    else if (pid == 0){
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

		int trove    = open(filenm, O_WRONLY | O_CREAT, 0644);
        dup2(trove, 1);
  		close(trove);

		
        int i = execl("/usr/bin/gzip","/usr/bin/gzip", (char*)NULL);
        printf("%i\n", i);
		if (i<0) {
			perror("execl");
		}

		perror("/usr/bin/gzip");

        exit(EXIT_FAILURE);
    }

    // wait child
    wait(NULL);

}


// parents writes compressed file to pipe
// child reads pipe and calls zacat to read the compressed file
