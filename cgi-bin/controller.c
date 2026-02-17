#include "controller.h"
#include "view.h"
#include <string.h>
#include <stdlib.h>

void handle_request(sqlite3 *db) {
    char action[32] = {0};
    char title[256] = {0};
    char id_str[16] = {0};
    int id = 0;
    
    cgiFormStringNoNewlines("action", action, sizeof(action));
    cgiFormStringNoNewlines("title", title, sizeof(title));
    cgiFormStringNoNewlines("id", id_str, sizeof(id_str));
    
    if (id_str[0]) id = atoi(id_str);
    
    Todo todos[100];
    int count = 0;
    
    // Process actions with prepared statements
    if (strcmp(action, "add") == 0 && title[0]) {
        create_todo(db, title);
    } 
    else if (strcmp(action, "toggle") == 0 && id > 0) {
        int completed = 0;
        // Get current status with prepared statement
        sqlite3_stmt *stmt;
        const char *sql = "SELECT completed FROM todos WHERE id = ?;";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, id);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                completed = !sqlite3_column_int(stmt, 0);
            }
            sqlite3_finalize(stmt);
        }
        update_todo(db, id, completed);
    } 
    else if (strcmp(action, "delete") == 0 && id > 0) {
        delete_todo(db, id);
    }
    
    list_todos(db, todos, &count);
    render_header();
    render_todos(todos, count);
    render_footer();
}
