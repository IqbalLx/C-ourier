#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "migrator.h"
#include "helper.h"

// Generics
void create_table(struct Table table)
{
    char db_foldername[3] = "db";
    char *slash = decide_slash();
    char filepath[255] = ".";
    strcat(filepath, slash);
    strcat(filepath, db_foldername);
    strcat(filepath, slash);
    strcat(filepath, table.name);
    strcat(filepath, ".csv");

    FILE *file = fopen(filepath, "w");
    if (file == NULL)
    {
        printf("failed to create table %s\n", table.name);
        exit(1);
    }

    for (int i = 0; i < table.column_length; i++)
    {
        if (i < table.column_length - 1)
        {
            fprintf(file, "%s,", table.columns[i]);
        }
        else
        {
            fprintf(file, "%s", table.columns[i]);
        }
    }

    fclose(file);

    printf("table %s created successfully\n", table.name);
}

void drop_table(struct Table table)
{
    char filepath[255] = "./db/";
    strcat(filepath, table.name);
    strcat(filepath, ".csv");

    if (remove(filepath) == 0)
        printf("table %s drop successfully\n", table.name);
    else
        printf("unable to drop table %s\n", table.name);
}

// Users
void users_table(char mode)
{
    struct Table user_table =
        {
            .name = "users",
            .column_length = 5,
            .columns = {
                "id",
                "name",
                "email",
                "password",
                "role",
            },
        };

    if (mode == 'c')
        create_table(user_table);
    else
        drop_table(user_table);
}

// Packages
void packages_table(char mode)
{
    struct Table package_table =
        {
            .name = "packages",
            .column_length = 13,
            .columns = {
                "id",
                "name",
                "sender_name",
                "sender_city",
                "receiver_name",
                "receiver_city",
                "length",
                "width",
                "height",
                "weight",
                "delivery_type",
                "distance",
                "delivery_price",
                "tracking_number",
            },
        };

    if (mode == 'c')
        create_table(package_table);
    else
        drop_table(package_table);
}

void package_statuses_table(char mode)
{
    struct Table package_status_table =
        {
            .name = "package_statuses",
            .column_length = 4,
            .columns = {
                "id",
                "package_id",
                "status",
                "timestamp",
            },
        };

    if (mode == 'c')
        create_table(package_status_table);
    else
        drop_table(package_status_table);
}

// Delivery Types
void delivery_types_table(char mode)
{
    struct Table delivery_type =
        {
            .name = "delivery_types",
            .column_length = 8,
            .columns = {
                "id",
                "name",
                "distance_price",
                "weight_volume_price",
                "eta_hours",
                "max_distance",
                "max_volume",
                "max_weight",
            },
        };

    if (mode == 'c')
        create_table(delivery_type);
    else
        drop_table(delivery_type);
}

// Cities
void cities_table(char mode)
{
    struct Table cities_table =
        {
            .name = "cities",
            .column_length = 4,
            .columns = {
                "id",
                "name",
                "longitude",
                "latitude",
            },
        };

    if (mode == 'c')
        create_table(cities_table);
    else
        drop_table(cities_table);
}

void do_migrate_or_rollback(char mode)
{
    users_table(mode);
    packages_table(mode);
    package_statuses_table(mode);
    delivery_types_table(mode);
    cities_table(mode);
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Too many arguments supplied.\n");
        return 0;
    }

    if (argc < 2)
    {
        printf("No argument supplied.\n");
        return 0;
    }

    char mode = argv[1][0];
    if (mode != 'c' && mode != 'd')
    {
        printf("Invalid arguments. Only 'c' for create and 'd' for drop/delete\n");
        return 0;
    }

    if (mode == 'c')
        printf("Migrating ...\n");
    else if (mode == 'd')
        printf("Rollback ...\n");

    do_migrate_or_rollback(mode);

    if (mode == 'c')
        printf("Migration completed!\n");
    else if (mode == 'd')
        printf("Rollback completed!\n");

    return 0;
}