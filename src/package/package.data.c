#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "entity.h"
#include "helper.h"

void load_delivery_types(FILE *delivery_types_table, struct DeliveryType *delivery_types)
{
    char row[255];
    int row_index = 0;
    int delivery_type_index = 0;
    while (fgets(row, sizeof(row), delivery_types_table))
    {
        if (row_index == 0)
        {
            row_index++;
            continue;
        }

        char *value = strtok(row, ",");
        int col_index = 0;
        while (value != NULL)
        {
            switch (col_index)
            {
            case 0:
                delivery_types[delivery_type_index].id = atoi(value);
                break;

            case 1:
                strncpy(delivery_types[delivery_type_index].name, value, sizeof(delivery_types[delivery_type_index].name) - 1);
                delivery_types[delivery_type_index].name[sizeof(delivery_types[delivery_type_index].name) - 1] = '\0';
                break;

            case 2:
                delivery_types[delivery_type_index].distance_price = atoi(value);
                break;

            case 3:
                delivery_types[delivery_type_index].weight_volume_price = atoi(value);
                break;

            case 4:
                delivery_types[delivery_type_index].eta_hours = atoi(value);
                break;

            case 5:
                delivery_types[delivery_type_index].max_distance = atoi(value);
                break;

            case 6:
                delivery_types[delivery_type_index].max_volume = atoi(value);
                break;

            case 7:
                delivery_types[delivery_type_index].max_weight = atoi(value);
                break;
            }

            value = strtok(NULL, ",");
            col_index++;
        };

        delivery_type_index++;
        row_index++;
    }
}

void load_cities(FILE *cities_table, struct City *cities)
{
    char row[255];
    int row_index = 0;
    int city_index = 0;
    while (fgets(row, sizeof(row), cities_table))
    {
        if (row_index == 0)
        {
            row_index++;
            continue;
        }

        char *value = strtok(row, ",");
        int col_index = 0;
        while (value != NULL)
        {
            switch (col_index)
            {
            case 0:
                cities[city_index].id = atoi(value);
                break;

            case 1:
                strncpy(cities[city_index].name, value, sizeof(cities[city_index].name) - 1);
                cities[city_index].name[sizeof(cities[city_index].name) - 1] = '\0';
                break;

            case 2:
                cities[city_index].longitude = atof(value);
                break;

            case 3:
                cities[city_index].latitude = atof(value);
                break;
            }

            value = strtok(NULL, ",");
            col_index++;
        };

        city_index++;
        row_index++;
    }
}

