#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
//TURN OFF ANTIVIRUS BEFORE EXECUTING THE PROGRAM

//get total number of days for each month (not leap years)
const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//check if the year is leap year
int countLeapYears(int date[])
{
    int years = date[2];
 
    // Check if the current year needs to be considered for the count of leap years or not
    if (date[1] <= 2)
        years--;
 
    // An year is a leap year if it is a multiple of 4, multiple of 400 and not a multiple of 100.
    return years / 4 - years / 100 + years / 400;
}

int getDifference(int checkIn[], int checkOut[])
{
    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'checkIn'
 
    // initialize count using years and day
    long int n1 = checkIn[2] * 365 + checkIn[0];
 
    // Add days for months in given date
    for (int i = 0; i < checkIn[1] - 1; i++)
        n1 += monthDays[i];
 
    // Since every leap year is of 366 days, Add a day for every leap year
    n1 += countLeapYears(checkIn);
 
    // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'checkOut'
 
    long int n2 = checkOut[2] * 365 + checkOut[0];
    for (int i = 0; i < checkOut[1] - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(checkOut);
 
    // return difference between two counts
    return (n2 - n1);
}

struct Customer {
	int checkIn[3]; 	
	int checkOut[3];
	char fullName[50] , phone[13], roomNo[3], ic[13];
	int adult, children;
	double fee;
};

struct Room {
	char roomType[30], roomNo[3], ic[13];
	double price;	
};

int getData(FILE *getCustomer, struct Customer cust[], struct Room roomdata[][10])
{
	getCustomer = fopen("Customer list.txt", "a+");
	char line[150];
	char *token;
	int i = 0;
	while(!feof(getCustomer))
	{
		while(fgets(line, sizeof line, getCustomer) != NULL)
		{			
			token = strtok(line, ","); //split by delimeter ','
			strcpy(cust[i].ic, token);	
			fflush(stdin);				
			strcpy(cust[i].fullName, strtok(NULL,","));
			strcpy(cust[i].phone, strtok(NULL, ","));					
			cust[i].adult = atoi(strtok(NULL, ","));						
			cust[i].children = atoi(strtok(NULL,","));						
			cust[i].checkIn[0] = atoi(strtok(NULL, " ")); cust[i].checkIn[1] = atoi(strtok(NULL, " ")); cust[i].checkIn[2] = atoi(strtok(NULL, ","));
			cust[i].checkOut[0] = atoi(strtok(NULL, " ")); cust[i].checkOut[1] = atoi(strtok(NULL, " ")); cust[i].checkOut[2] = atoi(strtok(NULL, ","));			
			cust[i].fee = atof(strtok(NULL, ","));	
			strcpy(cust[i].roomNo, strtok(NULL,","));
			
			//convert char to int
			int number = cust[i].roomNo[1] - '0';
			number--;
			
			//copy ic according to room into struct room		
			if(cust[i].roomNo[0] == 'D')
				strcpy(roomdata[0][number].ic, cust[i].ic );				
			else if(cust[i].roomNo[0] == 'K')
				strcpy(roomdata[1][number].ic, cust[i].ic );
			else if(cust[i].roomNo[0] == 'S')
				strcpy(roomdata[2][number].ic, cust[i].ic );
			else if(cust[i].roomNo[0] == 'P')
				strcpy(roomdata[3][number].ic, cust[i].ic );
			else if(cust[i].roomNo[0] == 'T')
				strcpy(roomdata[4][number].ic, cust[i].ic );
			i++;
		}		
	}	
	fclose(getCustomer);
	return i;	
}

void trimLeading(char * str)
{
    int index, i, j;

    index = 0;

    /* Find last index of whitespace character */
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }


    if(index != 0)
    {
        /* Shift all trailing characters to its left */
        i = 0;
        while(str[i + index] != '\0')
        {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0'; // Make sure that string is NULL terminated
    }
}

void setRoom( struct Room roomData[][10] )
{
	//Deluxed Single
	for(int i = 0 ; i < 10 ; i++)
	{
		char no[3], code[3] = {'D'};
		memset(roomData[0][i].ic, '\0', sizeof roomData[0][i].ic);
		strcpy(roomData[0][i].roomType, "Deluxed Single Room");
		strcpy(roomData[0][i].roomNo, strcat(code, itoa((i+1),no,10))); // character + int -> string
		roomData[0][i].price = 80.00;		
	}
	
	//Kids Suite Single
	for(int i = 0 ; i < 10 ; i++)
	{
		char no[2], code[3] = {'K'};
		memset(roomData[1][i].ic, '\0', sizeof roomData[1][i].ic);
		strcpy(roomData[1][i].roomType, "Kids Suite Room");
		strcpy(roomData[1][i].roomNo, strcat(code, itoa((i+1), no, 10)));
		roomData[1][i].price = 519.00;
	}
	
	//Studio Suite Single
	for(int i = 0 ; i < 10 ; i++)
	{
		char no[2],code[3] = {'S'};
		memset(roomData[2][i].ic, '\0', sizeof roomData[2][i].ic);
		strcpy(roomData[2][i].roomType, "Studio Suite Room");
		strcpy(roomData[2][i].roomNo, strcat(code, itoa((i+1), no, 10)));
		roomData[2][i].price = 170.00;
	}
	
	//Premiere Suite Single
	for(int i = 0 ; i < 10 ; i++)
	{
		char no[2],code[3] = {'P'};
		memset(roomData[3][i].ic, '\0', sizeof roomData[3][i].ic);
		strcpy(roomData[3][i].roomType, "Premiere Suite Room");
		strcpy(roomData[3][i].roomNo, strcat(code, itoa((i+1), no, 10)));
		roomData[3][i].price = 341.00;
	}
	
	//Three- Bedroom Apartment
	for(int i = 0 ; i < 10 ; i++)
	{
		char no[2], code[3] = {'T'};
		memset(roomData[4][i].ic, '\0', sizeof roomData[4][i].ic);
		strcpy(roomData[4][i].roomType, "Three-Bedroom Apartment");
		strcpy(roomData[4][i].roomNo, strcat(code, itoa((i+1), no, 10)));
		roomData[4][i].price = 477.00;
	}
}

void mainMenu()
{
	printf("     ______                         ________\n");
	printf("    /  __  .                       /__   __/\n");
	printf("   /  /_/  / .__________________.    /  /  .__________.\n");
	printf("  /    __ '  |E ||N ||D ||A ||H |   /  /   |E ||C ||C |\n");
	printf(" /__/\\_\\     |__||__||__||__||__|  /__/    |__||__||__|\n\n");
	printf("                      H    O    T   E   L");
	
}

void login()
{
	mainMenu();
	char u[13], pw[15], username[13], password[15],line[50];
	char *token;
	FILE * credential = fopen("login_credential.txt","r");
	printf("\n========================================================= \n");
	printf("                         L O G I N\n");
	printf("\n========================================================= \n\n");
	printf("\t\t Username = ");
	scanf("%s", &username);
	printf("\t\t Password = ");
	scanf("%s", &password);
	
	while(!feof(credential))
	{
		while(fgets(line, sizeof line, credential) != NULL)
		{
			
			token = strtok(line, ","); //split by delimeter ','
			for(int i = 0 ; i < 2 ; i++)
			{
				if(i == 0) //ic
				{					
					strcpy(u, token);
					token = strtok(NULL, ",");
					
				}
				else //password
				{
					strcpy(pw, token);
				
				}
					
			}
			if((strcmp(username,u) == 0) && (strcmp(password, pw) == 0))
			{
				system("cls");	
				printf("\n\n\n\t\t\t Login success!\n\n\n");
				system("pause");				
			}
			else
			{
				printf("\n\n\t\t Wrong credential!\n\n");
				system("pause");
				system("cls");
				login(); //recursive
			}
								
		}			
	}
	fclose(credential);	
}

int admin()
{	
	int c;
	do{
		
		printf("\n========================================================= \n");
		printf("\t\t [ Searching option ] \n");
		printf("\t\t [1] - Display Customer \n");
		printf("\t\t [2] - Display Room \n");
		printf("\t\t [3] - E-Report \n");
		printf("\t\t [4] - Customer List \n");
		printf("\t\t [5] Exit \n\n");
		printf("\t\t Enter your choice\n");
		printf("\n========================================================= \n\n");
		printf("\t\t\t\t");
		printf(" = ");
		scanf("%d", &c);
	}
	 while (c < 1 || c > 5);
	return c;
}

int access()
{
	int choice;
	do
	{
		printf("\t\t  .-----------.       .-----.______\n");
		printf("\t\t /| MAINDESK  |       |RECORD      |\n");
		printf("\t\t|-'           |       |   _________|_\n");
		printf("\t\t|  ~~~~~~~~~~ |       |  /           /\n");
		printf("\t\t|  ~~~~~~~~~~ |       | /           /\n");
		printf("\t\t|  ~~~~~~~~~~ |       |/___________/\n");
		printf("\t\t|  ~~~~~~~~~~ |\n");
		printf("\t\t'-------------'\n\n");
		printf("\t\t\tMAINDESK                 RECORD\n");
		printf("\t\t\t  [1]                      [2]\n\n");
		printf("                                                 [3] EXIT \n");
		printf("\t\t\t\t = ");
		scanf("%d", &choice);
		
	} while (choice < 1 || choice > 3);
	return choice;
}

int sort(const void *x, const void *y)
{
	struct Customer *cust1 = (struct Customer *)x;
	struct Customer *cust2 = (struct Customer *)y;	 	
 
 	return ( cust1->fullName - cust2->fullName);	//sort from z - a, return -1
}

void displaySort(struct Customer cust[], struct Room roomData[][10], int count)
{
	system("cls");
	mainMenu();
	qsort(cust, count, sizeof(struct Customer), sort); //do sorting from z-a	
	printf("\n\n========================================================= \n\n");
	printf("\t\t LIST OF CUSTOMER\n\n");
	int num = 1;
	for (int i = count-1 ; i >= 0 && (strcmp(cust[i].fullName, "\0") != 0); i--) //print inversely to get a-z
	{		
		printf("\t[%d]\t%s \t[%s]\n", num, cust[i].fullName, cust[i].ic);
		num++;
	}
	system("pause");
	
}

void displayCustomer (char name[], struct Customer cust[])
{
	system("cls");
	mainMenu();
	int i;
	bool found = false;
		
	i= 0 ;
	while (i < 50)
	{
		if( strcmp(cust[i].fullName, name) == 0)
		{
			printf("\n\n========================================================= \n\n");
			printf("\t\t Customer Detail  \n\n");
			printf("Fullname   \t\t: %s\n", cust[i].fullName);
			printf("IC Number   \t\t: %s\n", cust[i].ic);
			printf("Phone Number   \t\t: %s\n", cust[i].phone);
			printf("Room No   \t\t: %s\n", cust[i].roomNo);
			printf("Check-in date   \t: %d %d %d\n", cust[i].checkIn[0], cust[i].checkIn[1], cust[i].checkIn[2]);
			printf("Check-out date   \t: %d %d %d\n", cust[i].checkOut[0], cust[i].checkOut[1], cust[i].checkOut[2]);
			printf("Number of adult   \t: %d\n", cust[i].adult);
			printf("Number of children   \t: %d\n", cust[i].children);
			printf("Total fee   \t\t: RM %.2lf\n\n", cust[i].fee);
			found = true;
			system("pause");				
			break;
		}
		i++;
	}				
	
	if(!found)
	{
		char newName[50];
		system("cls");
		mainMenu();
		printf("\n\n\t\t Name not found\n\n");
		printf("\t\t Please enter the correct full name !\n");
		printf("========================================================= \n\n");
		printf("\t\t Name : ");
		fflush(stdin);			
    	fgets(newName, sizeof(newName), stdin);
    	//clear all \n in the string
		int len = strlen(newName);
		if( newName[len-1] == '\n' )
    		newName[len-1] = '\0';
		displayCustomer(newName, cust);    		
	}	
}

void displayRoom (int room, struct Customer custData[], struct Room roomData[][10])
{
	system("cls");
	mainMenu();
	printf("\n\n========================================================= \n\n");
	int cust = 0;
	
		if( room == 1 )
			printf("\t\t\tDeluxed Single\n\n");
		else if ( room == 2 )
			printf("\t\t\tKids Suite \n\n");
		else if ( room == 3 )
			printf("\t\t\tStudio Suite \n\n");
		else if ( room == 4 )
			printf("\t\t\tPremiere Suite \n\n");
		else if ( room == 5 )
			printf("\t\t\tThree-Bedroom Apartment \n\n");
			
		for ( int j = 0 ; j < 10 ; j++ )
		{
			if( strcmp(roomData[room-1][j].ic, "\0") != 0 ) //Room is vacant
			{
				printf("\t\t%s\t- ", roomData[room-1][j].roomNo);
				for ( int cust = 0 ; cust < 50 ; cust++)
				{
					if( strcmp(custData[cust].roomNo, roomData[room-1][j].roomNo) == 0 )
					{
						printf("%s [ %s ]\n", custData[cust].fullName, custData[cust].phone);
					}
				}
			}
			else
				printf("\t\t%s\t- Available\n", roomData[room-1][j].roomNo);
		}
	
	printf("\n");
	system("pause");
}

int mainDesk()
{
	int c;
	do{
		
		printf("\n========================================================= \n");
		printf("\t\t [ Record option ] \n");
		printf("\t\t [1] - Add Customer \n");
		printf("\t\t [2] - Update Record \n");
		printf("\t\t [3] - Exit \n\n");
		printf("\t\t Enter your choice\n");
		printf("\n========================================================= \n\n");
		printf("\t\t\t");
		printf(" = ");
		scanf("%d", &c);
	}
	 while (c < 1 || c > 3);
	return c;
}

void roomMenu()
{
	printf("\n==================================================================================== \n\n");
	printf("[1] Deluxed Single Room            [2] Kids Suite Room \n");
	printf("\t 1 Single bed                    \t 1 Double bed 1 Bunk bed\n");
	printf("\t 1 Adult 1 Children              \t 4 Adults 3 Children\n");
	printf("\t RM 80.00                        \t RM 519.00\n\n");
	printf("[3] Studio Suite Room              [4] Premiere Suite Room \n");
	printf("\t 2 Single beds                   \t 1 Extra-Large Double beds\n");
	printf("\t 2 Adult 2 children              \t 2 Adult 2 children\n");
	printf("\t RM 170.00                       \t RM 341.00\n\n");
	printf("\t\t[5] Three- Bedroom Apartment \n");
	printf("\t\t\t Bedroom 1 - 1 Extra-Large Double beds\n");
	printf("\t\t\t Bedroom 2 - 2 Single beds\n");
	printf("\t\t\t Living room - 1 Sofa bed\n");
	printf("\t\t\t 7 Adult + 3 Children\n");
	printf("\t\t\t RM 477.00\n\n");
	printf("\n==================================================================================== \n\n");
}

bool availableRoom(int type, struct Room roomData[][10])
{
	bool avail = false; 
	for ( int c = 0 ; c < 10 ; c++)
	{
		if(strcmp(roomData[type-1][c].ic, "\0") == 0) // available
		{
			avail = true; //return 0
		}		
	}
	return avail;
}

double pricey (int day , double price)
{
	return price*day;
}

double gst(double price)
{
	double tax = 0.06*price;
	return tax;
}

double companytax(double price)
{
	double tax = 0.1*price;
	return tax;
}

void displayReceipt(struct Customer cust[], struct Room roomdata[][10], int t, int r , int i, int day)
{
	mainMenu();
	double price = pricey(day , roomdata[t-1][r-1].price);
	double tax = gst(price);
	double total = tax + price ;
	printf("\n\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	printf("\t\t\t   RECEIPT\n");
	printf("\t\t\t CUSTOMER COPY\n\n");
	printf("NAME\t\t: %s\n", cust[i].fullName);
	printf("IC NUMBER\t: %s\n", cust[i].ic);
	printf("PHONE NUMBER\t: %s\n", cust[i].phone);
	printf("ROOM NUMBER\t: %s\n", cust[i].roomNo);
	printf("TYPE OF ROOM\t: %s\n", roomdata[t-1][r-1].roomType);
	printf("CHECK IN DATE\t: %d %d %d\n", cust[i].checkIn[0],cust[i].checkIn[1], cust[i].checkIn[2]);
	printf("CHECK OUT DATE\t: %d %d %d\n", cust[i].checkOut[0], cust[i].checkOut[1], cust[i].checkOut[2]);
	printf("NUMBER OF DAY(S): %d\n", day);
	printf("NO. OF ADULT\t: %d\n", cust[i].adult);
	printf("NO. OF CHILDREN : %d\n", cust[i].children);
	printf("PRICE\t\t: RM %.2lf\n", price);
	printf("TAX (6%c GST)\t: RM %.2lf\n", '%', tax);
	printf("TOTAL PRICE\t: RM %.2lf\n\n", total);
	printf("\tData have been successfully accepted. Enjoy your stay.");
	printf("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
}

void receipt(struct Customer cust[], struct Room roomdata[][10], int t, int r , int i, int day)
{
	char filename[100] = "[Receipt] ";	
	strcat(filename, cust[i].fullName);
	strcat(filename,".txt");
	FILE * receipt = fopen(filename, "w+");
	double price = pricey(day , roomdata[t-1][r-1].price);
	double tax = gst(price);
	double total = tax + price ;
	fprintf(receipt, "%s", "     ______                         ________\n");
	fprintf(receipt, "%s", "    /  __  .                       /__   __/\n");
	fprintf(receipt, "%s", "   /  /_/  / .__________________.    /  /  .__________.\n");
	fprintf(receipt, "%s", "  /    __ '  |E ||N ||D ||A ||H |   /  /   |E ||C ||C |\n");
	fprintf(receipt, "%s", " /__/\\_\\     |__||__||__||__||__|  /__/    |__||__||__|\n\n");
	fprintf(receipt, "%s", "                      H    O    T   E   L");
	fprintf(receipt, "%s", "\n\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	fprintf(receipt, "%s", "\t\t\t   RECEIPT\n");
	fprintf(receipt, "%s", "\t\t\t CUSTOMER COPY\n\n");
	fprintf(receipt, "%s", "NAME\t\t: ");
	fprintf(receipt, "%s\n", cust[i].fullName);
	fprintf(receipt, "%s", "IC NUMBER\t: ");
	fprintf(receipt, "%s\n", cust[i].ic);
	fprintf(receipt, "%s", "PHONE NUMBER\t: ");
	fprintf(receipt, "%s\n", cust[i].phone);
	fprintf(receipt, "%s", "ROOM NUMBER\t: ");
	fprintf(receipt, "%s\n", cust[i].roomNo);
	fprintf(receipt, "%s", "TYPE OF ROOM\t: ");
	fprintf(receipt, "%s\n", roomdata[t-1][r-1].roomType);
	fprintf(receipt, "%s", "CHECK IN DATE\t: ");
	fprintf(receipt, "%d %d %d\n", cust[i].checkIn[0],cust[i].checkIn[1], cust[i].checkIn[2]);
	fprintf(receipt, "%s", "CHECK OUT DATE\t: ");
	fprintf(receipt, "%d %d %d\n", cust[i].checkOut[0], cust[i].checkOut[1], cust[i].checkOut[2]);
	fprintf(receipt, "%s", "NUMBER OF DAY(S): ");
	fprintf(receipt, "%d ", day);
	fprintf(receipt, "%s\n", "days(s)");
	fprintf(receipt, "%s", "NO. OF ADULT\t: ");
	fprintf(receipt, "%d\n", cust[i].adult);
	fprintf(receipt, "%s", "NO. OF CHILDREN : ");
	fprintf(receipt, "%d\n", cust[i].children);
	fprintf(receipt, "%s", "PRICE\t\t: RM ");
	fprintf(receipt, "%.2lf\n", price);
	fprintf(receipt, "%s", "TAX (6% GST)\t: RM " );
	fprintf(receipt, "%.2lf\n", tax);
	fprintf(receipt, "%s", "TOTAL PRICE\t: RM ");
	fprintf(receipt, "%.2lf\n\n", cust[i].fee);
	fprintf(receipt, "%s", "\t\t    ENJOY YOUR STAY !");
	fprintf(receipt, "%s", "\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	fclose(receipt);	
}

void addCustomer (FILE *addCustomer, struct Customer cust[], struct Room roomdata[][10], int count)
{
	addCustomer = fopen("Customer list.txt", "a+");	
	int in[3], out[3];
	char name[50] = "\0", phone[13], ic[13];
	memset(name, '\0', sizeof(name));
	int adult , child, type, day;
	bool a = false, b = false, avail = false;
	do
	{
		roomMenu();
		printf("\t\t [ Fill in the form ] ");
		printf(" Room type : ");
		scanf("%d", &type);	
		avail = availableRoom(type, roomdata);	// check room availability
		if(avail) //if room available (return true)
		{	
			printf("\n\n\t\tRoom available. Please proceed to the form.\n\n");			
			printf("\t\t Check in date {dd mm yyy} :  ");
			scanf("%d", &in[0]); scanf("%d", &in[1]); scanf("%d", &in[2]);
			printf("\t\t Check out date {dd mm yyy} :  ");
			scanf("%d", &out[0]); scanf("%d", &out[1]); scanf("%d", &out[2]);
			day = getDifference(in, out) + 1 ; //get number of days including the day check-in
			printf("\t\t Number of day(s): %d day(s)\n", day);
			fflush(stdin); //to clear any leading wide space
			printf("\t\t Fullname : ");
			fgets(name, sizeof(name), stdin);
			//clear any \n in the string
			size_t length = strlen(name);
			if (name[length-1] == '\n')
    			name[length-1] = '\0';
    		//toUppercase the string name
    		for (int u = 0; name[u]!='\0'; u++) 
			{
      			if(name[u] >= 'a' && name[u] <= 'z') 
				{
         			name[u] = name[u] -32;
      			}
   			}
			fflush(stdin);			
			printf("\t\t Phone Number : ");
			scanf("%s", &phone);
			fflush(stdin);
			printf("\t\t IC Number : ");
			scanf("%s", &ic);
			fflush(stdin);
			printf("\t\t No. of adult : ");
			scanf("%d", &adult);
			printf("\t\t No. of children : ");
			scanf("%d", &child);	
			printf("\n==================================================================================== \n\n");
			
			//input into room
			bool foundRoom = false;
			int room = 0;
			while(!foundRoom && room < 10)
			{
				if(strcmp(roomdata[type-1][room].ic, "\0") == 0) //room is not vacant
				{
					foundRoom = true;
					break;					
				}
				room++;
			}
			
			if(foundRoom) //if available, copy into struct
			{
				printf("\n\t\t\tAccepting your request.....\n");
				printf("\t\t\tAccepted\n\n");
				system("pause");
				//key in data
				double price = pricey(day , roomdata[type-1][room].price);
				double tax = gst(price);
				double total = tax + price ;
				strcpy(cust[count].fullName, name);
				strcpy(cust[count].phone, phone);
				strcpy(cust[count].ic, ic);
				strcpy(roomdata[type-1][room].ic, ic);
				cust[count].adult = adult;
				cust[count].children = child;
				cust[count].checkIn[0] = in[0]; cust[count].checkIn[1] = in[1]; cust[count].checkIn[2] = in[2]; 
				cust[count].checkOut[0] = out[0]; cust[count].checkOut[1] = out[1]; cust[count].checkOut[2] = out[2];				
				strcpy(cust[count].roomNo, roomdata[type-1][room].roomNo);
				cust[count].fee =  total;
								
				//keyin to text file but checkif there's any existence data, continue
				char data[200] = {'\0'};			
				if(count == 0)//if first data to be put in textfile
				{
					fprintf(addCustomer, "%s,", cust[count].ic);
				}					
				else
				{
					fprintf(addCustomer, "\n%s,", cust[count].ic);
				}	
				fflush(addCustomer);				
				fprintf(addCustomer, "%s,", name);
				fflush(addCustomer);
				fprintf(addCustomer, "%s,", phone);
				fflush(addCustomer);
				fprintf(addCustomer, "%d,", adult);
				fflush(addCustomer);
				fprintf(addCustomer, "%d,", child);
				fflush(addCustomer);
				fprintf(addCustomer, "%d %d %d,", in[0], in[1], in[2]);
				fflush(addCustomer);
				fprintf(addCustomer, "%d %d %d,", out[0], out[1], out[2]);
				fflush(addCustomer);
				fprintf(addCustomer, "%.2lf,",  cust[count].fee);
				fflush(addCustomer);	
				fprintf(addCustomer, "%s,", cust[count].roomNo);
				fflush(addCustomer);
				system("cls");
				displayReceipt(cust, roomdata, type, room , count, day);
				receipt(cust, roomdata, type, room , count, day);				
				system("pause");
						
				
			}
			else
			{
				printf("DATA TAK MASUK\n");
				system("pause");
			}		
		}
		else
		{
			printf("\n\t\tRoom Not Available!\n");
			system("pause");
		}
			
	}while (!avail);
	fclose(addCustomer);
}

void updateDate(char code[], FILE *updateCustomer, struct Customer cust[],struct Room roomData[][10])
{		
	FILE * updateCust;
	updateCustomer = fopen("Customer list.txt", "a+");
	updateCust = fopen("[UPDATED] Customer list.txt", "w+")	;
	char oldname[100] = "Customer list.txt";
	char newname[100] = "[UPDATED] Customer list.txt" ;
	system("cls");
	mainMenu();
	bool found = false;
	while(!found)
	{
		int i = 0;
		while (i < 5)// row
		{
			int j = 0;
			while ( j < 10)//column
			{
				if( strcmp(roomData[i][j].roomNo, code) == 0) //room no match
				{
					int c = 0; //count customer
					while ( c < 50 )
					{
						if ( strcmp(cust[c].ic , roomData[i][j].ic) == 0)//if found display data
						{
							int newDate[3] = {0};
							printf("\n\n========================================================= \n\n");
							printf("\t\t Customer Detail  \n\n");
							printf("Fullname   \t\t: %s\n", cust[c].fullName);
							printf("IC Number   \t\t: %s\n", cust[c].ic);
							printf("Phone Number   \t\t: %s\n", cust[c].phone);
							printf("Room No   \t\t: %s\n", cust[c].roomNo);
							printf("Check-in date   \t: %d %d %d\n", cust[c].checkIn[0], cust[c].checkIn[1], cust[c].checkIn[2]);
							printf("Check-out date   \t: %d %d %d\n", cust[c].checkOut[0], cust[c].checkOut[1], cust[c].checkOut[2]);
							printf("Number of adult   \t: %d\n", cust[c].adult);
							printf("Number of children   \t: %d\n", cust[c].children);
							printf("Total fee   \t\t: RM %.2lf\n\n\n", cust[c].fee);
							printf("New Check-out Date \t = ");
							scanf("%d %d %d", &newDate[0], &newDate[1], &newDate[2]);
							int day = getDifference(cust[c].checkOut, newDate); //get number of days exclude the old checkout day
							//Update in struct
							cust[c].checkOut[0] = newDate[0]; cust[c].checkOut[1] = newDate[1]; cust[c].checkOut[2] = newDate[2];
							
							printf("Total day(s) \t\t = %d\n", day);
							double pBefore = roomData[i][j].price*1.1;
							printf("New Price up 10%c \t = %.2lf\n", '%', pBefore);
							double pAfter = pBefore * day;
							double getTax = gst(pAfter);
							pAfter += gst(pAfter);
							printf("New Price (x days)  \t = %.2lf\n", pAfter);
							cust[c].fee += pAfter;
							
							printf("Total fee after charging = RM %.2lf\n\n\n", cust[c].fee);
							printf("\n\n\t\t\t UPDATING YOUR INFORMATION \n");
							char data[100], dataCopy[100], extra[100]; 
							char *token;							
							//Update in textfile
							while(!feof(updateCustomer))
							{	
								while(fgets(data, sizeof data, updateCustomer) != NULL)
								{
									strcpy(dataCopy, data);
									token = strtok(data, ",");									
									if(strcmp(cust[c].ic, token) == 0 ) //if its the updated data
									{
										printf("Total fee after charging = RM %.2lf\n\n\n", cust[c].fee);
										printf("\n\n\t\t\t UPDATING YOUR INFORMATION \n");
										fprintf(updateCust, "%s,", cust[c].ic);
										fprintf(updateCust, "%s,", cust[c].fullName);
										fprintf(updateCust, "%s,", cust[c].phone);
										fprintf(updateCust, "%d,", cust[c].adult);
										fprintf(updateCust, "%d,", cust[c].children);
										fprintf(updateCust, "%d %d %d,", cust[c].checkIn[0], cust[c].checkIn[1], cust[c].checkIn[2]);
										fprintf(updateCust, "%d %d %d,", newDate[0], newDate[1], newDate[2]);
										fprintf(updateCust, "%.2lf,", cust[c].fee);			
										fprintf(updateCust, "%s,\n", cust[c].roomNo);												
									}
									else
									{
											fprintf(updateCust,"%s",dataCopy);										
									}
								}
								fflush(updateCustomer);
								fflush(updateCust);
							}
							printf("\n\n\tAn extra charge (+10%c) will be charged for each day(s) extended.", '%');							
							printf("\n\n\tYour check-out have been extended. Enjoy your stay.\n\n");
							system("pause");
							found = true;
						}
						c++;	
					}
				}
				j++;
			}
			i++;
		}
		if(found)
			break;
	}
	fflush(updateCustomer); //empty buffer
	fflush(updateCust);
	fclose(updateCust);
	fclose(updateCustomer);	
	remove(oldname);
    rename(newname, oldname);	
}


void report(struct Customer custData[], struct Room roomData[][10])
{
	FILE * reporto = fopen("Report.txt", "w+");
	system("cls");
	mainMenu();	
	fprintf(reporto, "%s", "     ______                         ________\n");
	fprintf(reporto, "%s", "    /  __  .                       /__   __/\n");
	fprintf(reporto, "%s", "   /  /_/  / .__________________.    /  /  .__________.\n");
	fprintf(reporto, "%s", "  /    __ '  |E ||N ||D ||A ||H |   /  /   |E ||C ||C |\n");
	fprintf(reporto, "%s", " /__/\\_\\     |__||__||__||__||__|  /__/    |__||__||__|\n\n");
	fprintf(reporto, "%s", "                      H    O    T   E   L");
	printf("\n\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	printf("\t\t\t   REPORT \n\n");
	fprintf(reporto, "\n\n%s\n\n", "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+");
	fprintf(reporto, "\t\t\t%s\n\n", "   REPORT ");
	//total customer
	int count;
	double price, total = 0;
	printf("\t\t\tTOTAL CUSTOMER \n\n");
	fprintf(reporto, "\t\t\t%s\n\n", "TOTAL CUSTOMER ");
	for (int i = 0 ; i < 5 ; i++)
	{
		count = 0; price = 0;
		if( i == 0 )
		{
			printf("\t\tDeluxed Single = ");
			fprintf(reporto, "\t\t%s", "Deluxed Single = ");
		}			
		else if ( i == 1 )
		{
			printf("\t\tKids Suite = ");
			fprintf(reporto, "\t\t%s", "Kids Suite = ");
		}
			
		else if ( i == 2 )
		{
			printf("\t\tStudio Suite = ");
			fprintf(reporto, "\t\t%s", "Studio Suite = ");
		}			
		else if ( i == 3 )
		{
			printf("\t\tPremiere Suite = ");
			fprintf(reporto, "\t\t%s", "Premiere Suite = ");
		}			
		else if ( i == 4 )
		{
			printf("\t\tThree-Bedroom Apartment = ");
			fprintf(reporto, "\t\t%s", "Three-Bedroom Apartment = ");
		}			
			
		for ( int j = 0 ; j < 10 ; j++ )
		{
			if( strcmp(roomData[i][j].ic, "\0") != 0 ) //Room is vacant
			{
				count++;
				for ( int cust = 0 ; cust < 50 ; cust++)
				{
					if( strcmp(custData[cust].roomNo, roomData[i][j].roomNo) == 0 )
					{
						price += custData[cust].fee;
						total += price;
					}
				}
				 
			}
		}
		//print count for each type
		printf("%d customer(s)\n", count);
		printf("\t\t   Total sales = RM %.2lf\n\n", price);	
		fprintf(reporto, "%d ", count);	fprintf(reporto, "%s\n", "customer(s)");	
		fprintf(reporto, "\t\t%s", "   Total sales = RM ");
		fprintf(reporto, "%.2lf\n\n", price);	
	}
	printf("\n\t\tGrand Total sales = RM %.2lf\n", total);
	printf("\t\tCompany Tax (10%c) = RM %.2lf\n\n", '%', companytax(total));
	fprintf(reporto, "\n\t\t%s", "Grand Total sales = RM ");
	fprintf(reporto, "%.2lf\n", total);	
	fprintf(reporto, "\t\t%s", "Company Tax (10%) = RM ");
	fprintf(reporto, "%.2lf\n\n", companytax(total));	
	system("pause");
	fclose(reporto);
}

void deleteCustomer(char code[], FILE *deleteCustomer, struct Customer cust[],struct Room roomData[][10])
{
	deleteCustomer = fopen("Customer list.txt", "a+");	
	FILE * updateCust = fopen("[UPDATED] Customer list.txt", "w+");	
	system("cls");
	mainMenu();
	bool found = false;
	while(!found)
	{
		int i = 0;
		while (i < 5)// row
		{
			int j = 0;
			while ( j < 10)//column
			{
				if( strcmp(roomData[i][j].roomNo, code) == 0) //if roomNo match
				{
					int c = 0;
					while ( c < 50 )
					{
						if ( strcmp(cust[c].ic , roomData[i][j].ic) == 0 )//if found display data
						{
							char confirm;
							printf("\n\n========================================================= \n\n");
							printf("\t\t Customer Detail  \n\n");
							printf("Fullname   \t\t: %s\n", cust[c].fullName);
							printf("IC Number   \t\t: %s\n", cust[c].ic);
							printf("Phone Number   \t\t: %s\n", cust[c].phone);
							printf("Room No   \t\t: %s\n", cust[c].roomNo);
							printf("Check-in date   \t: %d %d %d\n", cust[c].checkIn[0], cust[c].checkIn[1], cust[c].checkIn[2]);
							printf("Check-out date   \t: %d %d %d\n", cust[c].checkOut[0], cust[c].checkOut[1], cust[c].checkOut[2]);
							printf("Number of adult   \t: %d\n", cust[c].adult);
							printf("Number of children   \t: %d\n", cust[c].children);
							printf("Total fee   \t\t: RM %.2lf\n\n\n", cust[c].fee);
							printf("Confirm Check-Out? [Y/N] = ");
							fflush(stdin);
							scanf("%c", &confirm);
							
							if(confirm == 'Y' || confirm == 'y')
							{
								char data[100], dataCopy[100], extra[100]; 
								char *token;							
								//Update in textfile
								while(!feof(deleteCustomer))
								{	
									while(fgets(data, sizeof data, deleteCustomer) != NULL)
									{
										strcpy(dataCopy, data);	
										token = strtok(data, ",");									
										if(strcmp(cust[c].ic, token) == 0 ) //if found to be deleted data, do nothing
										{
											printf("\n\n\t\t\t PROCESSING YOUR REQUEST \n");																							
										}
										else //print other data into textfile
										{
											fprintf(updateCust, "%s", dataCopy);											
										}
									}
								}
								printf("\n\n Thank you for your stay.\n\n");
								system("pause");								
							}
							else
							{
								printf("\n\n Processed cancel.\n\n");
								system("pause");	
							}
							found = true;
							break;
						}						
						c++;							
					}
					if (!found)
					{						
						printf("\n\n\t\tData Not Found!\n\n");
						system("pause");
					}
				}
				j++;
			}
			i++;
		}
	}
	fclose(updateCust);
	fclose(deleteCustomer);	
	remove("Customer list.txt");
	//replace textfile with the old one
    rename("[UPDATED] Customer list.txt", "Customer list.txt");		
}

int main() 
{	
	FILE * addCust;	
	struct Room roomData[5][10];
	struct Customer custData[50];
	for(int i = 0 ; i < 50 ; i++)
	{
		//define all value in string to NULL
		memset(custData[i].fullName, '\0', sizeof custData[i].fullName);
		memset(custData[i].ic, '\0', sizeof custData[i].ic);
		memset(custData[i].phone, '\0', sizeof custData[i].phone);
		memset(custData[i].roomNo, '\0', sizeof custData[i].roomNo);
		custData[i].adult = custData[i].children = 0;
		custData[i].fee = 0;
		custData[i].checkIn[0] = custData[i].checkIn[1] = custData[i].checkIn[2] = 0;
		custData[i].checkOut[0] = custData[i].checkOut[1] = custData[i].checkOut[2] = 0;
	}	
	setRoom(roomData);
	int countCust;		
	countCust = getData(addCust, custData, roomData);	
	login();
	int choice, c, m;
	do
	{		
		countCust = getData(addCust, custData, roomData);				
		system("cls");
		choice = access();
		if(choice == 1) //MainDesk
		{
			system("cls");
			mainMenu();			
			m = mainDesk();
			if(m == 1) //Add New Customer
			{				
				system("cls");
				mainMenu();	
				printf("%d\n", countCust);							
				addCustomer(addCust, custData, roomData, countCust);				
				countCust++;
			}
			else if (m == 2) //Update Record
			{				
				int up;	
				system("cls");
				mainMenu();
				printf("\n========================================================= \n");
				printf("\t\t [ Update option ]\n");
				printf("\t\t [1] Extend check-out\n ");
				printf("\t\t [2] Check-out\n\n ");
				printf("\t\t\t = ");
				scanf("%d", &up);
				char code[2];
				if( up == 1 ) //Update check out date
				{						
					printf("\n\n\t\t Enter room no :  ");
					fflush(stdin);
					scanf("%s", &code);
					updateDate(code, addCust, custData, roomData);
				}
				else if ( up == 2 ) //Delete data
				{					
					printf("\n\n\t\t Enter room no :  ");
					fflush(stdin);
					scanf("%s", &code);
					deleteCustomer(code, addCust, custData, roomData);
				}
			}
			else if (m == 3) //Exit
			{
				system("cls");				
				printf("\n\n\t\t\t Exiting Program\n\n");
			}
		}
		else if (choice == 2)
		{
			system("cls");
			c = admin();
			if(c == 1) //Find customer by Name
			{
				char name[50];
				system("cls");
				mainMenu();
				printf("\n========================================================= \n");
				printf("\t\t[ Searching option ]\n");
				printf("\t\t Enter customer's name : ");
				fflush(stdin);
				fgets(name, sizeof(name), stdin);
				//remove \n in the string
				int len = strlen(name);
				if( name[len-1] == '\n' )
    				name[len-1] = '\0';
    			//convert name toUpper string
    			for (int u = 0; name[u]!='\0'; u++) 
				{
      				if(name[u] >= 'a' && name[u] <= 'z') 
					{
         				name[u] = name[u] -32;
      				}
   				}
				displayCustomer(name, custData);
			}
			else if (c == 2)
			{
				int room;
				system("cls");
				mainMenu();
				printf("\n========================================================= \n");
				printf("\t\t[ Searching option ]\n\n");
				printf("\t\t[1] Deluxed Single\n");
				printf("\t\t[2] Kids Suite\n");
				printf("\t\t[3] Studio Suite\n");
				printf("\t\t[4] Premiere Suite\n");
				printf("\t\t[5] Three-Bedroom Apartment\n\n");
				printf("\t\t Enter room package = ");
				fflush(stdin);
				scanf("%d", &room);
				displayRoom(room, custData, roomData);
			}
			else if ( c == 3)
			{
				report(custData, roomData);
			}
			else if (c == 4)
			{
				displaySort(custData, roomData, countCust);
			}
						
		}
		else if(choice == 3)
		{
			system("cls");
			printf("\n\n\t\t Exiting Program\n\n");
		}
					
	}while(choice != 3);
	
	
	return 0;
}
