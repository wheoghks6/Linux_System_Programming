#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#define MAX_CMD_ARG 10
#define BUFSIZ 256

const char* prompt = "myshell> ";
char* cmdvector[MAX_CMD_ARG];
char  cmdline[BUFSIZ];

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

void exe_cmd(int cnt)
{
	int open_null;
	int stdouttonull;
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
			waitpid(pid, NULL, 0);

		}
	}
	return 0;
}