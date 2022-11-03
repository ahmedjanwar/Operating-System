#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
    int pipe1[2];
    int pipe2[2];
    char str[8], str1[8];
    pid_t pid;

    if(pipe(pipe1) < 0){
        perror("Pipe 1 not created\n");
        exit(EXIT_FAILURE);
    }

    if(pipe(pipe2) < 0){
        perror("Pipe 2 not created\n");
        exit(EXIT_FAILURE);
    } 

    pid = fork();

    if (pid == 0){
        close(pipe1[1]);
        close(pipe2[0]);
        printf("\nChild Process");
        ssize_t rd_stat_child = read(pipe1[0], str, 8*sizeof(char));
        if(rd_stat_child > 0){
            printf("rc%zd\n", rd_stat_child);
            for(int i = 0; i < 4; i++){
                str[i] = ((char)(((int)str[i])-32));
            }

            printf("\nFinal str in child: %s\n", str);
            ssize_t wr_stat_child = write(pipe2[1], str, 8*sizeof(char));
            printf("wc%zd\n", wr_stat_child);
            if(wr_stat_child != sizeof(str)){
                perror("Sending to parent failed");
                exit(EXIT_FAILURE);
            }
        }else{
            perror("Child failed to read");
            exit(EXIT_FAILURE);
        }

    }else if (pid > 0){
        close(pipe1[0]);
        close(pipe2[1]);
        printf("\nParent Process");
        printf("\nEnter a 8 character string: ");
        scanf("%8s", str);
        if(sizeof(str)/(8*sizeof(char)) != 1){
            perror("Size of string greater than 8\n");
            exit(EXIT_FAILURE);
        }else{
            ssize_t wr_stat_parent = write(pipe1[1], str, 8*sizeof(char));
            printf("wp%zd\n", wr_stat_parent);
            if(wr_stat_parent != sizeof(str)){
                perror("Parent failed writing.\n");
                exit(EXIT_FAILURE);
            }
            ssize_t rd_stat_parent = read(pipe2[0], str, 8*sizeof(char));
            close(pipe2[0]);
            if(rd_stat_parent <= sizeof(str)){
                printf("rp%zd\n", rd_stat_parent);
                printf("\nParent Recieved\n %s", str);
            }else{
                perror("Parent error while reading\n");
                exit(EXIT_FAILURE);
            }

        }
    }

    return 0;
}
