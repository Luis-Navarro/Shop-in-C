#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product
{
	char* name;
	double price;
};
struct ProductStock
{
	struct Product product;
	int quantity;
};
struct Shop 
{
    double cash;
    struct ProductStock stock[20];
    int index;
};
struct Customer
{
	char* name;
	double budget;
    struct ProductStock ShoppingList[10];
     //index variable is required to keep track of the amount of items in the Shopping list. It will be referentiated later, when calling ShoppingList
    int index;
};
void printProduct(struct Product p)
{
    printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n",p.name, p.price);
    printf("---------------------------\n");
}

void printCustomer(struct Customer c)
{
    printf("COSTUMER NAME: %s \nCOSTUMER BUDGET: %.2f\n",c.name, c.budget);
    printf("---------------------------\n");
    for(int i=0; i<c.index; i++) //This for loop requires to know the number of items in ShoppingList
        {
            printProduct(c.ShoppingList[i].product);
            printf("%s ORDERS %d OF ABOVE PRODUCT\n\n", c.name, c.ShoppingList[i].quantity);
            double cost = c.ShoppingList[i].quantity * c.ShoppingList[i].product.price;
            printf("The cost to %s will be %.2f \n\n",c.name, cost);
        }
}
 
struct Shop createAndStockShop()
{
    
//Reading stock file in CSV as per Stock Overflow instructions:
    FILE * fp;    
    char* line = NULL;
    size_t len=0;
    ssize_t read;
//opening the specified file
    fp = fopen("stock.csv","r");
//if file is empty, exit
    if (fp ==NULL)
        exit(EXIT_FAILURE);
//While loop reading each line in the file
    getline(&line, &len, fp);
    double CashInShop = atof(line);
    struct Shop shop = {CashInShop};

    while ((read = getline(&line, &len, fp)) !=-1) 
    {
        //printf("%s IS A LINE \n", line);
// Now we need to extract the elements in each line as a variable. 
// strtok will be used to tokenise strings
// Tokenised items are all strings. To format items correctly atoi (integer) and atof (float) will be used:
        char *n = strtok(line, ",");
        char *p = strtok(NULL, ",");
        char *q = strtok(NULL, ",");
        int quantity = atoi(q);       
		double price = atof(p);
//Memory needs to be allocated for string name, since atoi and atof are already allocating memory for those items
        char *name= malloc(sizeof(char) * 50);
        strcpy(name,n);
        struct Product product = {name , price};
        struct ProductStock stockItem = {product, quantity};
        shop.stock[shop.index++] = stockItem;
//        printf("NAME OF PRODUCT %s PRICE %.2f QUANTITY %d\n", name, price, quantity); 
    }

    return shop;
}

void printShop(struct Shop s)
{
    printf("Shop has %.2f in cash\n", s.cash);
    for (int i = 0; i<s.index; i++)
    {
        printProduct(s.stock[i].product);
        printf("The shop has %d of that product\n\n", s.stock[i].quantity);
    }
}



int main(void)
{
//	 struct Customer Luis = {"Luis", 100.0};
//	//printCustomer(Luis);
//	
//	struct Product coke = {"Can Coke", 1.10};
//	//printProduct(coke); 
//    struct Product bread = {"Bread", 0.7};
//	
//	struct ProductStock cokeStock = {coke , 20};
//	struct ProductStock breadStock = {bread , 2};
//    Luis.ShoppingList[Luis.index++] = cokeStock;
//    Luis.ShoppingList[Luis.index++] = breadStock;
//    //this is adding a number to index for each item in ShoppingList
//    printCustomer(Luis);

    struct Shop shop = createAndStockShop();
    printShop(shop);

   
	//printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
	
	return 0;
}
