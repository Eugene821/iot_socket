#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

//int main(int argc, char *argv[])
int main(int argc, char ** argv)
{
	int n, in, out;
	char buf[100];
	int i,j;
	int a=10;
	int b=20;

	printf(" %s ,  %p\n","hello","hello");

	printf("%d / %d = %lf\n", a, b, (double)a/b*100);
	

	for(i=0; i<argc;i++)
	{
		printf("argv[%d] : %s\n",i, argv[i]);
	
		for (j=0;j<strlen(argv[i]);j++)
			printf("%c\n", argv[i][j]);
		printf("\n");
	}
	

	if(argc < 3) {
		write(fileno(stderr), "Usage : copy file1 file2\n",25);
		return 1;
	}
	if((in = open(argv[1], O_RDONLY)) < 0) {
		perror(argv[1]);
		return 2;
	}
	//if((out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
	if((out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR)) < 0) {

		perror(argv[2]);
		return 3;
	}

	while(1) {
		n=read(in,buf,sizeof(buf));
  		printf("n:%d\n",n);
		if(n<=0)
			break;
		write(out,buf,n);
	}
	close(out);
	close(in); 
	return 0;
}
