#ifndef PACKAGE_HEADER
#define PACKAGE_HEADER

// Data
void load_delivery_types(FILE *delivery_types_table, struct DeliveryType *delivery_types);
void load_cities(FILE *cities_table, struct City *cities);

// Core
void display_delivery_types(struct DeliveryType *delivery_types);
void diplay_cities(struct City *cities);

#endif