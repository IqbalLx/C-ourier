#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#define MAX_USERS 10
#define MAX_ITEMS 100

struct User
{
    int id;
    char name[255];
    char email[255];
    char password[255];
};

struct Item
{
    int id;
    char name[255];
    int price;
};

#endif