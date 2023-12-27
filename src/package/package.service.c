#include <stdio.h>
#include <string.h>

#include "entity.h"
#include "package.h"
#include "helper.h"

struct DisplayDeliveryType select_delivery_type(struct DeliveryType *delivery_types, int volume, int weight, double distance)
{
    // Filter eligible delivery type first
    int count_valid_delivery_type = 0;
    struct DisplayDeliveryType display_delivery_types[COUNT_DELIVERY_TYPES];

    for (int i = 0; i < COUNT_DELIVERY_TYPES; i++)
    {
        struct DeliveryType curr_delivery_type = delivery_types[i];
        if (
            distance <= curr_delivery_type.max_distance &&
            volume <= curr_delivery_type.max_volume &&
            weight <= curr_delivery_type.max_weight)
        {
            struct DisplayDeliveryType display_delivery_type;

            strncpy(display_delivery_type.name, curr_delivery_type.name, sizeof(curr_delivery_type.name));
            display_delivery_type.name[sizeof(curr_delivery_type.name) - 1] = '\0';

            display_delivery_type.eta_hours = curr_delivery_type.eta_hours;

            display_delivery_type.price = calc_price(curr_delivery_type, volume, weight, distance);

            display_delivery_types[count_valid_delivery_type] = display_delivery_type;

            count_valid_delivery_type++;
        }
    }

    // Then display and ask user input
    int selected_id, answer;
    while (1)
    {
        printf("Pilihan jenis pengiriman yang tersedia: \n\n");
        show_delivery_types(display_delivery_types, count_valid_delivery_type);
        printf("\n\n");

        printf("1. Pilih jenis pengiriman\n");
        printf("2. Urutkan termurah\n");
        printf("3. Urutkan termahal\n");
        printf("4. Urutkan tercepat\n");
        printf("5. Urutkan terlama\n");

        printf("Masukkan pilihan: ");
        scanf("%d", &answer);

        switch (answer)
        {
        case 1:
            printf("Masukkan pilihan jenis pengiriman: ");
            scanf("%d", &selected_id);

            if (selected_id < 1 && selected_id > count_valid_delivery_type)
            {
                printf("Pilihan tidak valid\n");
                break;
            }

            return display_delivery_types[selected_id - 1];

        case 2:
            bubble_sort_display_delivery_type_by_price(display_delivery_types, 1, count_valid_delivery_type);
            break;

        case 3:
            bubble_sort_display_delivery_type_by_price(display_delivery_types, 0, count_valid_delivery_type);
            break;

        case 4:
            insertion_sort_display_delivery_type_by_eta(display_delivery_types, 1, count_valid_delivery_type);
            break;

        case 5:
            insertion_sort_display_delivery_type_by_eta(display_delivery_types, 0, count_valid_delivery_type);
            break;

        default:
            printf("Pilihan tidak valid\n");
            continue;
        }
    }
}

void do_add_new_package(FILE *packages_table, struct Package *packages, int *current_package_row,
                        FILE *package_statuses_table, struct PackageStatus *package_statuses, int *current_package_status_row,
                        struct City *cities, struct DeliveryType *delivery_types)
{
    if (*current_package_row == (MAX_PACKAGES - 1) ||
        *current_package_status_row == (MAX_PACKAGE_STATUSES - 1))
    {
        printf("Tidak bisa mengirim paket lagi\n");
        return;
    }

    struct Package this_package;
    this_package.id = (*current_package_row) + 1;
    generate_random_string(this_package.tracking_number);

    struct City orig_city, dest_city;
    int volume;
    double distance;
    struct DisplayDeliveryType delivery_type;

    // Construct Package
    printf("Masukkan nama paket: ");
    scanf("%s", &this_package.name);

    printf("Masukkan nama pengirim: ");
    scanf("%s", &this_package.sender_name);

    printf("Pilih kota asal dari pilihan berikut\n\n");
    orig_city = select_city(cities);
    strncpy(this_package.sender_city, orig_city.name, sizeof(orig_city.name));
    this_package.sender_city[sizeof(orig_city.name) - 1] = '\0';

    printf("Masukkan nama penerima: ");
    scanf("%s", &this_package.receiver_name);

    printf("Pilih kota tujuan dari pilihan berikut\n\n");
    dest_city = select_city(cities);
    strncpy(this_package.receiver_city, dest_city.name, sizeof(dest_city.name));
    this_package.receiver_city[sizeof(dest_city.name) - 1] = '\0';

    printf("Masukkan panjang paket (cm): ");
    scanf("%d", &this_package.length);

    printf("Masukkan lebar paket (cm): ");
    scanf("%d", &this_package.width);

    printf("Masukkan tinggi paket (cm): ");
    scanf("%d", &this_package.height);

    printf("Masukkan berat paket (kg): ");
    scanf("%d", &this_package.weight);

    volume = calc_volume(this_package.length, this_package.width, this_package.height);
    distance = calc_distance(orig_city.latitude, orig_city.longitude, dest_city.latitude, dest_city.longitude);
    delivery_type = select_delivery_type(delivery_types, volume, this_package.weight, distance);

    this_package.distance = distance;
    strncpy(this_package.delivery_type, delivery_type.name, sizeof(delivery_type.name));
    this_package.delivery_type[sizeof(delivery_type.name) - 1] = '\0';
    this_package.delivery_price = delivery_type.price;

    // Construct Package Status
    struct PackageStatus package_status = {
        .id = (*current_package_status_row) + 1,
        .package_id = this_package.id,
        .status = "Diterima oleh C-Ourier",
    };
    get_current_datetime(package_status.timestamp, sizeof(package_status.timestamp));

    add_new_package(
        packages_table,
        packages,
        current_package_row,
        package_statuses_table,
        package_statuses,
        current_package_status_row,
        this_package,
        package_status);

    printf("\n\nPaket anda dengan nomor resi %s, sudah kami terima.\nSilahkan lacak berkala untuk mengetahui status paket\n\n",
           this_package.tracking_number);
}