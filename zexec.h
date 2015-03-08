/*
 * ZExec.h
 *
 *  Created on: 2015年3月6日
 *      Author: zz
 */

#ifndef ZEXEC_H_
#define ZEXEC_H_

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include "zlog/zlog.h"
using std::string;

class ZExec {
public:
	ZExec(const string& m_uid);
	virtual ~ZExec();

	void setCmd(const char* cmd);
	void setCmd(const string& cmd);

	void setLogfile(const char* filepath);
	void setLogfile(const string& filepath);

	// 未运行返回 -1
	pid_t getPid(void);

	// 检查程序是否在运行
	bool isRuning();

	// 程序退出时调用, status 为退出码
	virtual void onExit(int status);

	virtual bool run(); 	// 启动
	virtual bool kill();	// 退出

private:
	pid_t  m_pid;

	string m_uid;  // 任务标识
	string m_cmd;  // 启动命令
	string m_logfile; // 子进程的日子输出
};

#endif /* ZEXEC_H_ */
