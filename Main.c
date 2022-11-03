

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
int main()
{
		char *args[]={"./hello","./world",NULL};
		int chilExitStatus;
		pid_t  ws;
		
		int ch;
		int exit = 1;
		
		while(exit==1){
		printf("1-hello\n");
		printf("2-world\n");
		printf("0-Exit loop\n");
		scanf("%d",&ch);
				if(ch==0){
					printf("Bye!\n");
					break;
			//exit=0;
		}
		
		pid_t pID = fork();
		/*child*/
		if(pID ==0){
			
			if(ch==1)
				execv(args[0],args);//add execv error checker from notes
			
			else if(ch==2)
				execv(args[1],args);
		}
		else if(pID < 0){
			printf("faildto fork");
			//exit(1);
		}
		/*Parent*/
		else{
			ws = waitpid(pID,&chilExitStatus,WUNTRACED); 
			printf("program exits from parent pid was %d\n",ws);
		}
			

		printf("Ending-----\n");
		
		}
	
	return 0;
}

