/*
 * test_execvp.cpp
 *
 *  Created on: 2015年3月6日
 *      Author: zz
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
extern char **environ;

int main() {
	const char* file = "ls";
//	const char* args[] = {"sh", "/bin/ls . >> log 2>&1", NULL, ".", ">>", "log", "2>&1", NULL};

	//const char* args[] = {"./hello", NULL};
	//const char* args[] = {"sh", "./hello", ">>", "log", "2>&1", NULL};
	//	./hello: ./hello: cannot execute binary file
	const char* args[] = {"/root/workspace/win/zexec/test/hello", ">>", "log", "2>&1", NULL};

	int fd;
//	int maxfd = sysconf(_SC_OPEN_MAX);
//	for (fd = 0; fd < maxfd; ++fd) {
//		close(fd);
//	}

	fd = open("log", O_WRONLY|O_APPEND|O_CREAT, 0644);


	for (int i = 1; i <= 10; i++) {
		fprintf(stdout, "execvp: stdout %d\n", i);
	}

	for (int i = 1; i <= 10; i++) {
		fprintf(stderr, "execvp: stderr %d\n", i);
	}

	printf("================  before dup  ==================\n");
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	close(STDIN_FILENO);
	close(STDIN_FILENO);
	close(STDIN_FILENO);

	printf("================  after dup  ==================\n");
	for (int i = 1; i <= 10; i++) {
		fprintf(stdout, "execvp: stdout %d\n", i);
	}

	for (int i = 1; i <= 10; i++) {
		fprintf(stderr, "execvp: stderr %d\n", i);
	}

	execvp(args[0], (char* const*)args);
	perror("execvp:");
}


