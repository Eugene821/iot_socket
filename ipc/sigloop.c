#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void signal_hander(int signo) { // 시그널 핸들러 정의 
	if(signo == SIGINT)
	{
        printf("Catch SIGINT!, but no stop %d\n",signo);
//		exit(0);
	}
	else if(signo == SIGALRM)
    	printf("Catch SIGALRM!  %d\n",signo);
}

int main(void) {
        if (signal(SIGINT, signal_hander) == SIG_ERR) { // 핸들러 에러처리
                printf("Can't catch SIGINT! \n");
                exit(1);
        }
        if (signal(SIGALRM, signal_hander) == SIG_ERR) { // 핸들러 에러처리
                printf("Can't catch SIGALARM! \n");
                exit(1);
        }
        for (;;) // 무한루프 
		{
                pause();
//				sleep(2);
				alarm(2);
		}
        return 0;
}
