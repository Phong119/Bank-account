#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <assert.h>
#include "user.c"
#define MAX_USERS 50
/* Allow user to enter username and password then add user,
   print USER SUCCESSFULLY ADDED if added successfully, USER ALREADY EXISTED if already existed 
   and USER ALREADY FULL if no more space for new user */
   USER user;
   void getPassword(char *password, int maxLength) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        // Enter to out
        if (ch == '\r') {
            break;
        }

        // Delete action
        if (ch == '\b' && i > 0) {
            printf("\b \b"); // Clear character
            i--;
            continue;
        }

        // Save and show "*"
        if (i < maxLength - 1) {
            password[i++] = ch;
            printf("*");
        }
    }

    password[i] = '\0'; // add the end character
}
void account(void)
{
    printf ("********WELCOME TO THE BANK***********");
    printf ("\n----------ENTER YOUR PERSONAL INFORMATION--------");
    printf ("\nEnter your first name: ");
    scanf ("%s",user.firstname);
    printf ("\nEnter your last name: ");
    scanf ("%s",user.lastname);
    printf("\nEnter your phone number: ");
    scanf("%s",user.phone);
    printf ("\nEnter your address: ");
    getchar();
    gets (user.address);
    printf ("\n****Day of birth****");
    printf ("\nEnter Day: ");
    scanf ("%d",&user.dob.day);
    printf ("\nEnter Month: ");
    scanf ("%d",&user.dob.month);
    printf ("\nEnter birth year: ");
    scanf ("%d",&user.dob.year);
    printf ("\nEnter the deposit:");
    scanf("%f",&user.amt);
    printf ("\nEnter the bank User Name:");
    scanf ("%s",user.username);
    printf ("\nEnter the PassWord:");
    getPassword(user.pwd,MAX_SIZE);
    ERROR_CODE status = addUser(&user);
    printf ("\n\n");
  if (status == USER_SUCCESSFULLY_ADDED) {
    printf("----USER SUCCESSFULLY ADDED!----\n");
  } else if (status == USER_ALREADY_EXISTED) {
    printf("----USER ALREADY EXISTED!----\n");
  } else {
    printf("----USER ADMINISTRATION FULL!----\n");
  }

  printf("\nPress Enter to continue...");
  getch();
 }

/* Allow user to enter username and password then authenticate user,
   print LOGIN SUCCESSFUL if login successfully, otherwise print LOGIN FAILED */
bool login(unsigned* userIdx)
{
    char check1 [MAX_SIZE];
    char check2 [MAX_SIZE];
    printf ("*******LOGIN TO BANK ACCOUNT!!!!*******");
    printf ("\nEnter the User Name:");
    scanf ("%s",check1);
    printf ("Enter the PassWord:");
    getPassword(check2,MAX_SIZE);
    bool state=authenticateUser(check1, check2, userIdx);
    printf("login %s\n", state?"success":"false");
    getch();
    return state;
}

/* Allow user to deposit or withdrawn money from his/her account */
void transaction(unsigned userIdx)
{   
    int input_draw;
    int input_deposit;
    int choice;
    do{
    printf ("Press 1 to Deposit:");
    printf ("\nPress 2 to withdraw:");
    printf ("\nPress 3 to back previous: \n");
    scanf ("%d",&choice);
    switch (choice)
    {
    case 1:
        printf ("Enter the amount of money you want deposit: ");
        scanf ("%d",&input_deposit);
        deposit(userIdx,input_deposit); 
        printf ("Deposit successful: %.2f",input_deposit);
        getch();
        break;
        case 2:
        printf ("Enter the amount of money you want withdraw: ");
        scanf ("%d",&input_draw);
        withdrawn(userIdx,input_draw); 
        printf ("\n Withdraw successfull!!!");
        printf ("\nTotal money left:%.2f",input_draw);
        getchar();
        break;
        case 3:
        break;
    default:
    system("CLS");
    printf ("Invalid choice!!!");}
        break;
    }while (choice !=3);
}

int main()
{
    int choice;
    bool auth = false;
    unsigned userIdx;
    
    while(1) {
        system("cls");
        printf("\nWELCOME TO BANK ACCOUNT SYSTEM\n\n");
    
        printf("**********************************\n");
    
        if (!auth) {
            printf("1.CREATE A BANK ACCOUNT\n");
            printf("2.SIGN IN\n");
            printf("3.EXIT\n\n");
        }
        else
        {
            printf("1.DISPLAY INFORMATION\n");
            printf("2.DEPOSIT OR WITHDRAWN\n");
            printf("3.TRANSFER MONEY\n");
            printf("4.LOG OUT\n");
            printf("5.EXIT\n\n");
        }
    
        printf("\n\nENTER YOUR CHOICE..");
    
        scanf("%d", &choice);
 
        switch (choice) 
        {
            case 1:
                system("cls");
                if (auth) 
                {
                    display(userIdx);
                }
                else 
                {
                    account();
                }
                break;
        
            case 2:
                system("cls");
                if (!auth) 
                {
                    auth = login(&userIdx);
                }
                else 
                {
                    transaction(userIdx);
                }
                break;
        
            case 3:
                system("cls");
                if (auth)
                {
                    transfermoney(userIdx);
                }
                else
                {
                    exit(0);
                }
                break;

            case 4:
                if (auth)
                {
                    system("cls");
                    auth = false;
                }

            case 5:
                if (auth)
                {
                    exit(0);
                }

                getch();
        }
    }
  return 0;
}

