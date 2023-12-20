#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "auth.h"

int do_user_register(FILE *users_table, struct Item *users, int *current_user_row)
{
    if (*current_user_row == (MAX_USERS - 1))
    {
        printf("Tidak bisa menambah user lagi\n");
        return 0;
    }

    char email[255];
    printf("Masukkan email: ");
    scanf("%s", &email);

    int is_email_exists = check_email_exists(users, current_user_row, email);
    if (is_email_exists)
    {
        printf("Email %s sudah terdaftar", email);
        return 0;
    }

    add_user(users_table, users, current_user_row, email);

    return 1;
}

int do_user_login(struct User *users, int *current_user_row, struct User *current_logged_in_user)
{
    char email[255], password[255];
    printf("Masukkan email: ");
    scanf("%s", &email);

    int is_email_exists = check_email_exists(users, current_user_row, email);
    if (!is_email_exists)
    {
        printf("Email %s tidak terdaftar", email);
        return 0;
    }

    struct User user;
    get_user(&user, users, current_user_row, email);

    printf("Masukkan password: ");
    scanf("%s", &password);

    int is_password_match = strcmp(user.password, password) == 0;
    if (!is_password_match)
    {
        printf("Password salah");
        return 0;
    }

    *current_logged_in_user = user;

    return 1;
}
