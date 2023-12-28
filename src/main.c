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

void display_greeting(struct User *user)
{
    char greet[255] = "Halo, ";
    strcat(greet, (*user).name);
    strcat(greet, "! Pilih menu sebagai ");
    strcat(greet, (*user).role);
    strcat(greet, " berikut");
    display_header(greet);
}

void display_user_main_menu(struct User *user)
{
    display_greeting(user);

    printf("1. Kirim Paket\n");
    printf("2. Lacak Paket\n");
    printf("3. Logout\n");

    printf("Masukkan pilihan: ");
}

void display_admin_main_menu(struct User *user)
{
    display_greeting(user);

    printf("1. Lihat Semua Paket\n");
    printf("2. Lihat Detail Paket\n");
    printf("3. Update Status Paket\n");
    printf("4. Logout\n");

    printf("Masukkan pilihan: ");
}

void user_main_menu(struct User *user,
                    struct DeliveryType *delivery_types, struct City *cities,
                    FILE *packages_table, struct Package *packages, int *current_package_row,
                    FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row)
{
    int answer;
    while (1)
    {
        display_user_main_menu(user);
        scanf("%i", &answer);

        switch (answer)
        {

        case 1:
            do_add_new_package(packages_table, packages, current_package_row,
                               package_statuses_table, package_statuses, current_package_status_row,
                               cities, delivery_types);
            break;

        case 2:
            do_track_package(
                packages, current_package_row,
                package_statuses, current_package_status_row);
            break;

        case 3:
            return;

        default:
            printf("Input tidak valid.\n");
            break;
        }
    }
}

void admin_main_menu(
    struct User *user, struct Package *packages, int *current_package_row,
    FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row)
{
    int answer;
    while (1)
    {
        display_admin_main_menu(user);
        scanf("%i", &answer);

        switch (answer)
        {
        case 1:
            do_display_packages_list(packages, current_package_row);
            break;

        case 2:
            do_display_package_detail(packages, current_package_row, package_statuses, current_package_status_row);
            break;

        case 4:
            return;

        default:
            printf("Input tidak valid.\n");
            break;
        }
    }
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

    // Start of Init Packages Table
    FILE *packages_table;
    open_database_table("packages", &packages_table);

    struct Package packages[MAX_PACKAGES];
    int current_package_row = 0;

    load_packages(packages_table, packages, &current_package_row);
    // End of Init Packages Table

    // Start of Init Package Statuses Table
    FILE *package_statuses_table;
    open_database_table("package_statuses", &package_statuses_table);

    struct PackageStatus package_statuses[MAX_PACKAGE_STATUSES];
    int current_package_status_row = 0;

    load_package_statuses(package_statuses_table, package_statuses, &current_package_status_row);
    // End of Init Package Statuses Table

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
            fclose(cities_table);
            fclose(packages_table);
            fclose(package_statuses_table);

            return 0;

        default:
            printf("Input tidak valid\n");

            fclose(users_table);
            fclose(delivery_types_table);
            fclose(cities_table);
            fclose(packages_table);
            fclose(package_statuses_table);

            return 0;
        }

        if (is_login_success)
        {
            int is_admin = strcmp(current_logged_in_user.role, "admin") == 0;
            if (is_admin)
            {
                admin_main_menu(&current_logged_in_user,
                                packages, &current_package_row,
                                package_statuses_table,
                                package_statuses,
                                &current_package_status_row);
            }
            else
            {
                user_main_menu(&current_logged_in_user, delivery_types,
                               cities, packages_table,
                               packages, &current_package_row,
                               package_statuses_table,
                               package_statuses,
                               &current_package_status_row);
            }

            // reset login state after main user session
            is_login_success = 0;
        }
    }

    fclose(users_table);
    fclose(delivery_types_table);
    fclose(cities_table);
    fclose(packages_table);
    fclose(package_statuses_table);

    return 0;
}