#include<sys/mman.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;

int main() {
    char ch;

    int32_t* A = (int32_t*) mmap(NULL, sizeof (int32_t) , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int32_t* wait = (int32_t*) mmap(NULL, sizeof (int32_t) , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *wait = 1;

    pid_t pid = fork();

    if(pid < 0) {
        cout << "Error during fork";
        return -1;
    }

    else if(pid == 0) {
        string filename;
        cout << "Enter filename: ";
        cin >> filename;

        ifstream file(filename);
        file.get(ch);

        *A = (int32_t)ch - 48;
        *wait = 0;
        cout << "Fork Filho: " << *A << endl;
    }

    else {
        while(*wait) {

        }

        cout << "Fork Pai: " << *A << endl;
    }

    return 0;
}