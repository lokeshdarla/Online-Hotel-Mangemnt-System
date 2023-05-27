#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
struct customer
{
    char phnumber[16];
    char name[25];
    char address[50];
    char insttructions[100];
    char payment[6];
    float total;
    int orderid[15];
    int quantity[15];
    float discount;
    float tax;
    int count;
    int hotel;
    int itemid[10];
} cst;
struct food
{
    char name[25];
    float price;
};
struct food items[15];
int itemcount = 0;
int orderCount=0;
char filename[14];
char hotelname[20];
int x;
void delete();
void invoice();
void hotelMenu();
void printMenu();
void takeOrder();
void reviewOrder();
void confirmOrder();
void generateBill(int );
void printInvoice();
void extractMenu(char[], char[]);
void searchBill(char []);
void presentOrder();
void cancel();
void footer();
int main()
{
	system("cls");
    int choice,n,i;
    char id[16];
    a:
    printf("\t\t===========||COUNT THE MEMORIES NOT CALORIES||============");
    printf("\n\n\n\t\t\t\t1.Order Food\n\n");
    printf("\t\t\t\t2.View Previous Bill\n\n");
    printf("\t\t\t\t3.Exit");
    printf("\n\n\n\t\tEnter choice: ");
    scanf("%d",&n);
    system ("cls");
    switch(n){
    	
    	case 1:

    printf("\t\t\tHOTELS CURRENTLY AVAIALBLE ARE: ");
    printf("\n\n\n\t\t\t\t1.Biryani House \n\n");
    printf("\n\n\t\t\t\t2.Food Truck\n\n");
    printf("\n\n\t\t\t\t3.Eat Grid\n");
    printf("\n\n\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    fflush(stdin);
    switch (choice)
    {
    case 1:
        cst.hotel = 1;
        hotelMenu(1);
        break;
    case 2:
        printf("Welcome to Food Truck\n");
        cst.hotel = 2;
        hotelMenu(2);
        break;
    case 3:
        printf("Welcome to Eat Grid\n");
        cst.hotel = 3;
        hotelMenu(3);
        break;
    default:
        printf("Invalid hotel code");
    }
    break;
    case 2: 
    printf("Enter your phonenumber to get details: ");
        scanf("%s",id);
        fflush(stdin);
        printf("Fetching your order details");
        for(i=0;i<5;i++){
         printf(".");
        fflush(stdout);
        sleep(1);	
		}
        searchBill(id);
        break;
    case 3:
    	return 0;
    	break;
    default:
    	printf("Invalid choice");
    	goto a;
    	break;
}
    return 0;
}

void hotelMenu(int n)
{
    
    system ("cls");
    switch (n)
    {
    case 1:
        strcpy(filename, "hotel1menu.txt");
        strcpy(hotelname, "Biryani House");
        system ("cls");
    printf("\n\t\t\tWelcome to %s.", hotelname);
    printf("Here is the menu\n\n");
        printMenu(filename, hotelname);
        
        break;
    case 2:
        strcpy(filename, "hotel2menu.txt");
        strcpy(hotelname, "Food Truck");
        system ("cls");
    printf("\n\t\t\tWelcome to %s.", hotelname);
    printf("Here is the menu\n\n");
        printMenu(filename, hotelname);
        
        break;
    case 3:
        strcpy(filename, "hotel3menu.txt");
        strcpy(hotelname, "Eat Street");
        system ("cls");
    printf("\n\t\t\tWelcome to %s.", hotelname);
    printf("Here is the menu\n\n");
        printMenu();
        
        break;
    default:
        break;
    }
}
void printMenu()
{
    int i;
    int n;
    FILE *fp;
    fp = fopen(filename, "r");
    while (fscanf(fp, "%s %f\n", items[itemcount].name, &items[itemcount].price) != EOF)
        itemcount++;
    printf("\t\t\tS.no\t\tItem\t\t\tPrice\n");
    for (i = 0; i < itemcount; i++)
        printf("\t\t\t%d\t%s\t%2.f\n", i + 1, items[i].name, items[i].price);
    fclose(fp);
    takeOrder();
}

void takeOrder()
{
    int i = 0;
	int  n, m;
	int b=0;
    while (1)
    {
    b:
        printf("Enter item id(0 to checkout)                : ");
        scanf("%d", &n);
        if (n == 0)
            break;
        if (n > itemcount)
        {
            printf("Invalid item Id\n");
            printf("Try Again!!!!\n");
            goto b;
        }
        cst.orderid[orderCount] = n - 1;

    a:
        printf("Enter quantity of %s : ", items[cst.orderid[orderCount]].name);
        scanf("%d", &m);
        cst.quantity[orderCount] = m;
        if (m < 1)
        {
            printf("Invalid Quantity!!\n");
            printf("Enter again\n");
            goto a;
        }
        cst.total += items[n - 1].price * m;
        cst.itemid[b]=orderCount;
        b++;
        orderCount++;
    }
    reviewOrder();
}
void presentOrder(){
	int n,i;
printf("\n\t\t\t\t\tEntered order details: \n\n");
    printf("\t\t\tS.no\t\tItem\t\t\tQuantity\tPrice\n");
    cst.total=0;
    for (i = 0; i < orderCount; i++)
    {
        n = cst.orderid[i];
        printf("\t\t\t%d\t%s\t%d\t\t%.2f\n", i + 1, items[n].name, cst.quantity[i], cst.quantity[i] * items[n].price);
        cst.total += cst.quantity[i] * items[n].price;
    }	
}
void reviewOrder()
{
    int i, n, cho, a;
    system ("cls");
    presentOrder();
    printf("\nBill upto Now: %.2f\n", cst.total);
    printf("\n1.Want to modify something\n");
    printf("2.Continue to confirm order\n");
    printf("3.Want to cancel order\n");
    printf("\nEnter your choice: ");
    scanf("%d", &cho);
   
    switch (cho)
    {
    case 1:
    c:
        printf("\n1.Want to add something\n");
        printf("2.Want to delete something\n");
        printf("Enter your choice:");
        scanf("%d", &a);
        fflush(stdin);
        if (a == 1)
        {   system("cls");
        presentOrder();
        printf("\n\t\t\tHere is the menu: \n");
        itemcount=0;
        printMenu();
        }
        else if (a == 2){
        	 system("cls");
        	 presentOrder();
        	  delete();
		}
           
        else
        {
            printf("Invalid choice");
            goto c;
        }
        break;
    case 2:
        confirmOrder();
        break;
    case 3:
    	cancel();
    default:
        break;
    }
}
void confirmOrder()
{   
    cst.discount = cst.total * 0.01;
    cst.tax = cst.total * 0.005;
    cst.total += cst.tax - cst.discount;

    fflush(stdin);
    system("cls");

    printf("Enter your name: ");
    fgets(cst.name, 25, stdin);
    int len = strlen(cst.name);
    if (cst.name[len - 1] == '\n') cst.name[len - 1] = '\0';

    printf("Enter your phone number: ");
    scanf("%s",cst.phnumber);
    fflush(stdin);

    printf("Enter Delivery Address: ");
    fgets(cst.address, 50, stdin);
    len = strlen(cst.address);
    if (cst.address[len - 1] == '\n') cst.address[len - 1] = '\0';

    printf("Enter Delivery Instructions: ");
    fgets(cst.insttructions, 100, stdin);
    len = strlen(cst.insttructions);
    if (cst.insttructions[len - 1] == '\n') cst.insttructions[len - 1] = '\0';

    int choice;
    do {
        printf("Choose Mode of payment\n");
        printf("1. COD\t 2. ONLINE\n");
        scanf("%d", &choice);
        if (choice == 1) strcpy(cst.payment, "COD");
        else if (choice == 2) strcpy(cst.payment, "ONLINE");
        else printf("Invalid Choice, please try again\n");
    } while (choice != 1 && choice != 2);

    system("cls");
    int i;
    printf("Confirming your order");
    for( i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    system("cls");
    printf("Order confirmed..\n");
    system("cls");
    printf("Generating Bill");
    for( i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    system("cls");

    cst.count = orderCount;
    FILE *fp = fopen("orders.txt", "a");
    if (fp == NULL) {
        printf("Error in file opening\n");
        return;
    }
    fwrite(&cst, sizeof(struct customer), 1, fp);
    fclose(fp);

    x = 0;
    generateBill(x);
}

void generateBill(int k)
{
    int n = cst.hotel;
    char filename[14];
    char hotelname[20];
    switch (n)
    {
    case 1:
        strcpy(hotelname, "Biryani House");
        break;
    case 2:
        strcpy(hotelname, "Food Truck");
        break;
    case 3:
        strcpy(hotelname, "Eat Street");
        break;
    default:
        break;
    }
    int i;
    printf("\n\n\n");
    printf("Date                 :%s\n", __DATE__);
    printf("Hotel Name           :%s\n", hotelname);
    printf("Customer Name        :%s\n",cst.name);
    printf("Phone Number         :%s\n", cst.phnumber);
    printf("Address              :%s\n", cst.address);
    printf("Payment mode         :%s\n", cst.payment);
    printf("Delivery Instructions:%s\n", cst.insttructions);
    
    printf("\n---------------------------------------");
    printf("---------------------------------------\n");
    printf("Item Name   \t\t Quantity\t\t Price");
    printf("\n---------------------------------------");
    for (i = 0; i < orderCount; i++)
    {
        printf("---------------------------------------\n");
        printf("%s\t\t", items[cst.orderid[i]].name);
        printf("%d\t\t", cst.quantity[i]);
        printf("%.2f\t\t", cst.quantity[i] * items[cst.orderid[i]].price);
        printf("\n---------------------------------------");
    }
    printf("---------------------------------------\n");
    printf("Discount\t\t\t\t\t-%.2f\n", cst.discount);
    printf("Tax     \t\t\t\t\t %.2f", cst.tax);
    printf("\n---------------------------------------");
    printf("---------------------------------------\n");
    printf("\t\t\tGRAND TOTAL\t\t%2.f", cst.total);
    printf("\n---------------------------------------");
    printf("---------------------------------------\n");
    printf("\t\t\tTHANK YOU");
    printf("\n---------------------------------------");
    printf("---------------------------------------\n");
    if(k==0)
    footer();
    else 
    return ;
    printf("\n\n");
    printf("Press any key to continue...");
    getch();
    main();
}
void footer(){
	printf("\t\tYOUR ORDER IS GETTING READY");
}
void searchBill( char id[16])
{
    int i = 0;
    FILE *fp = fopen("orders.txt", "r");
    if (fp == NULL)
    {
        printf("\nError opening file");
        return;
    }
    while (fread(&cst, sizeof(struct customer), 1, fp))
    {
        if (strcmp(cst.phnumber,id)==0)
        {
        	x = 1;
            i = 1;
            break;
        }
    }
    fclose(fp);
    if (i == 0)
    {
        printf("\nNo data found for the given ID: %s", id);
    }
    else
    {   
        orderCount = cst.count;
        printInvoice();
    }
}


void printInvoice()
{ 
    int n = cst.hotel;
    char filename[14];
    char hotelname[20];
    switch (n)
    {
    case 1:
        strcpy(filename, "hotel1menu.txt");
        strcpy(hotelname, "Biryani House");
        extractMenu(filename, hotelname);
        break;
    case 2:
        strcpy(filename, "hotel2menu.txt");
        strcpy(hotelname, "Food Truck");
        extractMenu(filename, hotelname);
        break;
    case 3:
        strcpy(filename, "hotel3menu.txt");
        strcpy(hotelname, "Eat Street");
        extractMenu(filename, hotelname);
        break;
    default:
        break;
    }
}
void extractMenu(char filename[], char hotelname[])
{
    FILE *fp;
    fp = fopen(filename, "r");
    while (fscanf(fp, "%s %f\n", items[itemcount].name, &items[itemcount].price) != EOF)
        itemcount++;
    fclose(fp);
    generateBill(x);
}
void delete(){
	int cho,a,j,quant=0;
	int i;
	z:
printf("1.want to delete item\n");
printf("2.Want to change quantity of a particular item\n");
printf("3.Back\n");
printf("Enter your choice :                    ");
scanf("%d",&cho);
switch(cho){
	case 1:
		printf("Enter id of item you want to delete: ");
	    scanf("%d",&a);
	    a-=1;
    	for(i=0;i<orderCount;i++){
		if(a==cst.itemid[i]){
		for(j=i;j<orderCount;j++){
			cst.orderid[j]=cst.orderid[j+1];
			cst.itemid[j]=cst.itemid[j+1];
			cst.quantity[j]=cst.quantity[j+1];
		}
		orderCount--;
		}
    	}
        
    reviewOrder();
     break;
	 

    case 2:
    	printf("Enter order id of which you want to change quantity: ");
    	scanf("%d",&a);
    	a-=1;
    	for(i=0;i<orderCount;i++){
    		if(a==cst.itemid[i]){
    		printf("Enter the new quantity of : ");
    		scanf("%d",&quant);
    		cst.quantity[i]=quant;
			}
		}
		reviewOrder();
		break;
	case 3:
		reviewOrder();
		break;
	default:
		printf("INVALID CHOICE!!!\n Try again");
		goto z;
}

}
void cancel(){
	int n,i;
	printf("Do you want to cancel your order ?\n");
	printf("1.Cancel\n2.Back\n");
	printf("Enter your choice : ");
	scanf("%d",&n);
	if(n==1){
	itemcount=0;
	orderCount=0;
	printf("\nCancelling your order");
		for (i = 0; i < 5; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
	system ("cls");
	main();
	}
	else if(n==2){
		
		
		system ("cls");
		reviewOrder();
		
	}
	
	
	
}

