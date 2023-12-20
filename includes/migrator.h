#ifndef MIGRATION_HEADER
#define MIGRATION_HEADER

struct Table
{
    char name[255];
    int column_length;
    char columns[255][255];
};

#endif