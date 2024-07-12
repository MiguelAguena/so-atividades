/*
gcc -pthread ...
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <iostream>

int iteracoes = 1000;

void worker() {
    for (int i = 0; i < iteracoes; i++) {
        for (int j = 0; j < iteracoes; j++) {
            for (int k = 0; k < iteracoes; k++) {
                sqrt(i % 100);
            }
        }
    }
}

void run_multithreaded(int n_threads) {
    pthread_t threads[n_threads];
    for (int i = 0; i < n_threads; i++) {
        pthread_create(&threads[i], NULL, (void* (*)(void*))worker, NULL);
    }
    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

void run_sequential(int n_threads) {
    for (int i = 0; i < n_threads; i++) {
        worker();
    }
}

int main(int argc, char* argv[]) {
    int n_threads = atol(argv[1]);
    run_multithreaded(n_threads);
    // run_sequential(n_threads);
    return 0;
}