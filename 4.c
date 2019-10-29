#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

struct Node{
  int data;
  struct Node* next;
  struct Node* prev;
};

struct Node* head;



int main(int argc, char*argv[]){
  int N = atoi(argv[1]);
  int fd[2], process[N];
  int hijo;
  pipe(fd);
  for(int i=0; i<N; i++){
    if(!fork()){
      hijo = getpid();
      close(fd[0]);
      close(1);
      dup(fd[1]);
      write(1, &hijo, sizeof(hijo));
      exit(0);
    }else{/* daddy */
      close(0);
      close(fd[1]);
      dup(fd[0]);
      read(fd[0], &hijo, sizeof(hijo));
      printf("%d\n", hijo);
      wait(NULL);
    }
  }
}