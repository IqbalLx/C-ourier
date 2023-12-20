#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "helper.h"

void load_users(FILE *users_table, struct User *users, int *current_user_row)
{
    char row[255];
    int row_index = 0;
    while (fgets(row, sizeof(row), users_table))
    {
        if (row_index == 0)
        {
            row_index++;
            continue;
        }

        char *value = strtok(row, ",");
        int col_index = 0;
        while (value != NULL)
        {
            switch (col_index)
            {
            case 0:
                users[*current_user_row].id = atoi(value);
                break;

            case 1:
                strncpy(users[*current_user_row].name, value, sizeof(users[*current_user_row].name) - 1);
                users[*current_user_row].name[sizeof(users[*current_user_row].name) - 1] = '\0';
                break;

            case 2:
                strncpy(users[*current_user_row].email, value, sizeof(users[*current_user_row].email) - 1);
                users[*current_user_row].email[sizeof(users[*current_user_row].email) - 1] = '\0';
                break;

            case 3:
                strncpy(users[*current_user_row].password, value, sizeof(users[*current_user_row].password) - 1);
                remove_new_line_char(&users[*current_user_row].password);
                break;
            }

            value = strtok(NULL, ",");
            col_index++;
        };

        (*current_user_row)++;
        row_index++;
    }
}

void add_user(FILE *user_table, struct User *users, int *current_user_row, char email[255])
{
    users[*current_user_row].id = *current_user_row + 1;

    char name[255], password[255];
    printf("Masukkan nama: ");
    scanf("%s", &name);

    printf("Masukkan password: ");
    scanf("%s", &password);

    strncpy(users[*current_user_row].email, email, sizeof(users[*current_user_row].email) - 1);
    users[*current_user_row].email[sizeof(users[*current_user_row].email) - 1] = '\0';

    strncpy(users[*current_user_row].name, name, sizeof(users[*current_user_row].name) - 1);
    users[*current_user_row].name[sizeof(users[*current_user_row].name) - 1] = '\0';

    strncpy(users[*current_user_row].password, password, sizeof(users[*current_user_row].password) - 1);
    users[*current_user_row].password[sizeof(users[*current_user_row].password) - 1] = '\0';

    fprintf(user_table, "\n%d,%s,%s,%s", users[*current_user_row].id, users[*current_user_row].name, users[*current_user_row].email, users[*current_user_row].password);

    (*current_user_row)++;
}

int check_email_exists(struct User *users, int *current_user_row, char email[255])
{
    for (int i = 0; i < *current_user_row; i++)
    {
        int is_match = strcmp(users[i].email, email) == 0;
        if (is_match)
        {
            return is_match;
        }
    };

    return 0;
}

void get_user(struct User *user, struct User *users, int *current_user_row, char email[255])
{
    for (int i = 0; i < *current_user_row; i++)
    {
        int is_match = strcmp(users[i].email, email) == 0;
        if (is_match)
        {
            *user = users[i];
        }
    };
}