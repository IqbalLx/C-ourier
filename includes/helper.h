#ifndef HELPER_HEADER
#define HELPER_HEADER

const char *decide_slash();
void open_database_table(char name[255], FILE **table);
void remove_new_line_char(char *str);

#endif