#ifndef USER_H
#define USER_H

#include <stdbool.h>

#define MAX_SIZE 50

typedef enum{
  USER_SUCCESSFULLY_ADDED,
  USER_ALREADY_EXISTED,
  USER_ADMINISTRATION_FULL
} ERROR_CODE;

struct date
{
  int month, day, year;
};

typedef struct
{
  char username[MAX_SIZE];
  char pwd[MAX_SIZE];
  char address[MAX_SIZE];
  char phone[MAX_SIZE];
  char firstname[MAX_SIZE];
  char lastname[MAX_SIZE];
  float amt;
  struct date dob;
  struct date deposit;
  struct date withdraw;
} USER;

void transfermoney(unsigned userIdx);

bool deposit(unsigned userIdx, float amt);

bool withdrawn(unsigned userIdx, float amt);

void display(unsigned userIdx);

bool authenticateUser(char* username, char* pwd, unsigned* userIdx);

ERROR_CODE addUser(USER *user);

#endif

