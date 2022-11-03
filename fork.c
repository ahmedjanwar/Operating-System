#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int chilExitStatus,chilExitStatus2;
	pid_t  ws,ws2;

	pid_t pid1;
	pid_t pid2;
	
	pid1 = fork();
	
	if (pid1==0){
		printf("Hello from First child process!\n");
		pid2 = fork();
	if (pid2 ==0){
		printf("Hello from Second child process!\n");
		sleep(2);
		printf("The Second child exiting now!\n");
	}
	else if(pid2>0){
		wait(0);
		printf("code of first child acting as parent to second child!\n");
		printf("child 2  forked %d\n",pid2);
	}
		printf("The First child exiting now!\n");
	}
	else if(pid1>0){
	wait(0);
	printf("Hello from Main parnt pid %d\n",getpid());
	printf("child 1  forked %d\n",pid1);
	//printf("child 2  forked %d\n",pid2);
	
	sleep(5);
	printf("code accesable for all\n");
	printf("parent exit\n");
	}
	else
		printf("error forking\n");
	return 0;
}
