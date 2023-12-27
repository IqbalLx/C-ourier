#include <stdio.h>
#include <math.h>
#include <string.h>

#include "entity.h"
#include "package.h"

void show_delivery_types(struct DisplayDeliveryType *display_delivery_types, int valid_delivery_type)
{
    for (int i = 0; i < valid_delivery_type; i++)
    {
        int curr_eta_hours = display_delivery_types[i].eta_hours;

        printf("%d. %s\n", i + 1, display_delivery_types[i].name);
        printf("Harga: Rp. %d\n", display_delivery_types[i].price);

        if (curr_eta_hours >= 24)
        {
            printf("Durasi Pengiriman: %d Hari\n", curr_eta_hours / 24);
        }
        else
        {
            printf("Durasi Pengiriman: %d Jam\n", curr_eta_hours);
        }
    }
}

void display_cities(struct City *cities)
{
    for (int i = 0; i < COUNT_CITIES; ++i)
    {
        printf("%d. %s\n", cities[i].id, cities[i].name);
    }
}

void display_packages(struct Package *packages, int *current_package_row)
{
    for (int i = 0; i < *current_package_row; ++i)
    {
        printf("Package ID: %d\n", packages[i].id);
        printf("Name: %s\n", packages[i].name);
        printf("Sender Name: %s\n", packages[i].sender_name);
        printf("Sender City: %s\n", packages[i].sender_city);
        printf("Receiver Name: %s\n", packages[i].receiver_name);
        printf("Receiver City: %s\n", packages[i].receiver_city);
        printf("Length: %d\n", packages[i].length);
        printf("Width: %d\n", packages[i].width);
        printf("Height: %d\n", packages[i].height);
        printf("Weight: %d\n", packages[i].weight);
        printf("Delivery Type: %s\n", packages[i].delivery_type);
        printf("Distance: %f\n", packages[i].distance);
        printf("Delivery Price: %d\n", packages[i].delivery_price);
        printf("Tracking Number: %s\n", packages[i].tracking_number);
        printf("\n");
    }
}

void display_package_statuses(struct PackageStatus *package_statuses, int *current_package_status_row)
{
    for (int i = 0; i < *current_package_status_row; ++i)
    {
        printf("Status ID: %d\n", package_statuses[i].id);
        printf("Package ID: %d\n", package_statuses[i].package_id);
        printf("Status: %s\n", package_statuses[i].status);
        printf("Timestamp: %s\n", package_statuses[i].timestamp);
        printf("\n");
    }
}

struct City select_city(struct City *cities)
{
    int city_id;
    while (1)
    {
        display_cities(cities);

        printf("\nMasukkan pilihan: ");
        scanf("%d", &city_id);

        if (city_id > COUNT_CITIES || city_id < 1)
        {
            printf("Pilihan tidak valid\n");
            continue;
        }

        return cities[city_id - 1];
    }
}

double degrees_to_radians(double degrees)
{
    return degrees * M_PI / 180.0;
}

double calc_distance(double lat1, double lon1, double lat2, double lon2)
{
    // Convert latitude and longitude from degrees to radians
    lat1 = degrees_to_radians(lat1);
    lon1 = degrees_to_radians(lon1);
    lat2 = degrees_to_radians(lat2);
    lon2 = degrees_to_radians(lon2);

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = EARTH_RADIUS * c;

    return distance;
}

int calc_volume(int length, int width, int height)
{
    return length * width * height;
}

int calc_price(struct DeliveryType delivery_type, int volume, int weight, double distance)
{
    int volume_in_m3 = ceil((float)volume / 1000);
    int weight_or_volume = weight;
    if (volume_in_m3 > weight)
        weight_or_volume = volume_in_m3;

    int weight_volume_price = weight_or_volume * delivery_type.weight_volume_price;
    int distance_price = ceil(distance * delivery_type.distance_price);

    return weight_volume_price + distance_price;
}

void swap_display_delivery_type(struct DisplayDeliveryType *x, struct DisplayDeliveryType *y)
{
    struct DisplayDeliveryType temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void bubble_sort_display_delivery_type_by_price(struct DisplayDeliveryType *arr, int is_ascending, int arr_length)
{
    for (int i = 0; i < arr_length - 1; i++)
    {
        for (int j = 0; j < arr_length - 1 - i; j++)
        {
            if (!is_ascending)
            {
                if (arr[j].price < arr[j + 1].price)
                {
                    swap_display_delivery_type(&arr[j], &arr[j + 1]);
                }
            }
            else
            {
                if (arr[j].price > arr[j + 1].price)
                {
                    swap_display_delivery_type(&arr[j], &arr[j + 1]);
                }
            }
        }
    }
}

void insertion_sort_display_delivery_type_by_eta(struct DisplayDeliveryType *arr, int is_ascending, int arr_length)
{
    int i, j;
    struct DisplayDeliveryType key;
    for (i = 1; i < arr_length; i++)
    {
        key = arr[i];
        j = i - 1;

        int condition;
        if (is_ascending)
        {
            condition = (j >= 0 && arr[j].eta_hours > key.eta_hours);
        }
        else
        {
            condition = (j >= 0 && arr[j].eta_hours < key.eta_hours);
        }
        while (condition)
        {
            arr[j + 1] = arr[j];
            j = j - 1;

            if (is_ascending)
            {
                condition = (j >= 0 && arr[j].eta_hours > key.eta_hours);
            }
            else
            {
                condition = (j >= 0 && arr[j].eta_hours < key.eta_hours);
            }
        }

        arr[j + 1] = key;
    }
}