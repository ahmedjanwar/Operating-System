#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//this program need sign handler sigchild
int main(){
	pid_t pid;
	pid = fork();
	if (pid==0){
	printf("Hello from child process!\n");
	printf("The child exiting now!\n");
	}
	else if(pid>0){
	printf("Hello from parnt pid %d\n",getpid());
	printf("the forked %d\n",pid);
	sleep(60);
	// this creates zombie process it gives un necessary process and it is harm for big projects
	// Zombie process the os creates empty process to fill the 60sec gap
	printf("parent exit\n");
	}
	else
	printf("error forking\n");
	return 0;
}
