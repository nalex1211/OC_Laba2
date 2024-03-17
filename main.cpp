#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PHILOSOPHERS_COUNT 5

pthread_mutex_t forks[PHILOSOPHERS_COUNT];

void* philosopher(void* num) {
    int id = *(int*)num;

    int leftFork = id;
    int rightFork = (id + 1) % PHILOSOPHERS_COUNT;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 2);

        if (leftFork < rightFork) {
            pthread_mutex_lock(&forks[leftFork]);
            printf("Philosopher %d picked up fork %d.\n", id, leftFork);
            pthread_mutex_lock(&forks[rightFork]);
            printf("Philosopher %d picked up fork %d.\n", id, rightFork);
        } else {
            pthread_mutex_lock(&forks[rightFork]);
            printf("Philosopher %d picked up fork %d.\n", id, rightFork);
            pthread_mutex_lock(&forks[leftFork]);
            printf("Philosopher %d picked up fork %d.\n", id, leftFork);
        }

        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 3);

        pthread_mutex_unlock(&forks[leftFork]);
        printf("Philosopher %d put down fork %d.\n", id, leftFork);
        pthread_mutex_unlock(&forks[rightFork]);
        printf("Philosopher %d put down fork %d.\n", id, rightFork);
    }
}

int main() {
    pthread_t philosophers[PHILOSOPHERS_COUNT];
    int ids[PHILOSOPHERS_COUNT];

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < PHILOSOPHERS_COUNT; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
