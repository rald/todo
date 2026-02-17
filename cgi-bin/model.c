#include "model.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO todos (title) VALUES (?);";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }
    
    sqlite3_bind_text(stmt, 1, title, -1, SQLITE_STATIC);
    int rc = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return rc;
}

int list_todos(sqlite3 *db, Todo todos[], int *count) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, title, completed FROM todos ORDER BY id DESC;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }
    
    *count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW && *count < 100) {
        todos[*count].id = sqlite3_column_int(stmt, 0);
        strncpy(todos[*count].title, (const char*)sqlite3_column_text(stmt, 1), 255);
        todos[*count].title[255] = '\0';
        todos[*count].completed = sqlite3_column_int(stmt, 2);
        (*count)++;
    }
    sqlite3_finalize(stmt);
    return 1;
}

int update_todo(sqlite3 *db, int id, int completed) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE todos SET completed = ? WHERE id = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }
    
    sqlite3_bind_int(stmt, 1, completed);
    sqlite3_bind_int(stmt, 2, id);
    int rc = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return rc;
}

int delete_todo(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM todos WHERE id = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }
    
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return rc;
}
