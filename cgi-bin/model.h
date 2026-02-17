#ifndef MODEL_H
#define MODEL_H

#include <sqlite3.h>
#include <cgic.h>

typedef struct {
    int id;
    char title[256];
    int completed;
} Todo;

int init_db(sqlite3 **db);
int create_todo(sqlite3 *db, const char *title);
int list_todos(sqlite3 *db, Todo todos[], int *count);
int update_todo(sqlite3 *db, int id, int completed);
int delete_todo(sqlite3 *db, int id);

#endif
