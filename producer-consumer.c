#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

char* buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t not_empty;
pthread_cond_t not_full;

void *producer(void *param);
void *consumer(void *param);

int insert_data(char* data) {
    if (count < BUFFER_SIZE) {
        buffer[count++] = data;
        return 0;
    } else {
        return -1;
    }
}

int remove_data(char** data) {
    if (count > 0) {
        *data = buffer[--count];
        return 0;
    } else {
        return -1;
    }
}

void *producer(void *param) {
    int iter = 0;
    while(iter < 5) {
        char* data = "Hello world!";
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);

        if (insert_data(data))
            fprintf(stderr, "Producer error\n");
        else
            printf("Produced: %s\n", data);

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);

        iter++;
    }
    return NULL;
}

void *consumer(void *param) {
    int iter = 0;
    while(iter < 5) {
        char* data;
        pthread_mutex_lock(&mutex);

        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        if (remove_data(&data))
            fprintf(stderr, "Consumer error\n");
        else
            printf("Consumed: %s\n", data);

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

        iter++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int num_producers = 5;
    int num_consumers = 5;

    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);

    for (int i = 0; i < num_producers; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }
    for (int i = 0; i < num_consumers; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}