void load_packages(FILE *packages_table, struct Package *packages, int *current_package_row)
{
    char row[255];
    int row_index = 0;
    while (fgets(row, sizeof(row), packages_table))
    {
        if (row_index == 0)
        {
            row_index++;
            continue;
        }

        char *value = strtok(row, ",");
        int col_index = 0;
        while (value != NULL)
        {
            switch (col_index)
            {
            case 0:
                packages[*current_package_row].id = atoi(value);
                break;

            case 1:
                strncpy(packages[*current_package_row].name, value, sizeof(packages[*current_package_row].name) - 1);
                packages[*current_package_row].name[sizeof(packages[*current_package_row].name) - 1] = '\0';
                break;

            case 2:
                strncpy(packages[*current_package_row].sender_name, value, sizeof(packages[*current_package_row].sender_name) - 1);
                packages[*current_package_row].sender_name[sizeof(packages[*current_package_row].sender_name) - 1] = '\0';
                break;

            case 3:
                strncpy(packages[*current_package_row].sender_city, value, sizeof(packages[*current_package_row].sender_city) - 1);
                packages[*current_package_row].sender_city[sizeof(packages[*current_package_row].sender_city) - 1] = '\0';
                break;

            case 4:
                strncpy(packages[*current_package_row].receiver_name, value, sizeof(packages[*current_package_row].receiver_name) - 1);
                packages[*current_package_row].receiver_name[sizeof(packages[*current_package_row].receiver_name) - 1] = '\0';
                break;

            case 5:
                strncpy(packages[*current_package_row].receiver_city, value, sizeof(packages[*current_package_row].receiver_city) - 1);
                packages[*current_package_row].receiver_city[sizeof(packages[*current_package_row].receiver_city) - 1] = '\0';
                break;

            case 6:
                packages[*current_package_row].length = atoi(value);
                break;

            case 7:
                packages[*current_package_row].width = atoi(value);
                break;

            case 8:
                packages[*current_package_row].height = atoi(value);
                break;

            case 9:
                packages[*current_package_row].weight = atoi(value);
                break;

            case 10:
                strncpy(packages[*current_package_row].delivery_type, value, sizeof(packages[*current_package_row].delivery_type) - 1);
                packages[*current_package_row].delivery_type[sizeof(packages[*current_package_row].delivery_type) - 1] = '\0';
                break;

            case 11:
                packages[*current_package_row].distance = atof(value);
                break;

            case 12:
                packages[*current_package_row].delivery_price = atoi(value);
                break;

            case 13:
                strncpy(packages[*current_package_row].tracking_number, value, sizeof(packages[*current_package_row].tracking_number) - 1);
                remove_new_line_char(&packages[*current_package_row].tracking_number);
                break;
            }

            value = strtok(NULL, ",");
            col_index++;
        };

        (*current_package_row)++;
        row_index++;
    }
}

void load_package_statuses(FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row)
{
    char row[255];
    int row_index = 0;
    while (fgets(row, sizeof(row), package_statuses_table))
    {
        if (row_index == 0)
        {
            row_index++;
            continue;
        }

        char *value = strtok(row, ",");
        int col_index = 0;
        while (value != NULL)
        {
            switch (col_index)
            {
            case 0:
                package_statuses[*current_package_status_row].id = atoi(value);
                break;

            case 1:
                package_statuses[*current_package_status_row].package_id = atoi(value);
                break;

            case 2:
                strncpy(package_statuses[*current_package_status_row].status, value, sizeof(package_statuses[*current_package_status_row].status) - 1);
                package_statuses[*current_package_status_row].status[sizeof(package_statuses[*current_package_status_row].status) - 1] = '\0';
                break;

            case 3:
                strncpy(package_statuses[*current_package_status_row].timestamp, value, sizeof(package_statuses[*current_package_status_row].timestamp) - 1);
                remove_new_line_char(&package_statuses[*current_package_status_row].timestamp);
                break;
            }

            value = strtok(NULL, ",");
            col_index++;
        };

        (*current_package_status_row)++;
        row_index++;
    }
}

void add_new_package(FILE *packages_table, struct Package *packages, int *current_package_row,
                     FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row,
                     struct Package package, struct PackageStatus package_status)
{
    // Update data in memory
    packages[*current_package_row] = package;
    package_statuses[*current_package_status_row] = package_status;

    // Persists both data
    fprintf(packages_table, "\n%d,%s,%s,%s,%s,%s,%d,%d,%d,%d,%s,%f,%d,%s",
            package.id, package.name, package.sender_name,
            package.sender_city, package.receiver_name, package.receiver_city,
            package.length, package.width, package.height, package.weight,
            package.delivery_type, package.distance, package.delivery_price,
            package.tracking_number);
    fprintf(package_statuses_table, "\n%d,%d,%s,%s", package_status.id, package_status.package_id,
            package_status.status, package_status.timestamp);

    (*current_package_row)++;
    (*current_package_status_row)++;
}

void add_new_package_status(
    FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row,
    struct PackageStatus package_status)
{
    package_statuses[*current_package_status_row] = package_status;
    fprintf(package_statuses_table, "\n%d,%d,%s,%s", package_status.id, package_status.package_id,
            package_status.status, package_status.timestamp);

    (*current_package_status_row)++;
}