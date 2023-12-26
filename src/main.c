#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "auth.h"
#include "helper.h"

void display_header(char title[255])
{
    printf("\n");
    printf("====================================================\n");
    printf("%s\n", title);
    printf("====================================================\n");
}

void display_login()
{
    display_header("Selamat Datang Koperasi ITTS");

    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Keluar\n");

    printf("Masukkan pilihan: ");
}

int main()
{

    // Start of Init Users Table
    FILE *users_table;
    open_database_table("users", &users_table);

    struct User users[MAX_USERS];
    int current_user_row = 0;

    load_users(users_table, users, &current_user_row);
    // End of Init Users Table

    struct User current_logged_in_user;

    int answer;
    while (1)
    {
        display_login();
        scanf("%i", &answer);

        int is_login_success, is_register_success;
        switch (answer)
        {
        case 1:
            is_register_success = do_user_register(users_table, users, &current_user_row);
            if (is_register_success)
            {
                display_header("Selamat registrasi berhasil");
                break;
            }
            break;

        case 2:
            is_login_success = do_user_login(users, &current_user_row, &current_logged_in_user);
            if (is_login_success)
            {
                display_header("Selamat login berhasil");
                break;
            }
            break;

        case 3:
            fclose(users_table);
            return 0;

        default:
            printf("Input tidak valid\n");
            break;
        }

        if (is_login_success)
            break;
    }

    fclose(users_table);

    return 0;
}