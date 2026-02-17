CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -I. -I cgic -I sqlite3
LIBS=-L cgic -lcgic -L sqlite3 -lsqlite3 -lm -pthread

SRC=model.c view.c controller.c todo.c
OBJ=$(SRC:.c=.o)

all: libcgic.a libsqlite3.a todo.cgi

libcgic.a: cgic/cgic.c cgic/cgic.h
	gcc -c cgic/cgic.c -o cgic/cgic.o
	ar rcs cgic/libcgic.a cgic/cgic.o

libsqlite3.a: sqlite3/sqlite3.c sqlite3/sqlite3.h
	gcc -c sqlite3/sqlite3.c -o sqlite3/sqlite3.o
	ar rcs sqlite3/libsqlite3.a sqlite3/sqlite3.o

todo.cgi: $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm cgic/*.o cgic/libcgic.a
	rm sqlite3/*.o sqlite3/libsqlite3.a
	rm -f *.o todo.cgi todo.db

