#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_LIMITS 100

struct product {
    char name[50];
    float price;
    int stock;
};

struct recipt_item{
    char name[50];
    float price;
    int quantity;
    float line_total;
};

int product_found(const char *serial, struct product *pt);

#endif