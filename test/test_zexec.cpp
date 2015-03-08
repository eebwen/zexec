/*
 * test_zexec.cpp
 *
 *  Created on: 2015年3月6日
 *      Author: zz
 */

#include "../zexec.h"
#include <stdio.h>

int main(int ac, char* av[]) {
	ZExec exec("aaa");
//	exec.setCmd("ls");
//	exec.setLogfile("ls.log");

	exec.setCmd("loop_echo");
	exec.setLogfile("loop_echo.log");

	zlog_set_echo(1);
	zlog_set_strlevel("ALL");

	if (exec.run()) {
		printf("run success!!\n");
	} else {
		printf("run failed!\n");

	}

	return 0;
}


