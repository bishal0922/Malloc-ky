CFLAGS = -Wall -Wextra -pedantic -ggdb

heap: main.c
	$(CC) $(CFLAGS) -o heap main.c
