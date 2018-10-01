#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct Argumentos{
    int a;
    int b;
    int* c;
};

void* sum(void* args) {
    struct Argumentos* ptr_args = (struct Argumentos*) args;
    int a = ptr_args->a;
    int b = ptr_args->b;
    int* c = ptr_args->c;
    *c = a + b;
}


int main (int argc, char *argv[])
{
    int tamanho;
    scanf("%d", &tamanho);
    
    int A[tamanho];
    for(int i = 0; i < tamanho; i++){
        scanf("%d", &A[i]);
    }
    int B[tamanho];
    for(int i = 0; i < tamanho; i++){
        scanf("%d", &B[i]);
    }
    
    int C[tamanho];
    pthread_t threads[tamanho];
    int rc;
    struct Argumentos args;
    for(int i = 0; i < tamanho; i++){
        args.a = A[i];
        args.b = B[i];
        args.c = &C[i];
        rc = pthread_create(&threads[i], NULL, sum, (void*) &args);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        pthread_join(threads[i], NULL);
    }
    

    for(int i = 0; i < tamanho; i++) {
        printf("%d i: %d\n", i, C[i]);
    }
    

    pthread_exit(NULL);
    return 0;
}