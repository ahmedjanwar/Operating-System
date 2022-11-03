#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <signal.h>

void sighandler(int signo, siginfo_t *info, void *context) {
	printf("In signal handler for signal %d\n", signo);
}


int main() {


    struct sigaction act = { 0 };    
    act.sa_sigaction = &sighandler;

    if (sigaction(SIGINT, &act, NULL) == -1) {
        perror("sigaction");
        exit(-1);
    }

    while(1){
        sleep(1);
    }

  return 0;
}
