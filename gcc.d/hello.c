#include <stdio.h>
#include <unistd.h>
#define PI 3.1415

int main(int argc, char * argv[]){
	printf("hello world\n");
	while (1) {
		sleep(1);
		printf("Hello World %lf\n",PI);
	}
	return 0;
}
