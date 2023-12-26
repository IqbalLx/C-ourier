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