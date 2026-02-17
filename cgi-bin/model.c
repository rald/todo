#include "model.h"
#include <string.h>
#include <stdlib.h>

int init_db(sqlite3 **db) {
    if (sqlite3_open("todo.db", db) != SQLITE_OK) return 0;
    
    const char *sql = "CREATE TABLE IF NOT EXISTS todos ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "title TEXT NOT NULL, "
                      "completed INTEGER DEFAULT 0);";
    char *err = 0;
    if (sqlite3_exec(*db, sql, 0, 0, &err) != SQLITE_OK) {
        sqlite3_free(err);
        return 0;
    }
    return 1;
}

int create_todo(sqlite3 *db, const char *title) {
    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO todos (title) VALUES ('%s');", title);
    char *err = 0;
    return sqlite3_exec(db, sql, 0, 0, &err) == SQLITE_OK;
}

int list_todos(sqlite3 *db, Todo todos[], int *count) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, title, completed FROM todos ORDER BY id DESC;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return 0;
    
    *count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW && *count < 100) {
        todos[*count].id = sqlite3_column_int(stmt, 0);
        strncpy(todos[*count].title, (char*)sqlite3_column_text(stmt, 1), 255);
        todos[*count].title[255] = '\0';
        todos[*count].completed = sqlite3_column_int(stmt, 2);
        (*count)++;
    }
    sqlite3_finalize(stmt);
    return 1;
}

int update_todo(sqlite3 *db, int id, int completed) {
    char sql[256];
    snprintf(sql, sizeof(sql), "UPDATE todos SET completed=%d WHERE id=%d;", completed, id);
    char *err = 0;
    return sqlite3_exec(db, sql, 0, 0, &err) == SQLITE_OK;
}

int delete_todo(sqlite3 *db, int id) {
    char sql[128];
    snprintf(sql, sizeof(sql), "DELETE FROM todos WHERE id=%d;", id);
    char *err = 0;
    return sqlite3_exec(db, sql, 0, 0, &err) == SQLITE_OK;
}
