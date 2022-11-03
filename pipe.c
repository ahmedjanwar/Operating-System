#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAX 10

int main()
{

int fd[2];
pipe(fd);
pid_t pid = fork();
int number;

if( pid == 0 ) {//child
	 number = 5;
	
	close(fd[0]);
	// fd[0] read  and fd[1] write
	
	close(1);	

	dup(fd[1]);
	write(1, &number, sizeof(number));
}
else if(pid > 0) {
	wait(NULL);
	printf("child process finished \n");	
	close(0);

	close(fd[1]);

	dup(fd[0]);
	int arr[MAX];
	
	read(fd[0],&number, sizeof(number));
	number++;
	printf("Values from child process:\n");
	printf("Value is: %d \n",number);
}
else {
	perror("error\n"); //fork()
	
     }
}

