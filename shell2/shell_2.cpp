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

void exe_cmd(int cnt)
{
	int open_null;
	int stdouttonull;

	setpgid(0, 0);
	if (!check_background(cnt))
	{
		tcsetpgrp(STDIN_FILENO, getpid());
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);

	if (check_background(cnt))
	{
		switch (fork())
		{
		case -1:
			fatal("Error calling fork()");
		case 0:
			open_null = open("/dev/null", O_RDWR);
			stdouttonull = dup2(open_null, 1);
			execvp(cmdvector[0], cmdvector);
		default:
			exit(1);
		}
	}
	execvp(cmdvector[0], cmdvector);

}

int main(int argc, char** argv) {
	int i = 0;
	pid_t pid;
	int numtokens;

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

		numtokens = makelist(cmdline, " \t", cmdvector, MAX_CMD_ARG);
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
			exe_cmd(numtokens);
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
	return 0;
}