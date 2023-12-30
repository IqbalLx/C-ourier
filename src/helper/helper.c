#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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

    setlinebuf(*table);
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

char get_current_datetime(char *datetime, size_t buffer_size)
{
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    info = localtime(&rawtime);

    strftime(datetime, buffer_size, "%Y-%m-\%d %H:%M:\%S", info);
}

char generate_random_string(char *string)
{
    static const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int charset_length = sizeof(charset) - 1;

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 8; ++i)
    {
        string[i] = charset[rand() % charset_length];
    }
    string[8] = '\0';
}

void remove_word_from_string(char *str, const char *word_to_remove)
{
    char *found = strstr(str, word_to_remove); // Find the word in the string
    while (found)
    {
        memmove(found, found + strlen(word_to_remove), strlen(found + strlen(word_to_remove)) + 1);
        found = strstr(str, word_to_remove); // Find next occurrence
    }
}

void trim_space(char *str)
{
    int start = 0, end = strlen(str) - 1;

    // Trim spaces from the start
    while (isspace((unsigned char)str[start]))
    {
        start++;
    }

    // Trim spaces from the end
    while (end >= start && isspace((unsigned char)str[end]))
    {
        end--;
    }

    // Shift characters to the start of the string
    for (int i = 0; i <= end - start; i++)
    {
        str[i] = str[start + i];
    }

    // Null-terminate the trimmed string
    str[end - start + 1] = '\0';
}