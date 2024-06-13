#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int fatal(char *s);
static void signal_hander(int signo)
{
	if(signo == SIGINT)
		printf("Catch SIGINT!, but no stop  %d\n", signo);
	else if(signo==SIGALRM)
		printf("Catch SIGALRM! %d\n", signo);
	else if(signo==SIGUSR1)
		printf("Catch SIGUSR1! %d\n", signo);
}
int main(void)
{
	pid_t pid;
	int status;
	char *argv[] = {"ls","-l",NULL};
	if(signal(SIGINT, signal_hander)==SIG_ERR)
	{
		printf("Can`t catch SIGINT! \n");
		exit(1);
	}
	if(signal(SIGALRM, signal_hander)==SIG_ERR)
	{
		printf("Can`t catch SIGALARM! \n");
		exit(1);
	}
	if(signal(SIGUSR1, signal_hander)==SIG_ERR)
	{
		printf("Can`t catch SIGUSER1! \n");
		exit(1);
	}
	for(;;)
	{
		sleep(2);
		kill(0,SIGUSR1);
		alarm(2);
	}

	return 0;
//	switch(pid = fork())
//	{
//		case -1:
//			fatal("fork failed.\n");
//			break;
//		case 0:
//			sleep(60);
//			execl("/bin/ls","ls","-l",NULL);
//			execlp("ls","ls","-l",NULL);
//			execv("/bin/ls",argv);
//			fatal("exec failed\n");
//			break;
//		default:
//			wait((int *)0);
//			kill(pid, SIGUSR1);
//			wait(&status);
//			printf("ls completed %d\n",status >> 8);
//			exit(0);
//	}
}
int fatal(char *s)
{
	perror(s);
	exit(1);
}
