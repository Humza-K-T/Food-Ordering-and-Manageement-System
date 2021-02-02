/*
----------------------
FoCP Semester Project  
----------------------
"FoodPanda Of NUST"
----------------------

-------
 LOGIC 
-------

The Program is divided into 2 main parts which are further divided into multiple parts according to need.

Part 1: Shop Side
Part 2: Customer Side


Part 1: This part allows you to add, edit and modify shops which can be accessed by the users.
Part 2: This part allows you to view menus and make orders.

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//Structures Declaration

//Structure to hold data of dishes of each shop
typedef struct Menu_details {
	char dish_name[20]; //malai roll
	char dish_category[20]; //paratha_roll
	int price; //250
	int dish_number; //dish number in array
	char shop_name[50];

}Menu_struct;

//structure to hold complete data of each shop
typedef struct shop_details {
	char username[50]; //Humza_Khawar
	char shop_name[50]; //Retro
	char contact_number[25];//0312-1234567
	char password[30];//pass_1234
	char address[100];//Retro , near razi hostel,nust
	char timings[30];
	int total_dishes; //25 dishes
	Menu_struct dishes[50];
	int shop_number_in_data; //shop number in array

}shop;





//Structure to hold the data of order made my user
typedef struct Bill_details {
	Menu_struct  cart[50]; //list of ordered items
	int cart_counter; //total items counter
	int finalbill;
	char time[50];
}Bill;


//structure to hold complete data of each user
typedef struct User_details
{	char username[50]; //Humza_Khawar
	char contact_number[30];//0312-1234567
	char password[30];//pass_1234
	char address[70];//Retro , near razi hostel,nust
	Bill last_order;
	int user_number_in_data;//user number in data
} user;


//variable Initializations


shop shops_data[100] = { NULL };//database of shops
shop active_shop = { NULL };//current shop in system being modified
int total_shops = 0;//total shops in database



user user_data[100] = { NULL };//database of users
user active_user = { NULL };//current user in system being modified
int total_users = 0;//total users in database



Bill active_bill;//Current bill of user

Menu_struct total_dishes[1000] = { NULL }; //total dishes in the database
int total_menu = 0; //total dish counter




FILE* fileptr = NULL;  //file pointer
time_t t;  //time
int i = 0;//loop variable


void get_database();  //takes data from files and stores it in arrays for faster and easier access
void save_database(); //function to store data in a file



int input(int, int); //(0:compare with shop data   1:compare with user data)(0:check for new user   1:check for old user)  : return 1 if data found

// functions for shop owners


void shop_main(); //main function for shop owners 
void shop_creation();//function to deal with shop creation
void shop_edit();//function to deal with shop editing
void shop_summary();//fuction to display shop sale history


void dish_creation();//function to deal with dish creation
void dish_edit();//function to deal with dish editing


//all dish categories

char categories[11][20] = { "Paratha","Wrap","Burger","Steak","Wings","Chinese","BBQ","Desi_Food","Biryani","Sideline","Drinks" };




// functions for customers

void customer_main();   //main lobby for the customer
void new_customer();    //functon for new customer
void old_customer();	//function for returning customer
void after_login();		//function to display choices after logging in


void all_dishes();		//function which displays all dishes sorted according 
void all_shops();		//function which displays menu according to shop choice
void specific_shop();	//function which displays menu of the last shop from which user purchased




//main function
void main()
{

	//import the data of all created shops and user in arrays shops_data and user_data
	get_database();


	int first_choice = 0;

	//Welcome Screen
	printf("\n\t\t\t  ***Welcome to the FoodPanda of NUST***");


	while (first_choice != 3 && first_choice != 2 && first_choice != 1)//keeps executing until user chooses to exit
	{
		time(&t);
		//Getting choice of user
		printf("\n\n\t\t\t\t\t1.Customer\n\t\t\t\t\t2.Shop Owner\n\t\t\t\t\t3.Exit");

		printf("\n\nChoose your status or press 3 to exit: ");

		scanf("%d", &first_choice);

		switch (first_choice)
		{
		case 1:

			//go to the customer menu
			system("cls");
			customer_main();
			break;
		case 2:
			//go to the shop menu
			system("cls");
			shop_main();
			break;
		case 3:

			//exit
			printf("\n\n**************************Thank you for choosing NUST FoodPanda. Do give us another visit.***************************\n");
			break;
		default:
			printf("\nWrong Input. Please Try Again.");
			break;
		}
		break;
	}

	//save all updated data in the files
	save_database();
}


//getting data from files
void get_database()
{


	FILE* fileptr = NULL;
	//getting details of shops

	fileptr = fopen("shop_data", "a+");
	if (fileptr == NULL)
	{
		printf("\nError Opening Shop Database"); //file pointor pointer error handling
	}
	else
	{
		fread(&shops_data, sizeof(shops_data), 1, fileptr);//reads data of shops from file

		fclose(fileptr);
		fflush(fileptr);

		int i = 0;

		while (i < sizeof(shops_data))
		{
			if (strcmp(shops_data[i].username, "") != 0) //counting the total shops in array
			{
				total_shops++;
			}
			else
			{
				break;
			}
			i++;

		}

	}



	//getting the data of users

	fileptr = fopen("users_data", "a+");

	if (fileptr == NULL)
	{
		printf("\nError Opening Shop Database"); //file pointor pointer error handling
	}
	else
	{

		fread(&user_data, sizeof(user_data), 1, fileptr); //reads data of users from file
		fclose(fileptr);
		fflush(fileptr);
	}

	i = 0;//resetting the counter
	while (i < sizeof(user_data))
	{
		if (strcmp(user_data[i].username, "") != 0)//counting users in data
		{
			total_users++;
		}
		else
		{
			break;
		}
		i++;
	}
}

//saving updated data in files
void save_database()
{
	FILE* fileptr = NULL;


	//getting details of shops

	fileptr = fopen("shop_data", "wb");
	if (fileptr == NULL)

	{
		printf("\nError Opening Shop Database"); //file pointor pointer error handling
	}
	else
	{
		fwrite(shops_data, sizeof(shops_data), 1, fileptr);//writing updated shop data

		fclose(fileptr);
		fflush(fileptr);
	}

	fileptr = fopen("users_data", "wb");
	if (fileptr == NULL)
	{
		printf("\nError Opening Shop Database"); //file pointor pointer error handling
	}
	else
	{

		fwrite(&user_data, sizeof(user_data), 1, fileptr);//writing updated user data
		fclose(fileptr);
		fflush(fileptr);
	}

}


//main shop function
void shop_main() {


	int choice = 1;
	printf("\n\nWelcome to Shop Owners Menu. \n");
	printf("\nPress '1' for New Shop Creation ");
	printf("\nPress '2' for Existing Shop login");
	printf("\nPress any other key to Exit Shop Owners Menu\n");
	printf("\nEnter Choice: ");
	scanf("%d", &choice);

	//sending control to desired function

	while ((choice == 1) || (choice == 2) || (choice == 3))//keeps executing until user chooses to exit
	{
		switch (choice)
		{
			case(1): {
				system("cls");
				shop_creation();	//shop creation menu
				break;
			}
			case(2):
			{	
				system("cls");
				shop_edit();	//shop editing menu
				break;
			}
			default:
				break;
		}


		shops_data[active_shop.shop_number_in_data] = active_shop;  //stores the updated data of shop in shop database
		system("cls");


		//reprinting menu until user exits

		printf("\n\n Welcome to Shop Owners Menu. \n\n");
		printf("\n Press 1 for New Shop Creation \n");
		printf("\n Press 2 for Existing Shop login\n");
		printf("\n Press any other key to Exit Shop Owners Menu\n");
		printf("\n\nEnter Choice: ");
		scanf("%d", &choice);

	}

}

//(0:compare with shop data   1:compare with user data)
//(0:check for new user/shop   1:check for old user\shop)  : return 1 if data found
int input(int database_check, int type) 
{
										//(0:compare with shop data   1:compare with user data)
									//(0:check for new user/shop   1:check for old user\shop)  : return 1 if data found


	int flag = 0;  //flag to show the output of search in databases

	switch (database_check)
	{
		case (0)://check in shop database
		{
			for (int i = 0; i < total_shops; i++)
			{
				if (strcmp(active_shop.username, shops_data[i].username) == 0)
				{
					flag++;

					if (type == 0)//username exisits. new account not possible
					{
						return flag;

					}
					else //retrieve data of the shop
					{
						active_shop = shops_data[i];
						active_shop.shop_number_in_data = i;
						return flag;
					}
				}
			}
			break;
		}


		case(1)://user database check
		{
			for (int i = 0; i < total_users; i++)
			{
				if (strcmp(active_user.username, user_data[i].username) == 0)
				{
					flag++;

					if (type == 0)//user_id exisits. new account not possible
					{
						return flag;

					}
					else //retrieve data of the user
					{
						active_user = user_data[i];
						active_user.user_number_in_data = i;
						return flag;
					}
				}
			}
			break;
		}

		default:
			printf("\nWrong parameters used for check in database");
			break;
	}

	return flag;
}

//function to create a new shop
void shop_creation()
{
	system("cls");
	printf("\nWelcome to Shop Account Creation Menu\n\n");

	printf("\nNo Spaces can be included.\n\n");

	printf("\nEnter username: ");
	

	scanf("%s", &active_shop.username);
	
	while (input(0, 0) != 0) {		//check in shop database for new user. flag would be non zero if the user exists in the data base		

		printf("\nThe User Name already Exists. Kindly Try another Name");

		fgetc(stdin);
		printf("\nEnter username: ");

		scanf("%s", &active_shop.username);


	}
	printf("\nEnter Password: ");
	
	
	scanf("%s", &active_shop.password);
	printf("\nEnter Name of Shop with \"_\" instead of Spaces: ");

	scanf("%s", &active_shop.shop_name);

	printf("\nEnter Contact Number of Shop i.e +92-312-5472423 : ");

	scanf("%s", &active_shop.contact_number);

	printf("\nEnter Address of Shop with \"_\" instead of Spaces: ");

	scanf("%s", &active_shop.address);

	printf("\nEnter timings of Shop with \"_\" instead of Spaces : ");

	scanf("%s", &active_shop.timings);


	//sets the dish counter to zero in new shop
	active_shop.total_dishes = 0;
	//assigns the shop number to the last slot of the shop data array
	active_shop.shop_number_in_data = total_shops;

	//updates active shop data in shop database
	shops_data[total_shops] = active_shop;

	//increases the shop counter
	total_shops++;

	printf("\n\nShop Created Successfully. Would You Like edit it and add exciting Dishes?");
	int choice = 0;

	
	printf("\n Enter 1 for \"Yes\" \n Press any key to return to main menu.\n Enter Choice: ");
	scanf("%d", &choice);

	if (choice == 1) 
	{ //sends the user to shop edit menu
		shop_edit();
	}
}


//function to edit shop
void shop_edit() {

	system("cls");

	printf("\nWelcome to Shop Editing Menu\n");

										//login screen for user
	printf("\nEnter Username: ");

	scanf("%s", &active_shop.username);

	while (input(0, 1) == 0) {		//check in shop database for new user. flag would be non zero if the user exists in the data base		

		printf("\nThe User Name is not found. Kindly Try again\n");

		printf("\nEnter username: ");

		scanf("%s", &active_shop.username);

	}

	char temp_password[sizeof(active_shop.password)];

	printf("\nEnter Password: ");

	scanf("%s", &temp_password);

	//checks for correct password

	while ((strcmp(active_shop.password, temp_password) != 0))
	{
		printf("\nWrong Password. Try Again!!\n\n");

		printf("Enter password again: ");

		scanf("%s", &temp_password);
	}

	system("cls");

	//successful login
	//shop edit menu


	printf("\n\nWelcome to %s \nYou Have successfully Logged In\n\n", active_shop.shop_name);

	printf("\n\n1.Create Dish\n2.Edit Dish\n3.View Sale History\n4.Exit");

	printf("\n\nPress Any other key to Exit this Menu.\n");

	int choice;

	printf("\nEnter Choice: ");
	scanf("%d", &choice);

	while ((choice == 1) || (choice == 2) || (choice == 3)) //keeps executing until user chooses to exit
	{
		switch (choice)
		{
		case(1): {//dish creation menu
			system("cls");
			dish_creation();
			break;
		}
		case(2): {//dish price change menu
			system("cls");
			dish_edit();
			break;
		}
		case(3):	//shop sale summary menu
			system("cls");
			shop_summary();
			break;

		default:
			break;
		}

		system("cls");

		printf("\n\nWelcome to %s  \n\n", active_shop.shop_name);

		printf("\n\n1.Create Dish\n2.Edit Dish\n3.View Sale History\n4.Exit");

		printf("\nPress Any other key to Exit this Menu.\n");

		printf("\n Enter Choice: ");
		scanf("%d", &choice);

	}
}

//function for dish creation
void dish_creation() {


	//new dish creation Menu


	system("cls");
	printf("\n\nWelcome to Dish Creation Menu\n\n");

	printf("\nEnter Dish Name : ");  //dish name
	scanf("%s", &active_shop.dishes[active_shop.total_dishes].dish_name);

	printf("\n Enter Dish Price : ");	//dish price
	scanf("%d", &active_shop.dishes[active_shop.total_dishes].price);

	strcpy(active_shop.dishes[active_shop.total_dishes].shop_name, active_shop.shop_name); //add shop name to the dish details to be used in menu

	printf("\nChoose the category of the dish");

	printf("\n\n 1.Paratha \n 2.Wrap\n 3.Burger\n 4.Steak\n 5.Wings\n 6.Chinese\n 7.BBQ\n 8.Desi Food\n 9.Biryani\n 10.Sideline\n 11.Drinks ");

	int choice = 0;

	printf("\nEnter Choice: ");
	scanf("%d", &choice);


	while ((choice <= 0) && (choice > 10))//checks if user entered the correct choice
	{
		printf("\nWrong Choice. Try Again!\n");
		scanf("%d", &choice);

	}

	//assigns the category according to user choice
	switch (choice)
	{
		case(1):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Paratha");
			break;
		case(2):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Wrap");
			break;
		case(3):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Burger");

			break;
		case(4):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Steak");

			break;
		case(5):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Wings");

			break;
		case(6):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Chinese");

			break;
		case(7):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "BBQ");

			break;
		case(8):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Desi_Food");

			break;
		case(9):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Biryani");

			break;
		case(10):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Sideline");

			break;
		case(11):
			strcpy(active_shop.dishes[active_shop.total_dishes].dish_category, "Drinks");

			break;

		default:
			break;
	}


	//gives the dish a dish number according to the dishes already available in the shop

	active_shop.dishes[active_shop.total_dishes].dish_number = active_shop.total_dishes;

	//increases shop dish counter
	active_shop.total_dishes++;

	//updates shop data in the shop database
	shops_data[active_shop.shop_number_in_data] = active_shop;

	printf("\nDish Added Successfully. Press Any Key to Exit this menu");
	getchar();
	getchar();

}

//function to change dish price
void dish_edit() {

	system("cls");
	int choice;
	printf("\n\nWelcome to Dish Edit Menu\n\n");


	//displays the already available dishes

	if (active_shop.total_dishes != 0)
	{
		printf("\nYour Dishes are Following\n");//displaying dishes
		for (int i = 0; i < active_shop.total_dishes; i++)
		{
			printf("\n%d. %s %d %s", (i + 1), active_shop.dishes[i].dish_name, active_shop.dishes[i].price, active_shop.dishes[i].dish_category);
		}

		printf("\n\n");

		printf("\nWhich dish would you like to edit? \n Enter Choice: ");//asks user for dish choice

		scanf("%d", &choice);

		printf("\n\n Enter new price for %s", active_shop.dishes[choice - 1].dish_name); //asks for new price
		scanf("%d", &active_shop.dishes[choice - 1].price);

		choice = 1;
		while (choice == 1) {	//asks user if he wants to edit any other dish

			printf("\nChanges Saved!!. \n\nPress 1 to Edit Another Dish.\nPress any other key to exit this menu\nEnter Choice: ");
			scanf("%d", &choice);
			if (choice == 1)
			{
				dish_edit();
			}

		}
	}
	else
	{
		// if no dishes are available in the shop

		printf("\nYou have not created Any Dish. Kindly Create a dish");
	}

	printf("\n Press Any Key to Exit");
	getchar();
	getchar();
}

//function to view shop sale summary
void shop_summary() {

	FILE* fileptr = { NULL };
	//opening the shopname file
	fileptr = fopen(active_shop.shop_name, "r");

	if (fileptr==NULL)
	{	
		//if summary file doesnt exist

		printf("\nNo sale Found");

	}
	else
	{
		// prints the summary file from start to end

		char a = fgetc(fileptr);	//counter to check for end of file

			while (a!=EOF)
			{
				char  data[100] = { 0 };

				fgets(data, sizeof(data), fileptr);
				printf("\n%c%s",a, data);

				a = fgetc(fileptr);


			}
		
	}
	//exiting the function
	printf("\nPress any key to continue!\n");
	getchar();
	getchar();
	system("cls");
}




//customer part begins here



//main function for customer
void customer_main()
{
	
	int choice = 0;
	total_menu = 0;

	//counting the total dishes in every shop and copying all dish data to total_dishes array

	for (int j = 0; j < total_shops; j++)
	{
		for (int k = 0; k < shops_data[j].total_dishes; k++)
		{
			total_dishes[total_menu] = shops_data[j].dishes[k];
			total_menu++;
		}
	}

	//customer menu

	printf("\n\nWelcome to Customer's Menu.\n");

	printf("\n1.New Customer\n2.Returning Customer\n3.Back");

	printf("\n\nChoose how to want to Proceed: ");

	scanf("%d", &choice);


	switch (choice)
	{
		case 1:
			system("cls"); //sending control to new customer menu
			new_customer();
			break;
		case 2:
			system("cls");//sending control to old customer menu
			old_customer();
			break;
		case 3:
			system("cls");//exiting program
			printf("\n\n**************************Thank you for choosing NUST FoodPanda. Do give us another visit.***************************\n");
			break;
		default:
			printf("\nSorry wrong input. Please Try Again.");
			customer_main();

	}

}

//function for new customer

void new_customer()
{

	//account creation menu

	printf("\nPlease enter your username: ");
	scanf("%s", &active_user.username);

	while (input(1, 0) != 0)//checks for username in database
	{
		printf("\nUsername is invalid. Try Again!!");

		printf("\nPlease enter your username with \"_\" instead of Spaces: ");
		scanf("%s", &active_user.username);
	}

	printf("Enter your contact number i.e +92-312-5472423 : ");
	scanf("%s", &active_user.contact_number);

	printf("Enter you addresswith \"_\" instead of Spaces: ");
	scanf("%s", &active_user.address);

	printf("Please enter the password for your account: ");
	scanf("%s", &active_user.password);


	//assigns the user number the last number in user data array


	active_user.user_number_in_data = total_users;
	user_data[total_users] = active_user;

	total_users++;

	system("cls");
	printf("Account created successfully. Now you can login to your newly created account.\n");
	//returns to customer menu
	customer_main();
}

//function for old customer
void old_customer()
{
	//password vaidating variable
	char temp_password[sizeof(active_user.password)];

	//login screen

	printf("\nEnter Username: ");
	scanf("%s", &active_user.username);

	while (input(1, 1) == 0) {		//check in shop database for new user. flag would be non zero if the user exists in the data base		

		printf("\nThe User Name is not found. Kindly Try again\n");


		printf("\nEnter username: ");
		scanf("%s", &active_user.username);
	}


	printf("\nEnter Password: ");
	scanf("%s", &temp_password);

	while ((strcmp(active_user.password, temp_password) != 0)) { //keeps taking password until correct password is entered

		printf("\nWrong Password. Try Again!!\n\n");
		printf("Enter password again: ");
		scanf("%s", &temp_password);
	}

	after_login();//moves to after login screen
}


//function for display of choices to the customer
void after_login()
{

	//after login screen

	int choice = 0;
	while (choice != 4)
	{
		system("cls");
		//welcoming the user
		printf("\n\nWELCOME %s! WHAT WOULD YOU LIKE TO ORDER TODAY?\n", active_user.username);


		if (strcmp("",active_user.last_order.cart[0].shop_name) != 0)//if the user is returning customer
		{
			printf("\n\nYour Last Order was from %s on %s\n", active_user.last_order.cart[0].shop_name, active_user.last_order.time);
		}
		if (strcmp("", active_user.last_order.cart[0].shop_name) != 0)//choices if the user is returning customer
		{
			printf("\nPRESS '1' TO VIEW ALL DISHES\nPRESS '2' TO VIEW ALL SHOPS\nPRESS '3' TO GO Directly to %s \nPRESS '4' to go BACK\n", active_user.last_order.cart[0].shop_name);
			printf("\nYour choice: ");
			scanf_s("%d", &choice);
			switch (choice)
			{
			case 1:
				system("cls");
				all_dishes(); //displays all dishes sorted according to categories
				break;
			case 2:
				system("cls");
				all_shops(); //displays all available shops
				break;
			case 3:
				system("cls");
				specific_shop(); //displays the menu of last shop user ordered from
				break;

			default:
				printf("\nWRONG INPUT! TRY AGAIN.");
			}
			break;
		}
		else//choices if the user is not a returning customer
		{
			printf("\nPRESS '1' TO VIEW ALL DISHES\nPRESS '2' TO VIEW ALL SHOPS\nPRESS '3' TO GO BACK\n");
			printf("\nYour choice: ");
			scanf_s("%d", &choice);
			switch (choice)
			{
				case 1:
					system("cls");
					all_dishes(); //displays all dishes sorted according to categories
					break;
				case 2:
					system("cls");
					all_shops(); //displays all available shops
					break;
				case 3:
					system("cls");
					specific_shop(); //displays the menu of last shop user ordered from
					break;

				default:
					printf("\nWRONG INPUT! TRY AGAIN.");
			}
			break;
		}

	}
}

//function to display menu of last shop user ordered from
void specific_shop() {
	int dishchoice = 0;
	active_bill.finalbill = 0;
	
	printf("\t\t\t\t   More from %s:", active_user.last_order.cart[0].shop_name);
	printf("\n\t\t\t          --------------\n\n");

	//displays the dishes sorted according to categories
	for (int i = 0; i < 11; i++)
	{
		printf("\n\t\t\t\t      %s", categories[i]);
		printf("\n\t\t\t\t-----------------");
		for (int j = 0; j < total_menu; j++)
		{
			if ((strcmp(categories[i], total_dishes[j].dish_category ) == 0)&& (strcmp(total_dishes[j].shop_name, active_user.last_order.cart[0].shop_name) == 0))
			{
				printf("\n\t\t         Dish ID: %d %s for Rs.%d \n", (j + 1), total_dishes[j].dish_name,total_dishes[j].price);
			}
		}
	}
	printf("\n\nPlease enter the id for the dish you want to order: ");
	scanf_s("%d", &dishchoice);



	//keeps asking for dish choice until user exits
	while (dishchoice != 0)
	{
		//updates the dish details in the cart of active bill 
		active_bill.cart[active_bill.cart_counter] = total_dishes[dishchoice - 1];
		active_bill.cart_counter++;
		active_bill.finalbill += total_dishes[dishchoice - 1].price;


		printf("\nOrder noted.\n(Remember press 0 to finish ordering)\nAnything else  : ");

		scanf("%d", &dishchoice);
	}


	system("cls");
	//displaying the bill


	printf("\nYour cart is: \n");

	//displays all dish details in the cart

	for (i = 0; i < active_bill.cart_counter; i++)
	{
		printf("\n\"%s\" for   Rs.%d   from %s", active_bill.cart[i].dish_name, active_bill.cart[i].price, active_bill.cart[i].shop_name);
		printf("\n\t\t     +");

	}

	//printing total bill

	printf("\n----------------------------------------");
	printf("\nTotal bill is :  Rs.%d\t\t%s", active_bill.finalbill, ctime(&t));
	printf("----------------------------------------");

	//updating the last order details of the user


	strcpy(active_bill.time, ctime(&t));
	active_user.last_order = active_bill;
	user_data[active_user.user_number_in_data] = active_user;
	char line[] = "----------------------";

	//adding bill details to the shop summary
	FILE* fileptr = { NULL };
	fileptr = fopen(active_bill.cart[0].shop_name, "a+");
	if (fileptr == NULL) {
		printf("\nError opening %s summary file", active_bill.cart[0].shop_name);
	}
	else
	{
		fprintf(fileptr, "\n Date: %s\n", ctime(&t));
		for (int i = 0; i < active_bill.cart_counter; i++)
		{
			
			fprintf(fileptr, "%s %s %d \n", active_bill.cart[i].dish_name, active_bill.cart[i].dish_category, active_bill.cart[i].price);
		}
		fprintf(fileptr, "%s\n", line);
		fclose(fileptr);
		fflush(fileptr);
	}

	printf("\n\nPress any key to continue");
	getchar();
	getchar();
	printf("\n\n**************************Thank you for choosing NUST FoodPanda. Do give us another visit.***************************\n");


}

//fuction to display all dishes sorted according to category
void all_dishes()
{
	int dishchoice = 10;

	printf("\nALL DISHES ARE SORTED IN CATEGORIES \n\n");

	//loop to compare categories and display all thee sorted dishes
	for (int i = 0; i < 11; i++)
	{
		printf("\n\t\t\t\t      %s", categories[i]);
		printf("\n\t\t\t\t-----------------");
		for (int j = 0; j < total_menu; j++)
		{
			if (strcmp(categories[i], total_dishes[j].dish_category) == 0)
			{
				printf("\n\t\t   Dish ID: %d %s for Rs.%d from shop:%s\n", (j + 1), total_dishes[j].dish_name, total_dishes[j].price, total_dishes[j].shop_name);
			}
		}
	}
	//getting choice of user
	printf("\nPlease enter the id for the dishes you want to order:  ");
	scanf("%d", &dishchoice);

	//printing the menu again until user wants to exit
	while (dishchoice != 0)
	{
		system("cls");
		printf("\nOrder noted.\n\t\t\t          --------------\n"
			"\t\t\t\t   More from %s:", total_dishes[dishchoice - 1].shop_name);
		printf("\n\t\t\t          --------------\n\n");


		for (int i = 0; i < 11; i++)
		{
				printf("\n\t\t\t\t      %s", categories[i]);
				printf("\n\t\t\t\t-----------------");
				for (int j = 0; j < total_menu; j++)
				{
					if ((strcmp(categories[i], total_dishes[j].dish_category) == 0) && ((strcmp(total_dishes[dishchoice - 1].shop_name, total_dishes[j].shop_name)==0)))
					{
						printf("\n\t\t         Dish ID: %d %s for Rs.%d \n", (j + 1), total_dishes[j].dish_name, total_dishes[j].price);
					}
				}
		}

		//updating bill details and cart

		active_bill.cart[active_bill.cart_counter] = total_dishes[dishchoice - 1];
		active_bill.cart_counter++;
		active_bill.finalbill += total_dishes[dishchoice - 1].price;
		
		printf("\n(Remember press 0 to finish ordering)\n");
		printf("\nCurrent order has been noted. \nWould you like anything else: ", total_dishes[dishchoice - 1].shop_name);
		scanf_s("%d", &dishchoice);

	}


	//displaying bill
	system("cls");

	printf("\nYour cart is: \n");

	//displaying cart
	for (i = 0; i < active_bill.cart_counter; i++)
	{
		printf("\n\"%s\" for   Rs.%d   from %s", active_bill.cart[i].dish_name, active_bill.cart[i].price, active_bill.cart[i].shop_name);
		printf("\n\t\t     +");

	}


	//displaying total bill
	printf("\n------------------------------------------------------------");
	printf("\nTotal bill is :  Rs.%d\t   %s", active_bill.finalbill, ctime(&t));
	printf("------------------------------------------------------------");


	char line[] = "--------------------------";

	//updating user's last order

	strcpy(active_bill.time, ctime(&t));
	active_user.last_order = active_bill;
	user_data[active_user.user_number_in_data] = active_user;



	printf("\n\nPress any key to continue");

	//updating the sale history of the shop

	FILE* fileptr = { NULL };
	fileptr = fopen(active_bill.cart[0].shop_name, "a+");//opening the shop summary file




	if (fileptr == NULL) {
		printf("\nError opening %s summary file", active_bill.cart[0].shop_name);
	}
	else
	{
		fprintf(fileptr, "\n Date: %s\n", ctime(&t));

		for (int i = 0; i < active_bill.cart_counter; i++)
		{
			
			fprintf(fileptr, "%s %s %d \n", active_bill.cart[i].dish_name, active_bill.cart[i].dish_category, active_bill.cart[i].price);
		}

		fprintf(fileptr, "%s", line);

		fclose(fileptr);

		fflush(fileptr);

	}

	getchar();
	getchar();

	printf("\n\n**************************Thank you for choosing NUST FoodPanda. Do give us another visit.***************************\n");
}


//function to display the all available shops
void all_shops()
{
	char line[50] = "--------------------------";
	int shopchoice = 0;
	int dishchoice = 0;

	printf("\nTHE FOLLOWING ARE ALL SHOPS IN NUST\n");


	//printing all available shops


	while (shopchoice < 1 || shopchoice > 11)
	{
		for (int i = 0; i < total_shops; i++)
		{
			printf("\n\t\t\t\tSHOP ID - %d:\t%s\n", i + 1, shops_data[i].shop_name);
		}

		//asking for user choice


		printf("\nPlease enter the id for the shop you want to order from: ");
		scanf_s("%d", &shopchoice);

		if (shopchoice < 1 || shopchoice > 11)
		{
			printf("\nINVALID CHOICE! TRY AGAIN!\n");
		}
	}

	//printing the menu of the shop sorted according to categories


	for (int i = 0; i < 11; i++)
	{
		printf("\n\t\t\t\t      %s", categories[i]);
		printf("\n\t\t\t\t-----------------");
		for (int j = 0; j < shops_data[shopchoice - 1].total_dishes; j++)
		{
			if ((strcmp(categories[i], shops_data[shopchoice-1].dishes[j].dish_category) == 0) )
			{
				printf("\n\t\t         Dish ID: %d %s for Rs.%d \n", (j + 1), shops_data[shopchoice - 1].dishes[j].dish_name, shops_data[shopchoice - 1].dishes[j].price);
			}
		}
	}

	//asking for the choice of the user


	printf("\n\nPlease enter the id for the dish you want to order:  ");
	scanf_s("%d", &dishchoice);


	while (dishchoice != 0)
	{
		//keeps displaying menu and asking user's choice until "0" is entered


		system("cls");
		printf("\nOrder noted.\n\t\t\t          --------------\n"
			"\t\t\t\t   More from %s:", shops_data[shopchoice - 1].shop_name);
		printf("\n\t\t\t          --------------\n\n");


		//displaying menu


		for (int i = 0; i < 11; i++)
		{
			printf("\n\t\t\t\t      %s", categories[i]);
			printf("\n\t\t\t\t-----------------");
			for (int j = 0; j < shops_data[shopchoice - 1].total_dishes; j++)
			{
				if ((strcmp(categories[i], shops_data[shopchoice - 1].dishes[j].dish_category) == 0))
				{
					printf("\n\t\t         Dish ID: %d %s for Rs.%d \n", (j + 1), shops_data[shopchoice - 1].dishes[j].dish_name, shops_data[shopchoice - 1].dishes[j].price);
				}
			}
		}

		//updating the cart according to the choice of the user

		active_bill.cart[active_bill.cart_counter] = shops_data[shopchoice - 1].dishes[dishchoice - 1];
		active_bill.cart_counter++;
		active_bill.finalbill += shops_data[shopchoice - 1].dishes[dishchoice - 1].price;


		//asking for choice


		printf("\n(Remember press 0 to finish ordering)\n");
		printf("\nCurrent order has been noted. Would you like anything else: ",shops_data[shopchoice - 1].shop_name);
		scanf_s("%d", &dishchoice);

	}

	system("cls");


	//displaying cart

	printf("\nYour cart is: \n");
	for (i = 0; i < active_bill.cart_counter; i++)
	{
		printf("\n\"%s\" for   Rs.%d   from %s", active_bill.cart[i].dish_name, active_bill.cart[i].price, active_bill.cart[i].shop_name);
		printf("\n\t\t     +");

	}

	//displaying the bill


	printf("\n-------------------------------------------------------------");
	printf("\nTotal bill is :  Rs.%d\t  %s", active_bill.finalbill, ctime(&t));
	printf("-------------------------------------------------------------");


	//updating the user's last order

	strcpy(active_bill.time, ctime(&t));
	active_user.last_order = active_bill;
	user_data[active_user.user_number_in_data] = active_user;

	printf("\n\nPress any key to continue");
	getchar();
	getchar();

	//updating the shop summary file

	FILE* fileptr = { NULL };
	fileptr = fopen(active_bill.cart[0].shop_name, "a+");//opening file
	if (fileptr == NULL) {
		printf("\nError opening %s summary file", active_bill.cart[0].shop_name);
	}
	else
	{
		fprintf(fileptr,"\n Date: %s\n", ctime(&t));
		
		for (int i = 0; i < active_bill.cart_counter; i++)
		{

			fprintf(fileptr, "%s %s %d \n", active_bill.cart[i].dish_name, active_bill.cart[i].dish_category, active_bill.cart[i].price);
		}
		fprintf(fileptr, "%s\n",line);
		fclose(fileptr); //closing file
		fflush(fileptr);
	}
	printf("\n\n*******Thank you for choosing NUST FoodPanda. Do give us another visit.*******\n");

}

//THE END OF SEMESTER PROJECT

//	MAY THE FORCE BE WITH US

//	MAY THE ODDS BE ALWAYS IN OUR FAVOUR



