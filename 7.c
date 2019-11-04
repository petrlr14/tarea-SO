#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *funcionThread (void *parametro);
void *funcionThreadOrdenarIzquierda (void *parametro);

void swap(int *xp, int *yp){ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void bubbleSortIzquierda(int arr[], int n){ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

void bubbleSortDerecha(int arr[], int n){ 
   int i, j; 
   for (i = n-1; i >=0; i--)       
       for (j = n-1-i; j >0; j--)  
           if (arr[j] < arr[j-1]) 
              swap(&arr[j-1], &arr[j]); 
} 

int main() {

	pthread_t idHilo;
	int error;

	error = pthread_create (&idHilo, NULL, funcionThread, NULL);

	if (error != 0){
		perror ("No puedo crear thread");
		exit (-1);
	}


  
    /*bubbleSortIzquierda(Arreglo, cantidad);

    for(int i =0; i<cantidad; i++){
        printf("la posicion %d es: %d\n", i+1, Arreglo[i] );
    }
  */
    return 0;
}

void *funcionThread (void *parametro){
    int cantidad;
    printf("Introduzca la cantidad de numeros a ingresar: ");
    scanf("%d", &cantidad);
    int Arreglo[cantidad];
    int numero;
    for(int i= 0;i<cantidad;i++){
        printf("ingrese numero: ");
        scanf("%d", &numero);
        Arreglo[i]=numero;
    }

    pthread_t idHiloOrdenarIzquierda;
    	int errorIzquierda;

	errorIzquierda = pthread_create (&idHiloOrdenarIzquierda, NULL, funcionThreadOrdenarIzquierda , NULL);

	if (errorIzquierda != 0){
		perror ("No puedo crear thread izquierdo");
		exit (-1);
	}
}

void *funcionThreadOrdenarIzquierda (void *parametro){
bubbleSortIzquierda(Arreglo, cantidad);

    for(int i =0; i<cantidad; i++){
        printf("la posicion %d es: %d\n", i+1, Arreglo[i] );
    }
}