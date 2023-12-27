#ifndef PACKAGE_HEADER
#define PACKAGE_HEADER

#define EARTH_RADIUS 6371 // Earth's radius in kilometers

// Struct
struct DisplayDeliveryType
{
    char name[255];
    int eta_hours;
    int price;
};

// Data
void load_delivery_types(FILE *delivery_types_table, struct DeliveryType *delivery_types);
void load_cities(FILE *cities_table, struct City *cities);
void load_packages(FILE *packages_table, struct Package *packages, int *current_package_row);
void load_package_statuses(FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row);
void add_new_package(FILE *packages_table, struct Package *packages, int *current_package_row,
                     FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row,
                     struct Package package, struct PackageStatus package_status);

// Core
void show_delivery_types(struct DisplayDeliveryType *display_delivery_types, int valid_delivery_type);
void display_cities(struct City *cities);
void display_packages(struct Package *packages, int *current_package_row);
void display_package_statuses(struct PackageStatus *package_statuses, int *current_package_status_row);
struct City select_city(struct City *cities);
double degrees_to_radians(double degrees);
double calc_distance(double lat1, double lon1, double lat2, double lon2);
int calc_volume(int length, int width, int height);
int calc_price(struct DeliveryType delivery_type, int volume, int weight, double distance);
void swap_display_delivery_type(struct DisplayDeliveryType *x, struct DisplayDeliveryType *y);
void bubble_sort_display_delivery_type_by_price(struct DisplayDeliveryType *arr, int is_ascending, int arr_length);
void insertion_sort_display_delivery_type_by_eta(struct DisplayDeliveryType *arr, int is_ascending, int arr_length);

// Service
struct DisplayDeliveryType select_delivery_type(struct DeliveryType *delivery_types, int volume, int weight, double distance);
void do_add_new_package(FILE *packages_table, struct Package *packages, int *current_package_row,
                        FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row,
                        struct City *cities, struct DeliveryType *delivery_types);

#endif