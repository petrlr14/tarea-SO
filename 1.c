#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


long int strtol(const char *nptr, char **endptr, int base);
void createSon();
int size(char *ptr);

/* Escribir N como parametro en la linea de comando */

int main(int argc, char*argv[]){
  if(argc!=2){
    fprintf(stderr, "Debe haber exactamente un argumento, el valor de N\n");
    exit(1);
  }
  char *ptr;
  int arg= strtol(argv[1], &ptr, 10);
  if(!arg){
    if(!size(ptr)){
      fprintf(stderr, "N debe ser mayor de 0\n");
    }else{
      fprintf(stderr, "La entrada debe ser un entero\n");  
    }
    exit(1);
  }
  printf("PID: %d\n", getpid());
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
    printf("PID: %d\n", getppid());
    for(int i=arg; i>=count; i--){
      printf("\t");
    }
    printf("PID: %d\n", getpid());
  }else{
    wait(NULL);
  }
  createSon(--count, arg);
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