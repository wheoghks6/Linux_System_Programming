#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#define MAX_CMD_ARG 10
#define BUFSIZ 256

const char* prompt = "myshell> ";
char* cmdvector[MAX_CMD_ARG];
char* commands[MAX_CMD_ARG];
char* cmdlist[MAX_CMD_ARG];
char  cmdline[BUFSIZ];

struct sigaction act;

void fatal(char* str) {
	perror(str);
	exit(1);
}

int check_background(int cnt)
{
	int i;

	for (i = 0; i < cnt; i++)
	{
		if (!strcmp(cmdvector[i], "&"))
		{
			cmdvector[i] = NULL;
			return 1;
		}
	}

	return 0;
}
void redirection(char* cmd)
{
	char* target;
	int len = strlen(cmd);
	int fd, i;

	for (i = len - 1; i >= 0; i--)
	{
		switch (cmd[i])
		{
		case '<':
			target = strtok(&cmd[i + 1], " \t");
			if ((fd = open(target, O_RDONLY | O_CREAT, 0644)) < 0)
				fatal("error : file open error");

			dup2(fd, STDIN_FILENO);
			close(fd);
			cmd[i] = '\0';
			break;
		case '>':
			target = strtok(&cmd[i + 1], " \t");
			if ((fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
				fatal("error : file open error");

			dup2(fd, STDOUT_FILENO);
			close(fd);
			cmd[i] = '\0';
			break;
		default:
			break;
		}
	}
}

int makelist(char* s, const char* delimiters, char** list, int MAX_LIST) {
	int i = 0;
	int numtokens = 0;
	char* snew = NULL;

	if ((s == NULL) || (delimiters == NULL)) return -1;

	snew = s + strspn(s, delimiters);	/* Skip delimiters */
	if ((list[numtokens] = strtok(snew, delimiters)) == NULL)
		return numtokens;

	numtokens = 1;

	while (1) {
		if ((list[numtokens] = strtok(NULL, delimiters)) == NULL)
			break;
		if (numtokens == (MAX_LIST - 1)) return -1;
		numtokens++;
	}
	return numtokens;
}

int cd_exe(int cmd_num, char** cmdvec) {
	if (cmd_num == 1)
		chdir(getenv("Home"));
	else if (cmd_num == 2) {
		if (chdir(cmdvec[1]))
			printf("No directory\n");
	}
	else
		printf("Error\n");
	return 1;
}

void zombie_controller(int signo) {
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0);
}

void excute_cmd(char* command)
{
	redirection(command);
	makelist(command, " \t", cmdvector, MAX_CMD_ARG); //실행할 명령어
	execvp(cmdvector[0], cmdvector);

}

void exe_cmd(char * cmdgrp, int numtokens)
{
	int open_null;
	int stdouttonull;
	int pipe_count;
	int p[2];
	int i = 0;
	
	setpgid(0, 0);
	int check_back = check_background(numtokens);
	
	if (!check_back)
	{
		tcsetpgrp(STDIN_FILENO, getpid());
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);

	pipe_count = makelist(cmdgrp, "|", cmdlist, MAX_CMD_ARG); // pipe 분류

	for(i=0; i<pipe_count -1; i++)
	{
		pipe(p);
		switch (fork())
		{
		case -1:
			fatal("Error calling fork()");
		case 0:
			close(p[0]);
			dup2(p[1], STDOUT_FILENO);
			excute_cmd(cmdlist[i]);
		default:
			close(p[1]);
			dup2(p[0], STDIN_FILENO);
		}
	}
	excute_cmd(cmdlist[i]);

}



int main(int argc, char** argv) {
	int i = 0;
	pid_t pid;
	int numtokens;
	int command_count = 0;
	char command_temp[BUFSIZ];
	memset(&act, 0, sizeof(act));
	act.sa_handler = zombie_controller;
	act.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &act, NULL);

	signal(SIGINT, SIG_IGN); //외부입력들에 대한 signal들 처리
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);


	while (1) {

		fputs(prompt, stdout);
		fgets(cmdline, BUFSIZ, stdin);
		if (cmdline[0] == '\n' || cmdline[0] == '\0')
			continue;

		cmdline[strlen(cmdline) - 1] = '\0';
		command_count = makelist(cmdline, ";", commands, MAX_CMD_ARG); //;단위 명령어 분할

		for (int i = 0; i < command_count; i++)
		{
			memcpy(command_temp, commands[i], strlen(commands[i]) + 1);
			numtokens = makelist(commands[i], " \t", cmdvector, MAX_CMD_ARG); //화이트 스페이스 분할
			if (strcmp(cmdvector[0], "exit") == 0) {
				exit(-1);
			}
			else if (strcmp("cd", cmdvector[0]) == 0) {
				cd_exe(numtokens, cmdvector);
				continue;
			}

			switch (pid = fork()) {
			case -1:
				fatal("main()");
				break;
			case 0:
				exe_cmd(command_temp, numtokens);
			default:
				if (check_background(numtokens))
				{
					break;
				}
				tcsetpgrp(STDIN_FILENO, pid);
				waitpid(pid, NULL, 0);
				tcsetpgrp(STDIN_FILENO, getpgid(0));
				fflush(stdout);

			}
		}
	}
	return 0;
}