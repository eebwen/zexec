/*
 * hello.c
 *
 *  Created on: 2015年3月6日
 *      Author: zz
 */

#include <stdio.h>

int main(int argc, char** argv){
	for (int i = 0; argv[i] != NULL; i++) {
		fprintf(stdout, "%s ", argv[i]);
	}
	fprintf(stdout, "\n");

	int count = 10;
	for (int i = 1; i <= 10; i++) {
		fprintf(stdout, "hello: stdout %d\n", i);
	}

	for (int i = 1; i <= 10; i++) {
		fprintf(stderr, "hello: stderr %d\n", i);
	}

	return 0;
}
