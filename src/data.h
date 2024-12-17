#ifndef DATA_H
#define DATA_H

#include <stddef.h> // For size_t
#include <time.h> //for timestamps

// enum to represent where an order stands
enum order_status {NEW, PENDING, FULFILLED};

// enum for order type
enum order_type { BUY, SELL };

// Struct to represent an order
struct order {
    char* product;    // Pointer to the product name
    int price;        // Price of the product in cents (to avoid floating-point precision issues)
    int quantity;     // Quantity of the product ordered
    int order_id;
    char* customer_name;
    time_t order_time;
    enum order_status status;
    enum order_type type;
    struct order *next;
};

struct order_node {
    struct order data;
};



// Function prototypes for working with orders
struct order* create_order(const char* product_name, int price, int quantity, enum order_type type);
void add_order(struct order** head, struct order* o);
void free_order(struct order* o);
void match_order(struct order* o, struct order* existing_orders, int num_orders);
void print_all_orders(struct order** head);
void print_order(struct order* o);
const char *order_type_to_string(enum order_type type);

#endif // DATA_H
