#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void createSon();

/* Escribir N como parametro en la linea de comando */

int main(int argc, char*argv[]){
  int arg= atoi(argv[1]);
  printf("dad: %d\n", getpid());
  createSon(arg, arg);
  return 0;
}

void createSon(int count, int arg){
  if(count==0){
    return;
  }
  if(!fork()){
    for(int i=arg; i>=count; i--){
      printf("\t");
    }
    printf("dad: %d\n", getppid());
    for(int i=arg; i>=count; i--){
      printf("\t");
    }
    printf("son: %d\n", getpid());
  }else{
    wait(NULL);
  }
  createSon(--count, arg);
}
