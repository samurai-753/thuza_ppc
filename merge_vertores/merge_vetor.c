#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 14

int A[] = {2, 4, 5, 7, 10, 12, 17, 1, 3, 6, 8, 9, 20, 21};
int vetor[N];

void* merge(void* t) {
    int thread = *((int*) t);
    
    int low = 0;
    int high = N/2 - 1;
    
    if(thread < N/2) {
        low = N/2;
        high = N - 1;
    }
    
    int x = A[thread];
    
    do {
        int index = (low + high) / 2;
        
        if(x < A[index]) {
            high = index - 1;
        } else {
            low = index + 1;
        }

    } while(low <= high);
    
    int pos = high + thread + 1 - (N/2);
    vetor[pos] = x;

}



int main (int argc, char *argv[])
{
    pthread_t threads[N];
    int rc;
    for(int i = 0; i < N; i++){
        rc = pthread_create(&threads[i], NULL, merge, (void*) &i);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        pthread_join(threads[i], NULL);
    }
    
    for(int i = 0; i < N; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    pthread_exit(NULL);
    return 0;
}