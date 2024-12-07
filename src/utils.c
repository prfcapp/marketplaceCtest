/// @brief helpers etc

#include <stdio.h>

void print_help() {
    printf("\n=== Help ===\n");
    printf("This is a simple marketplace program that allows you to create buy and sell orders.\n");
    printf("Orders should be entered in the following format:\n");
    printf("  type,product,quantity,price\n");
    printf("Where:\n");
    printf("  - type: BUY or SELL\n");
    printf("  - product: Name of the product\n");
    printf("  - quantity: Quantity of the product\n");
    printf("  - price: Price in cents (e.g., 10000 for $100.00)\n\n");
    printf("Commands:\n");
    printf("  - Enter orders in the format above to add them to the marketplace.\n");
    printf("  - Type 'exit' to quit the program.\n");
    printf("  - Type 'help' to see this message again.\n\n");
}

