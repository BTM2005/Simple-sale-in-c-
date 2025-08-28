#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "inventory.h"



int product_found(const char *serial, struct product *pt){
    FILE *ptr;
    ptr = fopen("inventory.txt", "r");

    if (ptr == NULL){
        printf("Error! File could not be opened.\n");
        exit(1);
    }

    char file_name[50];
    char file_serial[50];
    float file_price;
    int file_stock;

    while(fscanf(ptr, "%49s %49s %f %d", file_serial, file_name, &file_price, &file_stock) == 4){
        if(strcmp(file_serial, serial) == 0){
            strcpy(pt->name, file_name);
            pt->price = file_price;
            pt->stock = file_stock;
            fclose(ptr);
            return 1;
        }

    }
    fclose(ptr);
    return 0;
}