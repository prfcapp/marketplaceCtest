/*
specifically just the data types and what not. 

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

static int next_order_id = 1;

// Creates and initializes an order
struct order* create_order(const char* product_name, int price, int quantity, enum order_type type) {
    // Allocate memory for the new order
    struct order* o = malloc(sizeof(struct order));
    if (!o) {
        perror("Failed to allocate memory for order");
        return NULL;
    }

    // Set the order ID
    o->order_id = next_order_id++;

    // Allocate and copy the product name
    o->product = strdup(product_name);
    if (!o->product) {
        perror("Failed to allocate memory for product name");
        free(o);
        return NULL;
    }

    // Initialize other fields
    o->price = price;
    o->quantity = quantity;
    o->type = type;
    o->status = NEW; // New orders start with status NEW

    return o;
}

// Frees the memory associated with an order
void free_order(struct order* o) {
    if (!o) return;
    free(o->product); // Free the product name memory
    free(o);          // Free the order struct memory
}


// order matching function
void match_order(struct order* new_order, struct order* existing_orders, int num_orders) {
    for (int i = 0; i < num_orders; i++) {
        struct order* current = &existing_orders[i];
        
        // Check if the order matches (opposite type, same product, and compatible price)
        if (current->type != new_order->type &&
            strcmp(current->product, new_order->product) == 0 &&
            ((new_order->type == BUY && new_order->price >= current->price) ||
             (new_order->type == SELL && new_order->price <= current->price))) {
            
            // Process the match
            int matched_quantity = (new_order->quantity < current->quantity) ? new_order->quantity : current->quantity;
            printf("Matched %d units of %s between a %s and a %s order.\n",
                   matched_quantity, current->product,
                   (new_order->type == BUY ? "BUY" : "SELL"),
                   (current->type == BUY ? "BUY" : "SELL"));

            // Adjust quantities
            new_order->quantity -= matched_quantity;
            current->quantity -= matched_quantity;

            // Update statuses
            if (new_order->quantity == 0) new_order->status = FULFILLED;
            if (current->quantity == 0) current->status = FULFILLED;

            // Exit loop if the new order is fully fulfilled
            if (new_order->status == FULFILLED) break;
        }
    }
}



// print order
void print_all_orders(struct order_node* head){
    printf("\nAll orders:\n");
    struct order_node *current = head;
    while (current != NULL) {
        struct order *o = &current->data;
        print_order(o);
        current = current->next;
    }
}


void print_order(struct order* o){
    printf("Order ID: %d\n", o->order_id);
    printf("Order Type: %s\n", o->type);
    printf("Product: %s\n", o->product);
    printf("Quantity: %d\n", o->quantity);
    printf("Price: $%.2f\n", o->price / 100.0);
    printf("Order Status: %d\n\n", o->status);
    return;
}