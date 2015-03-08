/*
 * ZExec.cpp
 *
 *  Created on: 2015年3月6日
 *      Author: zz
 */

#include "zexec.h"
#include "zlog/zlog.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

extern char **environ;

ZExec::ZExec(const string& uid):m_uid(uid), m_pid(-1) {}

ZExec::~ZExec() {
	// TODO Auto-generated destructor stub
	m_pid = -1;
	kill();
}

void ZExec::setCmd(const char* cmd) {
	m_cmd = cmd;
}

void ZExec::setCmd(const string& cmd) {
	m_cmd = cmd;
}

void ZExec::setLogfile(const char* filepath) {
	m_logfile = filepath;
}

void ZExec::setLogfile(const string& filepath) {
	m_logfile = filepath;
}

pid_t ZExec::getPid(void) {
	return m_pid;
}

bool ZExec::isRuning() {
	if (m_pid > 0) {
		::kill(m_pid, 0);
		return true;
	}

	return false;
}

void ZExec::onExit(int status) {
	LOGD("%s exit with %d", m_uid.c_str(), status);
}


#define MAX_ARG_NUM 64
bool ZExec::run() {
	LOGA("begin");
	char* args[MAX_ARG_NUM] = {0};

	if (m_cmd.empty()) {
		LOGE("command is empty, exec_id = %s", m_uid.c_str());
		return false;
	}

	string cmd 	= m_cmd;
	int len 	= cmd.length();
	char* c_cmd	= const_cast<char*>(cmd.c_str());

	int i = 0;
	args[i] = c_cmd;
	for (int j = 0; j < len - 1; j++) {
		if (c_cmd[j] == ' ' && c_cmd[j+1] != ' ') {
			c_cmd[j] = '\0';
			args[++i] = c_cmd + j + 1;
		}
	}

	if (i >= MAX_ARG_NUM) {
		LOGE("cmd's args num too much, cmd = {%s}", m_cmd.c_str());
		return false;
	}

	args[++i] = NULL;

#if 0
	string debugArgs;
	for (int i = 0; args[i] != NULL; i++) {
		debugArgs += args[i];
	}
	LOGD("args : %s", debugArgs.c_str());
#endif

	int fd, maxfd;
	pid_t m_pid = vfork();
	if(m_pid == 0){//子进程
		maxfd = sysconf(_SC_OPEN_MAX);
		for (fd = 0; fd < maxfd; ++fd) {
			close(fd);
		}

		if (m_logfile.empty()) {
			fd = open("/dev/null", O_RDWR);
		} else {
			fd = open(m_logfile.c_str(), O_WRONLY|O_APPEND|O_CREAT, 0644);
		}

//		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);

		execvp(args[0], args);
		LOGE("execvp error:%m, please check command:%s", m_cmd.c_str());
		exit(-1); // fuck 不加此行导致 execvp 运行失败时，子进程继续运行，导致未知的错误
	}

	if (m_pid == -1) {
		return false;
	}

	LOGA("end");
	return true;
}

bool ZExec::kill() {
	if (isRuning()) {
		::kill(m_pid, SIGTERM);
		return true;
	}
	return false;
}
