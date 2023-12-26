#include <stdio.h>

#include "entity.h"

void display_delivery_types(struct DeliveryType *delivery_types)
{
    for (int i = 0; i < COUNT_DELIVERY_TYPES; ++i)
    {
        printf("Delivery Type ID: %d\n", delivery_types[i].id);
        printf("Name: %s\n", delivery_types[i].name);
        printf("Distance Price: %d\n", delivery_types[i].distance_price);
        printf("Weight/Volume Price: %d\n", delivery_types[i].weight_volume_price);
        printf("ETA Hours: %d\n", delivery_types[i].eta_hours);
        printf("Max Distance: %d\n", delivery_types[i].max_distance);
        printf("Max Volume: %d\n", delivery_types[i].max_volume);
        printf("Max Weight: %d\n", delivery_types[i].max_weight);
        printf("\n");
    }
}

void diplay_cities(struct City *cities)
{
    for (int i = 0; i < COUNT_CITIES; ++i)
    {
        printf("City ID: %d\n", cities[i].id);
        printf("Name: %s\n", cities[i].name);
        printf("Longitude: %f\n", cities[i].longitude);
        printf("Latitude: %f\n", cities[i].latitude);
        printf("\n");
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