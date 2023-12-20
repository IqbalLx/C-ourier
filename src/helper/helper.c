#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *decide_slash()
{
#ifdef _WIN32
    return "\\";
#elif __APPLE__
    return "/";
#elif __linux__
    return "/";
#endif
}

void open_database_table(char name[255], FILE **table)
{
    char db_foldername[3] = "db";
    char *slash = decide_slash();
    char filepath[255] = ".";
    strcat(filepath, slash);
    strcat(filepath, db_foldername);
    strcat(filepath, slash);
    strcat(filepath, name);
    strcat(filepath, ".csv");

    *table = fopen(filepath, "a+");
    if (*table == NULL)
    {
        printf("failed to open table %s\n", name);
        exit(1);
    }

    fseek(*table, 0, SEEK_SET);
}

void remove_new_line_char(char *str)
{
    int length = strlen(str);

    for (int i = 0; i < length; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0'; // Replace '\n' with '\0'
            break;         // Stop after the first newline is removed (if you want to remove all, remove this line)
        }
    }
}
