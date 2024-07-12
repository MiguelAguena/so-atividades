#include<sys/mman.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<pthread.h>
using namespace std;

int32_t A;
int32_t wait = -1;

void* workerA(void* filename) {
    while(wait) {

    }

    cout << "Thread A: " << A << endl;
}

void* workerB(void* filename) {
    char ch;
    ifstream file((char *) filename);
    file.get(ch);

    A = (int32_t)ch - 48;
    cout << "Thread B: " << A << endl;
    wait = 0;
}

int main(int argc, char* argv[]) {
    char ch;
    const char* filename = argv[1];

    pthread_t threadA;
    pthread_t threadB;

    pthread_create(&threadA, NULL, workerA, (void *) 0);
    pthread_create(&threadB, NULL, workerB, (void *) filename);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    return 0;
}
