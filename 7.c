#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int cantidad;
int Arreglo[100];
int numero;

void *funcionThreadOrdenarDerecha (void *args);
void *funcionThreadOrdenarIzquierda (void *args);

void swap(int *xp, int *yp){ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void bubbleSortIzquierda(){ 
   int i, j; 
    for (i = 0; i < cantidad-1; i++) {
        for (j = 0; j < cantidad-i-1; j++) {
            pthread_mutex_lock(&mutex);
            printf("esta hilo 2\n");
            if (Arreglo[j] > Arreglo[j+1]){
                swap(&Arreglo[j], &Arreglo[j+1]); 
            }
            pthread_mutex_unlock(&mutex);
       }

   }      

} 

void bubbleSortDerecha(){ 
   int i, j; 
   for (i = cantidad-1; i >=0; i--){
        for (j = cantidad-1-i; j >0; j--){
            pthread_mutex_lock(&mutex); 
            printf("esta hilo 1\n");
            if (Arreglo[j] < Arreglo[j-1]){
                swap(&Arreglo[j-1], &Arreglo[j]);
            }
            pthread_mutex_unlock(&mutex);     
        }
    }
}

int main() {
    pthread_t threads[NUM_THREADS]; 
    int error1; 
    int error2;

    printf("Introduzca la cantidad de numeros a ingresar(no mayor a 100): ");
    scanf("%d", &cantidad);

    for(int i= 0;i<cantidad;i++){
        printf("ingrese numero: ");
        scanf("%d", &numero);
        Arreglo[i]=numero;
    }

    /* Creamos los thread */
	error1 = pthread_create (&threads[0], NULL, funcionThreadOrdenarDerecha, NULL);
    if (error1 != 0)
	{
		perror ("No puedo crear thread 1");
		exit (-1);
	}
    error2 = pthread_create (&threads[1], NULL, funcionThreadOrdenarIzquierda, NULL);
    if (error2 != 0)
	{
		perror ("No puedo crear thread 2");
		exit (-1);
	}
    for(int i =0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_exit(NULL);
}

void *funcionThreadOrdenarDerecha (void *args){

    
    printf("estoy en el hilo 1\n");
    
    bubbleSortDerecha();
    for(int i =0; i<cantidad; i++){
        printf("la posicion %d en el hilo 1 es: %d\n", i+1, Arreglo[i] );
    }
    pthread_exit(NULL);

}

void *funcionThreadOrdenarIzquierda (void *args){
  
    printf("estoy en el hilo 2\n");
    
    bubbleSortIzquierda();
    for(int i =0; i<cantidad; i++){
        printf("la posicion %d en el hilo 2 es: %d\n", i+1, Arreglo[i] );
    }
    pthread_exit(NULL);
}
