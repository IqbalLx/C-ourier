#ifndef HELPER_HEADER
#define HELPER_HEADER

const char *decide_slash();
void open_database_table(char name[255], FILE **table);
void remove_new_line_char(char *str);
char get_current_datetime(char *datetime, size_t buffer_size);
char generate_random_string(char *string);
void remove_word_from_string(char *str, const char *word_to_remove);
void trim_space(char *str);

#endif