#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#define MAX_USERS 10
#define MAX_PACKAGES 100
#define MAX_PACKAGE_STATUSES 500
#define COUNT_DELIVERY_TYPES 4
#define COUNT_CITIES 10

struct User
{
    int id;
    char name[255];
    char email[255];
    char password[255];
    char role[255];
};

struct Package
{
    int id;
    char name[255];
    char sender_name[255];
    char sender_city[255];
    char receiver_name[255];
    char receiver_city[255];
    int length;
    int width;
    int height;
    int weight;
    char delivery_type[255];
    double distance;
    int delivery_price;
    char tracking_number[255];
};

struct PackageStatus
{
    int id;
    int package_id;
    char status[255];
    char timestamp[255];
};

struct DeliveryType
{
    int id;
    char name[255];
    int distance_price;
    int weight_volume_price;
    int eta_hours;
    int max_distance;
    int max_volume;
    int max_weight;
};

struct City
{
    int id;
    char name[255];
    double longitude;
    double latitude;
};

#endif