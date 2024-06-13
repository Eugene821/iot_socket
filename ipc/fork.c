#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int fatal(char *s);
int main(void)
{
	pid_t pid;
	int status;
	char *argv[] = {"ls","-l",NULL};
	switch(pid = fork())
	{
		case -1:
			fatal("fork failed.\n");
			break;
		case 0:
//			sleep(60);
//			execl("/bin/ls","ls","-l",NULL);
//			execlp("ls","ls","-l",NULL);
			execv("/bin/ls",argv);
			fatal("exec failed\n");
			break;
		default:
//			wait((int *)0);
			wait(&status);
			printf("ls completed %d\n",status >> 8);
			exit(0);
	}
}
int fatal(char *s)
{
	perror(s);
	exit(1);
}
