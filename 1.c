#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void createSon();

int main(int arg){
  printf("dad: %d\n", getpid());
  createSon(arg, arg);
  return 0;
}

void createSon(int count, int arg){
  if(count==0){
    return;
  }
  int child=fork();
  if(!child){
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
