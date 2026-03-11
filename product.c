/*
 * Author: Orel Elizaveta
 * Group: 13
 * File: product.c
 * Description: Implementation of functions for working with the Product structure.
 */

#include "../include/product.h"
#include <ctype.h> 

static int input_int(const char *prompt, int min, int max) {
    int value;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max) {
                return value;
            }
        }
        printf("Input error. Please try again.\n");
    }
}

static double input_double(const char *prompt, double min) {
    double value;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%lf", &value) == 1 && value >= min) {
                return value;
            }
        }
        printf("Input error. Please try again.\n");
    }
}

static void input_string(const char *prompt, char *dest, size_t size) {
    printf("%s", prompt);
    if (fgets(dest, size, stdin) != NULL) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len-1] == '\n') {
            dest[len-1] = '\0';
        }
    }
}

int date_compare(Date d1, Date d2) {
    if (d1.year != d2.year) return (d1.year < d2.year) ? -1 : 1;
    if (d1.month != d2.month) return (d1.month < d2.month) ? -1 : 1;
    if (d1.day != d2.day) return (d1.day < d2.day) ? -1 : 1;
    return 0;
}

Date get_current_date(void) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date d;
    d.year = tm.tm_year + 1900;
    d.month = tm.tm_mon + 1;
    d.day = tm.tm_mday;
    return d;
}

void input_products(Product *products, int *count) {
    int n;
    do {
        n = input_int("Enter the number of products (at least 12): ", 12, 100);
    } while (n < 12);
    *count = n;

    for (int i = 0; i < n; i++) {
        printf("\n--- Entering product #%d ---\n", i + 1);
        input_string("Name: ", products[i].name, sizeof(products[i].name));
        products[i].price = input_double("Price: ", 0.0);

        printf("Production date (year month day):\n");
        products[i].production_date.year = input_int("  year: ", 1900, 2100);
        products[i].production_date.month = input_int("  month: ", 1, 12);
        products[i].production_date.day = input_int("  day: ", 1, 31);

        printf("Expiration date (year month day):\n");
        products[i].expiration_date.year = input_int("  year: ", 1900, 2100);
        products[i].expiration_date.month = input_int("  month: ", 1, 12);
        products[i].expiration_date.day = input_int("  day: ", 1, 31);

        products[i].quantity = input_int("Quantity: ", 0, 1000000);
        input_string("Manufacturer: ", products[i].manufacturer, sizeof(products[i].manufacturer));
    }
}

void print_product(const Product *p) {
    printf("Name: %s\n", p->name);
    printf("Price: %.2f\n", p->price);
    printf("Production date: %04d-%02d-%02d\n",
           p->production_date.year,
           p->production_date.month,
           p->production_date.day);
    printf("Expiration date: %04d-%02d-%02d\n",
           p->expiration_date.year,
           p->expiration_date.month,
           p->expiration_date.day);
    printf("Quantity: %d\n", p->quantity);
    printf("Manufacturer: %s\n", p->manufacturer);
    printf("----------------------\n");
}

void sort_by_production_date(Product *products, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (date_compare(products[j].production_date,
                             products[j+1].production_date) > 0) {
                Product temp = products[j];
                products[j] = products[j+1];
                products[j+1] = temp;
            }
        }
    }
}

void print_expiring_soon(const Product *products, int count, Date current_date) {
    printf("\n=== Products expiring soon (within 2 days) ===\n");
    int found = 0;

    for (int i = 0; i < count; i++) {
        struct tm tm_exp = {0}, tm_cur = {0};
        tm_exp.tm_year = products[i].expiration_date.year - 1900;
        tm_exp.tm_mon  = products[i].expiration_date.month - 1;
        tm_exp.tm_mday = products[i].expiration_date.day;

        tm_cur.tm_year = current_date.year - 1900;
        tm_cur.tm_mon  = current_date.month - 1;
        tm_cur.tm_mday = current_date.day;

        time_t t_exp = mktime(&tm_exp);
        time_t t_cur = mktime(&tm_cur);
        if (t_exp == -1 || t_cur == -1) continue;

        double diff_days = difftime(t_exp, t_cur) / (60 * 60 * 24);
        if (diff_days >= 0 && diff_days <= 2) {
            print_product(&products[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No such products.\n");
    }
}

void print_manufacturer_counts(const Product *products, int count) {
    printf("\n=== Product quantities by manufacturer ===\n");
    
    char manufacturers[100][100];
    int quantities[100] = {0};
    int unique = 0;

    for (int i = 0; i < count; i++) {
        int found = -1;
        for (int j = 0; j < unique; j++) {
            if (strcmp(products[i].manufacturer, manufacturers[j]) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            strcpy(manufacturers[unique], products[i].manufacturer);
            quantities[unique] = products[i].quantity;
            unique++;
        } else {
            quantities[found] += products[i].quantity;
        }
    }

    for (int j = 0; j < unique; j++) {
        printf("%s: %d pcs.\n", manufacturers[j], quantities[j]);
    }
}

void print_max_price_not_expired(const Product *products, int count, Date current_date) {
    printf("\n=== Product with maximum price (not expired) ===\n");
    int max_idx = -1;
    double max_price = -1.0;

    for (int i = 0; i < count; i++) {
        struct tm tm_exp = {0}, tm_cur = {0};
        tm_exp.tm_year = products[i].expiration_date.year - 1900;
        tm_exp.tm_mon  = products[i].expiration_date.month - 1;
        tm_exp.tm_mday = products[i].expiration_date.day;

        tm_cur.tm_year = current_date.year - 1900;
        tm_cur.tm_mon  = current_date.month - 1;
        tm_cur.tm_mday = current_date.day;

        time_t t_exp = mktime(&tm_exp);
        time_t t_cur = mktime(&tm_cur);
        if (t_exp == -1 || t_cur == -1) continue;

        if (t_exp >= t_cur) { 
            if (max_idx == -1 || products[i].price > max_price) {
                max_price = products[i].price;
                max_idx = i;
            }
        }
    }

    if (max_idx != -1) {
        print_product(&products[max_idx]);
    } else {
        printf("No products with unexpired shelf life.\n");
    }
}
