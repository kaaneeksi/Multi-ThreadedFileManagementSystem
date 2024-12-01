#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include "threads.h"
#include "file_operations.h"

// Semaphores
sem_t serv_sem, cli_sem;

// Main thread
pthread_t main_thread;

// Command structure
struct Command {
    int client_id;
    char action[10];
} command;

void initialize_threads_and_semaphores() {
    sem_init(&serv_sem, 0, 0);
    sem_init(&cli_sem, 0, 0);
}

void start_main_thread() {
    pthread_create(&main_thread, NULL, main_thread_function, NULL);
}

void *main_thread_function(void *arg) {
    while (1) {
        sem_wait(&serv_sem); // Wait for a command
        printf("Main Thread: Command received. Action: %s\n", command.action);

        if (strcmp(command.action, "open") == 0) {
            open_file();
        } else if (strcmp(command.action, "update") == 0) {
            update_inventory(); // Envanteri günceller
        } else if (strcmp(command.action, "read") == 0) {
            read_file();
        } else if (strcmp(command.action, "write") == 0) {
            write_file();
        } else if (strcmp(command.action, "close") == 0) {
            printf("Closing the system...\n");
			sem_post(&cli_sem);
            break; // Ana döngüyü sonlandırır
        }

        sem_post(&cli_sem); // Notify the client
    }
    return NULL;
}


void simulate_client_request(const char *action) {
    // Simulate a client sending a command
    command.client_id = 1;
    strcpy(command.action, action);
    sem_post(&serv_sem); // Notify the server
    sem_wait(&cli_sem); // Wait for the operation to complete
    printf("Client: Operation completed.\n");
}

void clean_up_resources() {
    pthread_cancel(main_thread);
    sem_destroy(&serv_sem);
    sem_destroy(&cli_sem);
}
