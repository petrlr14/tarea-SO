#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void splitter(){

}

int main(void){
    int c = 0;
    char *buf = malloc(1);    
    char **argv = (char **)malloc(sizeof(char *));
    char delim[1];
    delim[0]=' ';
    pid_t pid; 
    puts("Bienvenido/a a la consola pirata v0.9 \nUtilice Ctrl + C para salir\n");
    printf("so@agave -> ");
    while (1){
        buf = malloc(1);
        fgets(buf, sizeof(char *), stdin);
        if(strcmp(buf,"exit")==10) break; 
        argv[0]=strtok(buf, delim);
        while (argv[c] != NULL ){
            c++;
            argv[c] = strtok(NULL, delim);
        }
        argv[c+1]=NULL;

        pid = fork();
        if(pid == 0){
            execve(argv[0],argv,NULL);
            kill(getpid(), SIGTERM);
        }else{
            wait(NULL);
            free(buf);
            printf("so@agave -> ");
        }
        c=0;
    }
    puts("Saliendo de la consola pirata v0.9"); 
    return 0;
}