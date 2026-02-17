#include <cgic.h>
#include "model.h"
#include "view.h"
#include "controller.h"

int cgiMain() {  // CGIC entry point
    sqlite3 *db = NULL;
    cgiHeaderContentType("text/html");
    
    if (!init_db(&db)) {
        fprintf(cgiOut, "<h1>Database error!</h1>");  // Use fprintf(cgiOut, ...)
        return 1;
    }
    
    handle_request(db);
    sqlite3_close(db);
    return 0;
}
