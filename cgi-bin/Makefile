CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -I. -I cgic -I sqlite3
LIBS=-L cgic -lcgic -L sqlite3 -lsqlite3 -lm

SRC=model.c view.c controller.c todo.c
OBJ=$(SRC:.c=.o)

todo.cgi: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o todo.cgi
