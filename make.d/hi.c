#include <stdio.h>
int input();
int output(int);
int main() {
	int n = input();
	if(!(output(n)))
		printf("Good Bye\n");
	return 0;
}

