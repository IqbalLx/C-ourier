#include <stdio.h>
#include <math.h>
#include <string.h>

#include "entity.h"
#include "package.h"
#include "helper.h"

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

int sequential_search_packages_by_tracking_number(struct Package *packages, int *current_package_row, char tracking_number[255])
{
    for (int i = 0; i < *current_package_row; i++)
    {
        struct Package curr_package = packages[i];
        int is_match = strcmp(curr_package.tracking_number, tracking_number) == 0;
        if (is_match)
        {
            return i;
        }
    }

    return -1;
}

struct FilteredPackageStatus filter_package_status_by_package_id(struct PackageStatus *package_statuses, int *current_package_status_row, int package_id)
{
    struct PackageStatus filtered_package_statuses[10];
    int filtered_package_status_index = 0;
    for (int i = 0; i < *current_package_status_row; i++)
    {
        struct PackageStatus curr_package_status = package_statuses[i];
        if (curr_package_status.package_id == package_id)
        {
            filtered_package_statuses[filtered_package_status_index] = curr_package_status;
            filtered_package_status_index++;
        }
    }

    struct FilteredPackageStatus res =
        {
            .count = filtered_package_status_index,
            .data = filtered_package_statuses,
        };

    return res;
}

void quick_sort_descending_package_status_by_id(struct PackageStatus *arr, int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high].id;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j].id > pivot)
            {
                i++;
                struct PackageStatus temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        struct PackageStatus temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int partition_id = i + 1;
        quick_sort_descending_package_status_by_id(arr, low, partition_id - 1);
        quick_sort_descending_package_status_by_id(arr, partition_id + 1, high);
    }
}

void merge(struct PackageStatus *arr, int low, int mid, int high)
{
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    struct PackageStatus left[leftSize];
    struct PackageStatus right[rightSize];

    for (int i = 0; i < leftSize; i++)
        left[i] = arr[low + i];
    for (int j = 0; j < rightSize; j++)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < leftSize && j < rightSize)
    {
        if (left[i].id >= right[j].id)
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < leftSize)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < rightSize)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort_descending_package_status_by_id(struct PackageStatus *arr, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;

        merge_sort_descending_package_status_by_id(arr, low, mid);
        merge_sort_descending_package_status_by_id(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

void insertion_sort_descending_package_status_by_id(struct PackageStatus arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        struct PackageStatus key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].id < key.id)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void display_package_status(struct Package package, struct PackageStatus *package_statuses, int length)
{
    printf("\nNama Paket: %s [%s]\n", package.name, package.tracking_number);
    printf("%s (%s) ->-> %s (%s)\n", package.sender_city, package.sender_name, package.receiver_city, package.receiver_name);

    printf("\nStatus Terakhir: %s\n", package_statuses[0].status);
    printf("Terakhir Diperbaharui: %s\n\n", package_statuses[0].timestamp);

    printf("Riwayat status: \n\n");
    for (int i = 0; i < length; i++)
    {
        printf(" | \n");
        printf("[*] %s", package_statuses[i].status);
        printf(" - %s \n", package_statuses[i].timestamp);
        printf(" | \n");
    }
}

int binary_search_package_by_id(struct Package *packages, int *current_package_row, int package_id)
{
    int left = 0;
    int right = (*current_package_row) - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (packages[mid].id == package_id)
            return mid;

        if (packages[mid].id < package_id)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void decide_next_status(struct Package package, char curr_package_status[255], char *next_package_status, size_t next_package_status_size)
{
    char status_instant_sameday[STATUS_INSTANT_SAMEDAY_COUNT][255] = {
        "Diterima oleh C-Ourier",
        "Diantar oleh Kurir",
        "Paket Diterima Oleh",
    };

    char status_nextday_regular[STATUS_NEXTDAY_REGULAR_COUNT][255] = {
        "Diterima oleh C-Ourier",
        "Sampai di Gudang",
        "Menuju Gudang",
        "Diterima di Gudang",
        "Diantar oleh Kurir",
        "Paket Diterima oleh",
    };

    // clean current status
    remove_word_from_string(curr_package_status, package.sender_city);
    remove_word_from_string(curr_package_status, package.receiver_city);
    remove_word_from_string(curr_package_status, package.receiver_name);
    trim_space(curr_package_status);

    int curr_package_status_idx;
    int is_package_instant_sameday = (strcmp(package.delivery_type, "Instant") == 0 ||
                                      strcmp(package.delivery_type, "Same Day") == 0);

    // Instant or Same day

    if (is_package_instant_sameday)
    {

        for (int i = 0; i < STATUS_INSTANT_SAMEDAY_COUNT; i++)
        {
            int is_match = strcmp(status_instant_sameday[i], curr_package_status) == 0;
            if (is_match)
            {
                curr_package_status_idx = i;
                break;
            }
        }

        strncpy(next_package_status, status_instant_sameday[curr_package_status_idx + 1], next_package_status_size - 1);
        next_package_status[next_package_status_size - 1] = "\0";

        int is_received_status = strcmp(next_package_status, "Paket Diterima Oleh") == 0;
        if (is_received_status)
        {
            strcat(next_package_status, " ");
            strcat(next_package_status, package.receiver_name);
        }

        return;
    }

    // Next Day and regular

    for (int i = 0; i < STATUS_NEXTDAY_REGULAR_COUNT; ++i)
    {
        int is_match = strcmp(status_nextday_regular[i], curr_package_status) == 0;
        if (is_match)
        {
            curr_package_status_idx = i;
            break;
        }
    }

    strncpy(next_package_status, status_nextday_regular[curr_package_status_idx + 1], next_package_status_size - 1);
    next_package_status[next_package_status_size - 1] = "\0";

    // Sampai di Gudang
    int is_received_in_orig_warehouse_status = strcmp(next_package_status, "Sampai di Gudang") == 0;
    if (is_received_in_orig_warehouse_status)
    {
        strcat(next_package_status, " ");
        strcat(next_package_status, package.sender_city);
    }

    // Menuju Gudang
    int is_gone_to_dest_warehouse_status = strcmp(next_package_status, "Menuju Gudang") == 0;
    if (is_gone_to_dest_warehouse_status)
    {
        strcat(next_package_status, " ");
        strcat(next_package_status, package.receiver_city);
    }

    // Diterima di Gudang
    int is_received_in_dest_warehouse_status = strcmp(next_package_status, "Diterima di Gudang") == 0;
    if (is_received_in_dest_warehouse_status)
    {
        strcat(next_package_status, " ");
        strcat(next_package_status, package.receiver_city);
    }

    // Paket Diterima oleh
    int is_received = strcmp(next_package_status, "Paket Diterima oleh") == 0;
    if (is_received)
    {
        strcat(next_package_status, " ");
        strcat(next_package_status, package.receiver_name);
    }

    return;
}