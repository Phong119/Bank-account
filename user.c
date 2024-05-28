#include "user.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <conio.h>

#define MAX_USERS 50
int count =0;
static USER userList[MAX_USERS];

/* Log error with the time, username and text message to a file */
static void logError(char* username, char* text)
{
FILE *INPUT;
  INPUT = fopen("logfile","a");
  if (INPUT == NULL) {
      perror("Failed to open logfile");
      return;
  }
  fseek(INPUT,0,EOF);

  time_t t; // time variable
  struct tm *tmp; // poiter to time type

  t = time(&t); // get the current time (s)
  tmp = localtime(&t); // Convert to day month time year

  fprintf(INPUT,"%s", asctime(tmp)); // asctime to covert time type to string
  fprintf(INPUT,"User: %s %s\n",username,text);
  fclose(INPUT);
}

/* Returns user index if user exists and -1 if not. */
static int getUserIdx(char* username)
{
  int index =-1; //false
  for (int i = 0; i < count; i++)
  {
    if (strcmp(username, userList[i].username) == 0)
    {
      return i;
    }
  }
  return index;
}

/* Allow user to deposit money from account to account */
void transfermoney(unsigned userIdx)
{
	  char receiver[MAX_SIZE];
    float transfer_money;
    int ID_receiver ;
    printf("*******Transfer Money System********");
    printf ("\n Enter the person you want you trasnfer:");
    scanf ("%s",&receiver);
    ID_receiver= getUserIdx(receiver);
    if (ID_receiver==-1){
      printf ("This person does not exist!!!");
      printf ("\n Press enter to continue: ");
      getchar();
    }
    printf ("Enter the amount of money: ");
    scanf ("%f",&transfer_money);
    getchar ();
    if (userList[userIdx].amt <transfer_money){
      printf ("The amount of money are not enough");
      printf ("\n Press enter to continue: ");
      getchar();
      return;
    }
    userList[userIdx].amt-= transfer_money;
    userList[ID_receiver].amt+= transfer_money;
    printf ("Transfer successfull!!!");
    getchar();
}

/* Allow user to deposit money */
bool deposit(unsigned userIdx, float amt)
{

	if(amt>=0){
   userList[userIdx].amt +=amt;

   return true;
   }
  return false;
}

/* Allow user to withdrawn money */
bool withdrawn(unsigned userIdx, float amt)
{
	if(amt>=0){
   userList[userIdx].amt -=amt;
   return true;
   


  }
  return false;
}

/* Display user information */
void display(unsigned userIdx)
{
	printf (" %s INFOMATION", userList[userIdx].username);
  printf ("\n---------------------------------------\n");
  printf ("First Name: %s",userList[userIdx].firstname);
  printf ("\nLast Name: %s",userList[userIdx].lastname);
  printf ("\nPhone number: %s",userList[userIdx].phone);
  printf ("\nAddress: %s",userList[userIdx].address);
  printf ("\nBirthday: %d %d %d",userList[userIdx].dob.day,userList[userIdx].dob.month,userList[userIdx].dob.year);
  printf ("\nDeposit:%f.2",userList[userIdx].amt);
  getch();
}

/* Returns true if the provided username and the provided password are correct for that user, 
   returns false otherwise. */
bool authenticateUser(char* username, char* pwd, unsigned* userIdx)
{
  bool status = false;
  for (int i = 0; i < count; i++)
  {
    if (strcmp(userList[i].username,username)==0)
    {
      if (strcmp(userList[i].pwd,pwd)==0)
      {
        *userIdx=i;
        return true;
      } 
    }
  }
  return false;
}

/* Returns true if user exists and false otherwise. */
static bool userExists(char* username)
{
  for (int i; i < count; i++)
  {
    if (strcmp(userList[i].username, username)==0)
    {
      return true;
    }
  }
return false;}


/* Adds a new user with the provided `username' and the provided password `pwd'
   Returns USER_SUCCESSFULLY_ADDED on success, USER_ALREADY_EXISTED
   in case provided username already exists and USER_ADMINISTRATION_FULL
   in case no more user can be added. */
ERROR_CODE addUser(USER *user)
{
 if (count == MAX_USERS){
  logError(user->username, "MAX LIMIT, FULL USER TO ADD");
  return USER_ADMINISTRATION_FULL;
 }
 if (userExists(user->username)){
  logError(user->username," THIS MEMBER WAS JOINED");
  return USER_ALREADY_EXISTED;
 }
 userList[count]=*user;
count++;
return USER_SUCCESSFULLY_ADDED;
}

