#include "view.h"

#include <cgic.h>
#include <stdio.h>

void render_header() {
    fprintf(cgiOut, "<!DOCTYPE html>\n");
    fprintf(cgiOut, "<html>\n");
    fprintf(cgiOut, "<head>\n");
    fprintf(cgiOut, "<title>TodoMVC CGI</title>\n");
    fprintf(cgiOut, "<meta name='viewport' content='width=device-width, initial-scale=1'>\n");
    fprintf(cgiOut, "<link rel='stylesheet' href='/css/style.css'>\n");
    fprintf(cgiOut, "</head>\n");
    fprintf(cgiOut, "<body>\n");
    fprintf(cgiOut, "<div class='container'>\n");
    fprintf(cgiOut, "<h1>TodoMVC</h1>\n");
    fprintf(cgiOut, "<form method='POST' class='input-group'>\n");
    fprintf(cgiOut, "<input type='text' name='title' placeholder=\"What needs to be done?\" required autocomplete='off'>\n");
    fprintf(cgiOut, "<button type='submit' name='action' value='add' class='btn btn-primary'>Add Todo</button>\n");
    fprintf(cgiOut, "</form>\n");
}

void render_todos(Todo todos[], int count) {
    int completed_count = 0;
    for (int i = 0; i < count; i++) {
        if (todos[i].completed) completed_count++;
    }
    
    fprintf(cgiOut, "<ul class='todo-list'>");
    for (int i = 0; i < count; i++) {
        char buf[1024];
        const char *text_class = todos[i].completed ? "completed" : "";
        const char *toggle_text = todos[i].completed ? "Undo" : "Done";
        const char *toggle_class = todos[i].completed ? "btn-success" : "btn-success";
        
        snprintf(buf, sizeof(buf),
            "<li class='todo-item'>"
            "<div class='todo-content'>"
            "<div class='todo-text %s'>%s</div>"
            "<div class='todo-actions'>"
            "<form method='POST' style='display:inline'>"
            "<input type='hidden' name='id' value='%d'>"
            "<button type='submit' name='action' value='toggle' class='btn %s'>%s</button>"
            "</form>"
            "<form method='POST' style='display:inline'>"
            "<input type='hidden' name='id' value='%d'>"
            "<button type='submit' name='action' value='delete' class='btn btn-danger'>Delete</button>"
            "</form>"
            "</div></div></li>",
            text_class, todos[i].title, todos[i].id, toggle_class, toggle_text,
            todos[i].id);
        fprintf(cgiOut, "%s", buf);
    }
    fprintf(cgiOut, "</ul>");
    
    // Add counter
    fprintf(cgiOut, "<div class='counter'>%d todos remaining (%d completed)</div>", 
            count - completed_count, completed_count);
}

void render_footer() {
    fprintf(cgiOut, "<div class='footer'>");
    fprintf(cgiOut, "Built with love using CGIC + SQLite3 + C<br>MVC Architecture");
    fprintf(cgiOut, "</div>");
    fprintf(cgiOut, "</div></body></html>\n");
}
