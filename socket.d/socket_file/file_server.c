#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	int read_cnt;
	int fd;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	socklen_t clnt_addr_size;
	char buffer[100];
	char message[]="Hello World!";
	//FILE *file;


	if(argc!=3) {	// argument가 3개가 아니면 printf
		printf("Usage : %s <port> <recv_file>\n",argv[0]);
		exit(1);
	}

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0){
		perror("socket()");
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))<0)
		error_handling("bind() error");

	if(listen(serv_sock, 5) < 0)
		error_handling("listen() error");

	clnt_addr_size=sizeof(clnt_addr);
	printf("clnt_addr_size : %u\n",clnt_addr_size);
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock < 0)
		error_handling("accept() error");
	
	fd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);//argument : [파일 이름 경로] [파일 열기 모드]
	if(fd < 0 )
		error_handling("open() error");

	

	//while ((read_cnt=read(clnt_sock, buffer, 100)) != 0){
	//	fwrite((void*)buffer,1,read_cnt,file);
	//	printf("read : %d\n", read_cnt);
	//}

	while(1){
		read_cnt=read(clnt_sock, buffer, 100);
		printf("read : %d\n", read_cnt);
		if(read_cnt==0)
			break;
		if(write(fd,buffer,read_cnt) <0)
			error_handling("write() error");

	}
	printf("Done..\n");

	sprintf(message, "hi");
	write(clnt_sock, message, strlen(message));
	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}

