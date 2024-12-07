/*
quick mock up of a marketplace like application to practice my C programming. shouldnt take too long....
famous last words.


*/
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "utils.h"
#include "marketplace.h"





int parse_order_input(const char* input, struct order** new_order) {
    // test this shit work
    printf("test purpose: printing parse order: %s\n", input);

    char type_str[10], product[100];
    int quantity, price;
    enum order_type type;

    // Scan input in the required format
    int scanned = sscanf(input, "%10[^,],%99[^,],%d,%d", type_str, product, &quantity, &price);
    if (scanned != 4) {
        printf("Failed to scan in order sadly bro.\n");
        return 0; // Invalid format
    }

    // Convert order type string to enum value
    if (strcmp(type_str, "BUY") == 0) {
        type = BUY;
    } else if (strcmp(type_str, "SELL") == 0) {
        type = SELL;
    } else {
        return 0; // Invalid order type
    }

    // Create the order using the parsed values
    *new_order = create_order(product, price, quantity, type);
    return *new_order != NULL;
}


int main() {
    // Pre-populate some orders
    struct order_node* orders[100]; // Array to hold the orders
    
    // Pre-populate example orders
    struct order_node temp = create_order("Laptop", 99999, 1, BUY);  // $999.99 for 1 Laptop
    create_order("Smartphone", 50000, 2, SELL); // $500.00 for 2 Smartphones

    // Display the pre-populated orders
    printf("Pre-populated orders:\n");
    print_all_orders(*orders);

    // Take user input for new orders
    char input[256]; // Buffer for user input
    struct order_node* new_order = NULL;

    printf("\nEnter new orders in the format: type,product,quantity,price\n");
    while (1) {
       printf("Enter order (or 'exit' to quit, 'help' for instructions): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Handle EOF or input error
        }

        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break; // Exit the loop if user types "exit"
        } else if (strcmp(input, "help") == 0) {
            print_help(); // Show help message
        } else if (strcmp(input, "show") == 0) {
            print_all_orders(*orders); // Show help message
        }else if (parse_order_input(input, &(new_order->data))) {
            orders[order_count++] = new_order;
            struct order* temp = &(new_order->data); 
            printf("Order added: Order ID: %d, Type: %s, Product: %s, Price: $%d.%02d, Quantity: %d\n",
                    temp->order_id,
                    temp->type == BUY ? "BUY" : "SELL",
                    temp->product,
                    temp->price / 100, temp->price % 100,
                    temp->quantity);
        } else {
            printf("Invalid input format. Please try again.\n");
        }
    }

    // Display all orders


    // Free the memory for orders
    for (int i = 0; i < order_count; i++) {
        free_order(orders[i]);
    }

    return 0;
}


