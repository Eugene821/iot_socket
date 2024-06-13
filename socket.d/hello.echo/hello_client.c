#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[100]={0};
	int str_len;
	int recv_cnt;
	int recv_len;
	int loopFlag=1;

	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock < 0)
		error_handling("socket () error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		error_handling("connect() error");

	//strcpy(message,"hello server LYJ");
	//fgets(message, sizeof(message)-1, stdin);
	//message[sizeof(message)-1] = '\0';
		
	printf("input a message!\n");
	do{	
		fgets(message, sizeof(message)-1, stdin);
		message[strlen(message)-1] = '\0'; //'\n' 제거
		if(!strcmp(message,"quit"))
			break;
		str_len=write(sock, message, strlen(message));
		memset(message, 0x00, sizeof(message));
		recv_len=0;

		do {
			recv_cnt = read(sock, &message[recv_len], sizeof(message)-1);
			if(recv_cnt <=0)
			{
				loopFlag =0;
				break;
			}
			printf("recv_cnt : %d\n", recv_cnt);
			recv_len +=recv_cnt;//recv_len = recv_len + recv_cnt
		
		} while(recv_len < str_len);
		printf("Message from server: %s \n",message);	

	} while(loopFlag);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
