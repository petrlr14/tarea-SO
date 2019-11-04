#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int size(char *ptr);

/* Signal */
void signalHandler(int signal);
int step=1, countNumber = 0;
/* ********************************* */


int main(int argc, char*argv[]){
  if(argc!=2){
    fprintf(stderr, "Debe haber exactamente un argumento, el valor de N\n");
    exit(1);
  }
  char *ptr;
  int N= strtol(argv[1], &ptr, 10);
  if(!N){
    if(!size(ptr)){
      fprintf(stderr, "N debe ser mayor de 0\n");
    }else{
      fprintf(stderr, "La entrada debe ser un entero\n");  
    }
    exit(1);
  }
  int count=0, father=getpid(), canFork[N], process[N];
  for(int i=0; i<N; i++){
    canFork[i]=1;
  }
  signal(SIGTSTP, signalHandler);
  signal(SIGPWR, signalHandler);
  for(int i=0; i<N; i++){
      if(getpid()==father){
        if(canFork[i]){
          canFork[i]=0;
          int child=fork();
          if(child>0){
            process[i]=child;
          }else{
            countNumber=i+1;
          }
        }
      }
  }
  
  while(1){
   if(father==getpid()){   
      for(long i=0; i<100000000; i++){}
      kill(process[count], SIGPWR);
      count+=step;
      if(count==N){
        count=0;
      }
      if(count<0){
        count=N-1;
      }
    }else{
      pause();
      printf("proceso hijo #%d: %d\n", countNumber ,getpid());
    } 
  }
}

void signalHandler(int signal){
  switch (signal){
  case SIGTSTP:
    step*=-1;
    for(int i=0; i<10000000; i++){}
    break;
  case SIGPWR:
  default:
    break;
  }
}

int size(char *ptr){
  int offset = 0;
  int count = 0;
  while (*(ptr + offset) != '\0'){
    ++count;
    ++offset;
  }
  return count;
}