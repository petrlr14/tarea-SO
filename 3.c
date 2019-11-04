#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    char *buf = malloc(1);    
    pid_t pid; 
    puts("Bienvenido/a a la consola pirata v0.9");
    printf("so@agave -> ");
    char **argv = (char **)malloc(sizeof(char *));
    while (1){
        fgets(buf, sizeof(char *), stdin);
        argv[0]=buf;
        argv[1]=NULL;

        pid = fork();
        if(pid == 0){
            
        //if(buf == "exit") break;
            
            execve(argv[0],argv,NULL);
        }else{
            wait(NULL);
            printf("so@agave -> ");
        }
        free(buf);
    }
    puts("Saliendo de la consola pirata v0.9"); 
    return 0;
}