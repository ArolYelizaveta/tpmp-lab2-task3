/*
 * Author: Orel Elizaveta
 * Group: 13
 * File: main.c
 * Description: Main program demonstrating work with products.
 *              When run with "test" argument, test data is used.
 */

#include "../include/product.h"
#include <string.h>

static void fill_test_data(Product *products, int *count) {
    *count = 12;

    const char *names[] = {
        "Milk", "Bread", "Cheese", "Sausage", "Yogurt", "Juice",
        "Cookies", "Chocolate", "Butter", "Kefir", "Cottage cheese", "Waffles"
    };
    const char *manufacturers[] = {
        "Grandma's Jar", "Bakery No.1", "Cheese House", "Meat Yard",
        "Dairy World", "Fruit Garden", "Sweet Tooth", "Confectioner",
        "Butter Factory", "Dairy World", "Dairy World", "Sweet Tooth"
    };
    double prices[] = {1.5, 0.8, 3.2, 5.0, 0.9, 2.1, 1.2, 2.5, 2.8, 1.1, 1.9, 1.3};
    int quantities[] = {10, 20, 5, 7, 15, 12, 8, 6, 4, 9, 3, 11};

    Date prod_dates[] = {
        {2025, 1, 10}, {2025, 1, 12}, {2025, 1, 5}, {2025, 1, 8},
        {2025, 1, 15}, {2025, 1, 7}, {2025, 1, 20}, {2025, 1, 18},
        {2025, 1, 9}, {2025, 1, 14}, {2025, 1, 11}, {2025, 1, 13}
    };

    Date exp_dates[] = {
        {2025, 3, 10}, {2025, 2, 12}, {2025, 3, 5}, {2025, 2, 8},
        {2025, 3, 1}, {2025, 4, 7}, {2025, 5, 20}, {2025, 6, 18},
        {2025, 2, 9}, {2025, 3, 14}, {2025, 2, 11}, {2025, 3, 13}
    };

    for (int i = 0; i < *count; i++) {
        strcpy(products[i].name, names[i % 12]);
        products[i].price = prices[i % 12];
        products[i].production_date = prod_dates[i % 12];
        products[i].expiration_date = exp_dates[i % 12];
        products[i].quantity = quantities[i % 12];
        strcpy(products[i].manufacturer, manufacturers[i % 12]);
    }
}

int main(int argc, char *argv[]) {
    Product products[100]; 
    int count = 0; 

    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        printf("Test mode: using predefined data.\n");
        fill_test_data(products, &count);
    } else {
        input_products(products, &count);
    }

    Date current = get_current_date();

    printf("\n=== Initial product list ===\n");
    for (int i = 0; i < count; i++) {
        print_product(&products[i]);
    }
    sort_by_production_date(products, count);
    printf("\n=== After sorting by production date (ascending) ===\n");
    for (int i = 0; i < count; i++) {
        print_product(&products[i]);
    }
    print_expiring_soon(products, count, current);
    print_manufacturer_counts(products, count);
    print_max_price_not_expired(products, count, current);

    return 0;
}
