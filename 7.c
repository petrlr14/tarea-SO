#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3
pthread_mutex_t mutex [100] = PTHREAD_MUTEX_INITIALIZER;
int cantidad;
int Arreglo[100];
int numero;

pthread_t threads[NUM_THREADS]; 
int error;
int error1; 
int error2;

void *funcionThreadOrdenarDerecha (void *args);
void *funcionThreadOrdenarIzquierda (void *args);
void *funcionThreadPedir(void *args);

void swap(int *xp, int *yp){ 
    
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void bubbleSortIzquierda(){ 
   int i, j; 
    for (i = 0; i < cantidad-1; i++) {
        for (j = 0; j < cantidad-i-1; j++) {
            pthread_mutex_lock(&mutex[j]);
            pthread_mutex_lock(&mutex[j+1]);
            if (Arreglo[j] > Arreglo[j+1]){
                swap(&Arreglo[j], &Arreglo[j+1]); 
            }
            pthread_mutex_unlock(&mutex[j]);
            pthread_mutex_unlock(&mutex[j+1]);
            
       }
   }
} 

void bubbleSortDerecha(){ 
   int i, j; 
   for (i = 0; i < cantidad; i++){
        for (j = cantidad-1-i; j >0; j--){
            pthread_mutex_lock(&mutex[j]);
            pthread_mutex_lock(&mutex[j-1]);
            if (Arreglo[j] < Arreglo[j-1]){
                swap(&Arreglo[j-1], &Arreglo[j]);
            }
            pthread_mutex_unlock(&mutex[j]);
            pthread_mutex_unlock(&mutex[j-1]);
                
        }
    }
}

int main() {
	error = pthread_create (&threads[0], NULL, funcionThreadPedir, NULL);
    if (error != 0)
	{
		perror ("No puedo crear thread principal");
		exit (-1);
	}
    pthread_join(threads[0], NULL);
    for(int i =0; i<cantidad; i++){
        printf("%d ", Arreglo[i] );
    }
    printf("\n");
    pthread_exit(NULL);
}

void *funcionThreadOrdenarDerecha (void *args){
    
    bubbleSortDerecha();
    pthread_exit(NULL);

}

void *funcionThreadOrdenarIzquierda (void *args){
     
    bubbleSortIzquierda();
    pthread_exit(NULL);
}

//FUNCION PEDIR
void *funcionThreadPedir(void *args){
    printf("Introduzca la cantidad de numeros a ingresar(no mayor a 100): ");
    do{
        scanf("%d", &cantidad);
        if(cantidad>100){
            printf("Numero ingresado es mayor a 100, ingreselo de nuevo\n");
        }
    }while(cantidad>100);
    

    for(int i= 0;i<cantidad;i++){

        printf("ingrese numero en posicion %i: ", i);
        scanf("%d", &numero);       

        Arreglo[i]=numero;
    }

    /* Creamos los thread */
	error1 = pthread_create (&threads[1], NULL, funcionThreadOrdenarDerecha, NULL);
    if (error1 != 0)
	{
		perror ("No puedo crear thread 1");
		exit (-1);
	}
    error2 = pthread_create (&threads[2], NULL, funcionThreadOrdenarIzquierda, NULL);
    if (error2 != 0)
	{
		perror ("No puedo crear thread 2");
		exit (-1);
	}
    for(int i =1; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_exit(NULL);
}