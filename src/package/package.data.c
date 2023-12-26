#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "entity.h"

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