#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSGSIZE 255

char* msg = "Hello Child Process!";
int main()
{
        char buf[255];
        int fd[2], pid, nbytes;
        if(pipe(fd) < 0) // pipe(fd)로 파이프 생성
                exit(1);
        pid = fork(); // 이 함수 실행 다음 코드부터 부모/자식 프로세스로 나뉨
        if (pid > 0) { // 부모 프로세스에는 자식프로세스의 pid값이 들어감
                printf("parent PID: %d, child PID: %d\n", getpid(), pid);
//                write(fd[1], msg, MSGSIZE); // fd[1]에 write한다.
                write(fd[1], msg, strlen(msg)); // fd[1]에 write한다.
                exit(0);
        }
        else { // 자식프로세스에는 pid값이 0이 됨
                printf("child PID: %d\n", getpid());
                nbytes = read(fd[0], buf, MSGSIZE); // fd[0]을 읽음
                printf("%d %s\n", nbytes, buf);
                exit(0);
        }
        return 0;
}
