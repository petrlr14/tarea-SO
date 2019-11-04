#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"
#include "sys/types.h"

//Creamos variable necesaria para crear procesos
pid_t pid;

//Funcion que calcula el factorial
int factorial(int n){
    if(n > 1){
        pid =fork();
        if(pid <0){
            printf("Error al crear un proceso hijo\n");
//Se regresa -1 cuando el proceso hijo no se puedo crear
            exit(-1);
        }
        else if(pid>0){
        int aux;
        waitpid(pid,&aux, 0);
//Se verifica si el proceso hijo fue terminado con exito
            if(WIFEXITED(aux)){
                aux = WEXITSTATUS(aux);
                if(aux != -1){
//Se calcula el factorial si el proceso hijo se creo con exito y el estado de regreso no fue -1
                    return aux*factorial(n-1);
                }
                else{
                    printf("Error al crear un proceso hijo\n");
                    exit(0);
                }
            }
            else{
                printf("Error en el proceso hijo\n");
            }
        }else if(pid == 0){
            exit(n);
        }
    }
    return 1;
}

int main(int argc, char *argv[]){
	printf("********************** Ejercicio 2 **********************\n");
    if(argc ==2){
//Se convierte el valor ingresado a entero
        int n = atoi(argv[1]);
        if(n>=0){
            printf("El valor ingresado es: %d \nEl resultado del factorial es: %d\n", n, factorial(n));
        }
        else{
            printf("Argumento ingresado invalido, el numero debe de ser mayor a 0\n");
        }
    }else if (argc < 2)
    {
        printf("Falta argumento(s)");
    }
    printf("********************** Fin **********************\n");
    return 0;
}
