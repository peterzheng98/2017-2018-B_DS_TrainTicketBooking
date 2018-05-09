#include <unistd.h>
#include <pthread.h>
#include "Timer.h"
typedef unsigned long long ull;
typedef long long ll;
typedef unsigned short us;

pthread_t timer, logger;
Timer globalTime;

void *TimerThread(void *arg) {
    pthread_detach(pthread_self());
    while (1) {
        globalTime++;
        sleep(1);
    }
}

int main() {
    int err = pthread_create(&timer, nullptr, TimerThread, nullptr);
    if(err != 0) // TODO : Thread Create Failed.

}

