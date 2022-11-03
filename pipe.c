//pipe pingpng between parent and child
// comment
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int atgc,char* argv[]){
    int pi1[2];
    int pi2[2];
    int pi3[2];
    int pi4[2];
    
    int number;
    
    int p1 = pipe(pi1);
    int p2 = pipe(pi2);
    int p3 = pipe(pi3);
    int p4 = pipe(pi4);
    
    if (p1 < 0 || p2 < 0)
    {
        printf("pipe failed");
        exit(1);
    }
    
    //int childS;
    pid_t pid = fork();
    
    
	if(pid < 0) {
		printf("fork failed");
		exit(1);
	} else if (pid == 0) {	
	//grandchild process
	  pid_t pidg = fork();
	  
	  if (pidg < 0){
	  printf("fork failed");
		exit(1);
	  }
	  else if (pidg == 0){
	  while(1){
	    sleep(1);
	    read(pi1[0],&number,sizeof(number));
	    sleep(1);
	    write(pi3[1],&number,sizeof(number));
	    sleep(5);
	    printf("Grand child Received, %d\n", number);
	    //--- pipe between grand child and child
	    read(pi4[0],&number,sizeof(number));
	    sleep(1);
	    write(pi2[1],&number,sizeof(number));
	    printf(" child Received, %d\n", number);  
	    }
	  } 
	  else{
	    while(1){
	    
	    //--- pipe between child and grandchild
	    sleep(1);
	    read(pi3[0],&number,sizeof(number));
	    sleep(1);
	    write(pi4[1],&number,sizeof(number));
	    //printf("Grand child Received, %d\n", number);
	    
	    

	    }
	    }
		
	} else {
	    number = 12;	
		while(1){
		number++;
		write(pi1[1],&number,sizeof(number));
		sleep(5);
		read(pi2[0],&number,sizeof(number));
		printf("parent Received, %d\n", number);

		}
	}
	return 0;



}
