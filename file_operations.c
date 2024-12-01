#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"

void open_file()
{
    FILE *file = fopen("inventory.txt", "r"); // Open the file in read mode

    if (file == NULL) {
        printf("Failed to open the file: inventory.txt\n");
        return;
    }

    printf("File successfully opened. Content:\n");

    char line[256]; // Buffer to hold each line
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file); // Close the file
}

void read_file()
{
    FILE *file = fopen("inventory.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file: inventory.txt\n");
        return;
    }

    printf("Reading file content:\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void write_file() {
    char product_name[50];
    int price, quantity;

    printf("Enter the product name: ");
    scanf("%49s", product_name);
    printf("Enter the price: ");
    scanf("%d", &price);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    FILE *file = fopen("inventory.txt", "a");

    if (file == NULL) {
        printf("Error: Could not open inventory file.\n");
        return;
    }

    // Ürün formatını hizalamak için %-15s gibi sabit genişlikler kullanıyoruz
    fprintf(file, "%-15s %-10d %-10d\n", product_name, price, quantity);
    fclose(file);

    printf("New inventory item added: %s %d %d\n", product_name, price, quantity);
}

void update_inventory() {
    printf("Update Options:\n");
    printf("1. Add a new product\n");
    printf("2. Update an existing product\n");
    printf("3. Remove a product\n");

    int choice;
    printf("Enter your choice (1-3): ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Invalid input. Exiting update process.\n");
        return;
    }

    char product_name[50] = {0};
    int price = 0, quantity = 0;

    switch (choice) {
        case 1: // Add a new product
            printf("Enter the product name to add: ");
            scanf("%49s", product_name);
            printf("Enter the price: ");
            scanf("%d", &price);
            printf("Enter the quantity: ");
            scanf("%d", &quantity);
            
            char add_command[1024];
            snprintf(add_command, sizeof(add_command),
                     "awk -v choice=1 -v prod=\"%s\" -v price=%d -v quantity=%d -f update.awk inventory.txt > temp.txt && mv temp.txt inventory.txt",
                     product_name, price, quantity);

            if (system(add_command) != 0) {
                printf("Error: Could not add the product.\n");
            } else {
                printf("Product '%s' added successfully.\n", product_name);
            }
            break;

        case 2: // Update an existing product
            printf("Enter the product name to update: ");
            scanf("%49s", product_name);
            printf("Enter the new price: ");
            scanf("%d", &price);
            printf("Enter the new quantity: ");
            scanf("%d", &quantity);

            char update_command[1024];
            snprintf(update_command, sizeof(update_command),
                     "awk -v choice=2 -v prod=\"%s\" -v price=%d -v quantity=%d -f update.awk inventory.txt > temp.txt && mv temp.txt inventory.txt",
                     product_name, price, quantity);

            if (system(update_command) != 0) {
                printf("Error: Could not update the product.\n");
            } else {
                printf("Product '%s' updated successfully.\n", product_name);
            }
            break;

        case 3: // Remove a product
            printf("Enter the product name to remove: ");
            scanf("%49s", product_name);

            char remove_command[1024];
            snprintf(remove_command, sizeof(remove_command),
                     "awk -v choice=3 -v prod=\"%s\" -f update.awk inventory.txt > temp.txt && mv temp.txt inventory.txt",
                     product_name);

            if (system(remove_command) != 0) {
                printf("Error: Could not remove the product.\n");
            } else {
                printf("Product '%s' removed successfully.\n", product_name);
            }
            break;

        default:
            printf("Invalid choice. Exiting update process.\n");
            break;
    }
}

