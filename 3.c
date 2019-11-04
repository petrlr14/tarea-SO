#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void splitter(){

}

int main(void){
    int c = 0;
    char *buf = malloc(1);    
    char **argv = (char **)malloc(sizeof(char *));
    char delim[1];
    delim[0]=' ';
    pid_t pid; 
    puts("Bienvenido/a a la consola pirata v0.9 \n");
    printf("so@agave -> ");
    while (1){
        fgets(buf, sizeof(char *), stdin);
        if(!strcmp(buf,"exit")) break; 
        argv[0]=strtok(buf, delim);
        while (argv[c] != NULL ){
            c++;
            argv[c] = strtok(NULL, delim);
        }
        argv[c+1]=NULL;

        pid = fork();
        if(pid == 0){
            execve(argv[0],argv,NULL);
        }else{
            wait(NULL);
            printf("so@agave -> ");
        }
        free(buf);
        c=0;
    }
    puts("Saliendo de la consola pirata v0.9"); 
    return 0;
}