#include <locale.h>
#include <stdio.h>
#include <string.h>
#include "threads.h"
#include "file_operations.h"

int main() {
    setlocale(LC_ALL, ""); // Use the default locale

    // Initialize threads and semaphores
    initialize_threads_and_semaphores();

    // Start the main thread
    start_main_thread();

    char command[10];
    while (1) {
        printf("Enter a command (read, write, update, close): ");
        scanf("%s", command);

        if (strcmp(command, "close") == 0) {
            simulate_client_request("close"); // Close komutu gönderilir
            break;
        }

        simulate_client_request(command);
    }

    // Clean up resources
    clean_up_resources();

    return 0;
}
