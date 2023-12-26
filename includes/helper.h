#ifndef HELPER_HEADER
#define HELPER_HEADER

const char *decide_slash();
void open_database_table(char name[255], FILE **table);
void remove_new_line_char(char *str);
char get_current_datetime(char *datetime);
char generate_random_string(char *string);

#endif