#ifndef PACKAGE_HEADER
#define PACKAGE_HEADER

// Data
void load_delivery_types(FILE *delivery_types_table, struct DeliveryType *delivery_types);
void load_cities(FILE *cities_table, struct City *cities);
void load_packages(FILE *packages_table, struct Package *packages, int *current_package_row);
void load_package_statuses(FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row);

// Core
void display_delivery_types(struct DeliveryType *delivery_types);
void diplay_cities(struct City *cities);
void display_packages(struct Package *packages, int *current_package_row);
void display_package_statuses(struct PackageStatus *package_statuses, int *current_package_status_row);

#endif