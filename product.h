/*
 * Author: Orel Elizaveta
 * Group: 13
 * File: product.h
 * Description: Заголовочный файл с определением структур и прототипов функций
 *              для работы с товарами (вариант 16).
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Структура для представления даты (год, месяц, день).
 */
typedef struct {
    int year;
    int month;
    int day;
} Date;

/*
 * Структура товара.
 * Поля: наименование, цена, дата производства, срок годности,
 *       количество, производитель.
 */
typedef struct {
    char name[100];
    double price;
    Date production_date;
    Date expiration_date;
    int quantity;
    char manufacturer[100];
} Product;


int date_compare(Date d1, Date d2);

Date get_current_date(void);

void input_products(Product *products, int *count);

void print_product(const Product *p);

void sort_by_production_date(Product *products, int count);

void print_expiring_soon(const Product *products, int count, Date current_date);

void print_manufacturer_counts(const Product *products, int count);

void print_max_price_not_expired(const Product *products, int count, Date current_date);

#endif
