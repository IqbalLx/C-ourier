#include <stdio.h>

#include "helper.h"
#include "entity.h"

void seed_users()
{
    FILE *users_table;
    open_database_table("users", &users_table);

    int user_seed_length = 2;
    struct User user_seeds[2] =
        {
            {
                .id = 1,
                .name = "Admin C-ourier",
                .email = "admin@c-ourier.id",
                .password = "password",
                .role = "admin",
            },
            {
                .id = 2,
                .name = "Iqbal",
                .email = "iqbal@email.com",
                .password = "pass",
                .role = "user",
            },
        };

    for (int i = 0; i < user_seed_length; i++)
    {
        struct User user = user_seeds[i];
        fprintf(users_table, "\n%d,%s,%s,%s,%s", user.id, user.name, user.email, user.password, user.role);
    }

    fclose(users_table);
}

void seed_delivery_types()
{
    FILE *delivery_types_table;
    open_database_table("delivery_types", &delivery_types_table);

    int delivery_type_seed_length = 4;
    struct DeliveryType delivery_type_seeds[4] =
        {
            {
                .id = 1,
                .name = "Instant",
                .eta_hours = 4,
                .max_distance = 40,
                .max_volume = 500,
                .max_weight = 20,
                .distance_price = 2500,
                .weight_volume_price = 1000,
            },
            {
                .id = 2,
                .name = "Same Day",
                .eta_hours = 8,
                .max_distance = 40,
                .max_volume = 500,
                .max_weight = 20,
                .distance_price = 2000,
                .weight_volume_price = 800,
            },
            {
                .id = 3,
                .name = "Next Day",
                .eta_hours = 24,
                .max_distance = 200,
                .max_volume = 1000,
                .max_weight = 30,
                .distance_price = 1000,
                .weight_volume_price = 500,
            },
            {
                .id = 4,
                .name = "Regular",
                .eta_hours = 72,
                .max_distance = 500,
                .max_volume = 2000,
                .max_weight = 50,
                .distance_price = 500,
                .weight_volume_price = 300,
            },
        };

    for (int i = 0; i < delivery_type_seed_length; i++)
    {
        struct DeliveryType delivery_type = delivery_type_seeds[i];
        fprintf(delivery_types_table, "\n%d,%s,%d,%d,%d,%d,%d,%d", delivery_type.id, delivery_type.name, delivery_type.distance_price, delivery_type.weight_volume_price, delivery_type.eta_hours, delivery_type.max_distance, delivery_type.max_volume, delivery_type.max_weight);
    }

    fclose(delivery_types_table);
}

void seed_cities()
{
    FILE *cities_table;
    open_database_table("cities", &cities_table);

    int city_seed_length = 10;
    struct City cities[10] =
        {
            {
                .id = 1,
                .name = "Surabaya",
                .latitude = -7.250445,
                .longitude = 112.768845,
            },
            {
                .id = 2,
                .name = "Jakarta",
                .latitude = -6.200000,
                .longitude = 106.816666,
            },
            {
                .id = 3,
                .name = "Bandung",
                .latitude = -6.914744,
                .longitude = 107.609810,
            },
            {
                .id = 4,
                .name = "Jember",
                .latitude = -8.184486,
                .longitude = 113.668076,
            },
            {
                .id = 5,
                .name = "Semarang",
                .latitude = -6.966667,
                .longitude = 110.416664,
            },
            {
                .id = 6,
                .name = "Solo",
                .latitude = -7.566667,
                .longitude = 110.816667,
            },
            {
                .id = 7,
                .name = "Malang",
                .latitude = -7.983908,
                .longitude = 112.621391,
            },
            {
                .id = 8,
                .name = "Tanggerang",
                .latitude = -6.178306,
                .longitude = 106.631889,
            },
            {
                .id = 9,
                .name = "Yogyakarta",
                .latitude = -7.797068,
                .longitude = 110.370529,
            },
            {
                .id = 10,
                .name = "Bogor",
                .latitude = -6.595038,
                .longitude = 106.816635,
            },
        };

    for (int i = 0; i < city_seed_length; i++)
    {
        struct City city = cities[i];
        fprintf(cities_table, "\n%d,%s,%f,%f", city.id, city.name, city.longitude, city.latitude);
    }

    fclose(cities_table);
}

int main()
{
    seed_users();
    seed_delivery_types();
    seed_cities();

    return 0;
}