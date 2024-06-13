#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>

//LYJ

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	int str_len;
	int read_cnt;
	int fd=0;
	struct sockaddr_in serv_addr;
	
	char buffer[100]={0};
	char message[30];

//	FILE *file;

	if(argc!=4){
		printf("Usage : %s <IP> <port> <recv_name>\n", argv[0]);
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

	fd = open(argv[3], O_RDONLY);
	if(fd < 0){
		//error_handling("fopen() error");
		printf("<%s> file open error\n", argv[3]);
		printf("open : %s\n", strerror(errno));
		exit(1);
	}

	while ((read_cnt = read(fd, buffer,sizeof(buffer))) >0)
		write(sock, buffer, read_cnt);

	printf("Done...\n");

	shutdown(sock,SHUT_WR);
	str_len=read(sock, message, sizeof(message)-1);

	if(str_len < 0){
		error_handling("read() error");
	}else{
		buffer[str_len]=0;
		printf("Message from server: %s \n",message);	
	}

	read(sock, buffer, 100);
	
	close(fd);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
