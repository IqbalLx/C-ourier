#ifndef AUTH_HEADER
#define AUTH_HEADER

// data
void load_users(FILE *users_table, struct User *users, int *current_user_row);
void add_user(FILE *user_table, struct User *users, int *current_user_row, char email[255]);
int check_email_exists(struct User *users, int *current_user_row, char email[255]);
void get_user(struct User *user, struct User *users, int *current_user_row, char email[255]);

// service
int do_user_register(FILE *users_table, struct Item *users, int *current_user_row);
int do_user_login(struct User *users, int *current_user_row, struct User *current_logged_in_user);

#endif