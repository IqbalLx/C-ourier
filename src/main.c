#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "auth.h"
#include "package.h"
#include "helper.h"

void display_ascii_title()
{
    printf("   _____       ____             _            \n");
    printf("  / ____|     / __ \\           (_)           \n");
    printf(" | |   ______| |  | |_   _ _ __ _  ___ _ __  \n");
    printf(" | |  |______| |  | | | | | '__| |/ _ \\ '__| \n");
    printf(" | |____     | |__| | |_| | |  | |  __/ |    \n");
    printf("  \\_____|     \\____/ \\__,_|_|  |_|\\___|_|    \n");
}

void display_header(char title[255])
{
    printf("\n");
    printf("====================================================\n");
    printf("\n%s\n\n", title);
    printf("====================================================\n");
}

void display_login()
{
    display_header("Selamat Datang di C-Ourier");

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

    // Start of Init Delivery Types Table
    FILE *delivery_types_table;
    open_database_table("delivery_types", &delivery_types_table);

    struct DeliveryType delivery_types[COUNT_DELIVERY_TYPES];
    load_delivery_types(delivery_types_table, delivery_types);
    // End of Init Delivery Types Table

    // Start of Init City Table
    FILE *cities_table;
    open_database_table("cities", &cities_table);

    struct City cities[COUNT_CITIES];
    load_cities(cities_table, cities);
    // End of Init City Table

    struct User current_logged_in_user;
    int answer;

    display_ascii_title();

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
            fclose(delivery_types_table);
            return 0;

        default:
            printf("Input tidak valid\n");

            fclose(users_table);
            fclose(delivery_types_table);
            return 0;
        }

        if (is_login_success)
            break;
    }

    fclose(users_table);
    fclose(delivery_types_table);

    return 0;
}