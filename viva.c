// to scan a item from the inventory and sell the product

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct product{
    char name[50];
    float price;
    int stock;
};
struct recipt_items{
    char name[50];
    float price;
    int quantity;
    float line_total;
};

#define MAX_limits 100
int product_found(const char *serial, struct product *pt);


int main(){
float total = 0.0;
float  discount = 0.0;
char serial[50];
char more = 'y';
float cash = 0.0, change = 0.0;

struct recipt_items rti[MAX_limits];
int sales_count = 0;

do {
    printf("Enter the serial number: ");
    scanf("%49s", serial);

    struct product pt;

    if (product_found(serial, &pt)) {
    int quantity = 1;
    printf("Product found: %s - Rp.%.2f\n", pt.name, pt.price);
    printf("In stock: %d\n", pt.stock);
    printf("ADD quantity: ");
    scanf("%d", &quantity);
    
    if (quantity > pt.stock) {
        printf("Insufficient stock! Only %d items available.\n", pt.stock);
        continue;
    }
    
    float line_total = pt.price *  quantity;
    total += line_total;
    
    
    if (sales_count < MAX_limits){
        strcpy(rti[sales_count].name, pt.name);
        rti[sales_count].price = pt.price;
        rti[sales_count].quantity = quantity;
        rti[sales_count].line_total = line_total;
        sales_count++;
    }

    printf("%d x %s added. Line_total: Rp.%.2f\n\n", quantity, pt.name, line_total);
    }
    else {
        printf("Product with serial '%s' not found in the inventory.\n", serial);
    }
    
    while(getchar() != '\n');

    printf("Do you want to add more product(y/n): ");
    scanf(" %c", &more);
 
    if(more != 'y' && more!='Y'){
        printf("Total amount: Rp.%.2f\n\n", total);
    }

}while(more == 'y'|| more == 'Y');

    while (getchar() != '\n');
   printf("Do you want to apply discount(y/n)? ");
   scanf(" %c", &more);

   if (more == 'y' || more == 'Y'){
    printf("Apply discount percentage: ");
    scanf("%f", &discount);
    total = total - (total*(discount/100));
   }
   printf("Total amount: Rp.%.2f\n", total);

   do {
   printf("\nCash Tendered: ");
   scanf("%f", &cash);

   if (cash < total){
    printf("Insufficient cash! Please enter at least Rp.%.2f\n", total);

   }

   }while(cash < total);

   change = cash - total;
   printf("\nChange: Rp.%.2f\n", change);
   printf("\n====Receipt====\n");
   printf("Item    QTY   PRICE  TOTAL\n");
   
   for(int i = 0; i < sales_count; i++){
    printf("%s\t%d\t%.2f\t%.2f\n",
     rti[i].name,
     rti[i].quantity,
     rti[i].price,
     rti[i].line_total);
   }
   printf("\n---------------------------\n");
   if (discount > 0.0){
    printf("Discount: %.2f%%\n", discount);
   }
   printf("Total   : Rp.%.2f\n", total);
   printf("Cash    : RP.%.2f\n", cash);
   printf("Change  : Rp.%.2f\n", change);

 return 0;
}


int product_found(const char *serial, struct product *pt)
{

    FILE *ptr;
    ptr = fopen("inventory.txt", "r");
    if (ptr == NULL)
    {
        printf("Error! File could not be opened.\n");
        exit(1);
    }

        char file_serial[50];
        char file_name[50];
        float file_price;
        int file_stock;

        while (fscanf(ptr, "%49s %49s %f %d", file_serial, file_name, &file_price, &file_stock) == 4){
            if (strcmp(file_serial, serial) == 0){
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

    /* Sample inventory.txt format:
ITEM001 Laptop 15000.00 5
ITEM002 Mouse 250.00 10
ITEM003 Keyboard 500.00 8
ITEM004 Monitor 8000.00 3
*/

