#include<stdio.h>
#include<string.h>

#include "inventory.h"

int main()
{
    char serial[50];
    char more = 'y';
    float total = 0.0, discount = 0.0;
    float cash = 0.0, change = 0.0;

    struct recipt_item rti[MAX_LIMITS];
    int sale_count = 0; 
    
    do {

        printf("Enter the serial: ");
        scanf("%49s", serial);
        struct  product pt;

        if (product_found(serial, &pt)){
            int quantity = 1;
            printf("Product found: %s - Rp.%.2f\n", pt.name, pt.price);
            printf("In stock: %d\n", pt.stock);
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if (quantity > pt.stock){
                printf("Insufficent stock! Only %d items are available.\n", pt.stock);
                continue;
            }

            float line_total = pt.price * quantity;
            total += line_total;

            if (sale_count < MAX_LIMITS)
             {
                  strcpy(rti[sale_count].name, pt.name);
                  rti[sale_count].price = pt.price;
                  rti[sale_count].quantity = quantity;
                  rti[sale_count].line_total = line_total;
                  sale_count++;
             }

          printf("%d x %s added. Line total: RP.%.2f\n\n", quantity, pt.name, line_total);
         }

        else {
            printf("Product with serial %s not found in the inventory.\n", serial);
         }
          while(getchar() != '\n');
          printf("Do you want to add more product(y/n)? ");
          scanf("%c", &more);
          while(getchar() != '\n');

          if (more != 'y' && more != 'Y'){
            printf("Total amount: Rp.%.2f\n", total);
          }
          
    }while(more == 'y' || more == 'Y');
   
    

     printf("Do you want to apply discount(y/n)? ");
     scanf("%c", &more);

     while(getchar() != '\n');

     if (more == 'y' ||  more == 'Y'){
        printf("Discount percentage: ");
        scanf("%f", &discount);
        total = total - (total*(discount/100));
     }
     
     printf("Total Amount: Rp.%.2f\n", total);
    
     do { 
        printf("Cash Tendered: ");
        scanf("%f", &cash);

        if (cash < total){
            printf("Insufficient cash! Please enter at least Rp.%.2f\n", total);
        }
     }while(cash < total);

     change = cash - total;
     printf("Change: Rp.%.2f\n", change);

     printf("\n====Receipt====\n");
     printf("Item    QTY     PRICE           TOTAL\n");

     for(int i = 0; i < sale_count; i++){
        printf("%s\t%d \t%.2f \t%.2f\n",
            rti[i].name,
            rti[i].quantity,
            rti[i].price,
            rti[i].line_total);
        }
        printf("\n---------------------------\n");
    if (discount > 0.0) {
        printf("Discount: %.2f%%\n", discount);
    }

    printf("Total   : Rp.%.2f\n", total);
    printf("Cash    : RP.%.2f\n", cash);
    printf("Change  : Rp.%.2f\n", change);

    return 0;
}