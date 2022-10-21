#include "trove.h"

void read_compressed() {

	int fd[2];
	if (pipe(fd) == -1) {
		perror("pipe");
	}
	int pid = fork();
	if (pid<0) {
		perror("fork");
	}
	if (pid == 1) {
		// CHILD PROCESS
		// close(fd[0]);

		char buf[BUFSIZ];

		int n = strlen(filenm) + 1;

		write(fd[1], &n, sizeof(int));

		write(fd[1], filenm, sizeof(char) * n);

		read(fd[0], buf, BUFSIZ);

		close(fd[0]);

		close(fd[1]);

		printf("%s\n", buf);

		wait(NULL);
	}
	else if (pid == 0) {//child
		// parent process

		char buf[BUFSIZ];

		char par_str[200];
		int n;

		read(fd[0], &n, sizeof(int));

		read(fd[0], par_str, sizeof(char) * n);

        dup2(fd[1], STDIN_FILENO);
        // close(fd[1]);

        int i = execl("/usr/bin/zcat","/usr/bin/zcat", par_str, (char*)NULL);
        printf("%i\n", i);
		if (i<0) {
			perror("execl");
		}
		perror("/usr/bin/zcat");

        exit(EXIT_FAILURE);

		dup2( fd[1], STDOUT_FILENO);
		read(fd[0], buf, BUFSIZ);
		write(fd[1], buf, BUFSIZ);

		close(fd[1]);
		close(fd[0]);

		// wait(NULL);
	}
}