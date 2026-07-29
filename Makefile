CC = gcc
CFLAGS = -Wall -Wextra -std=c11
INCLUDE = -Iinclude

SRC = src/main.c src/playlist_avl.c

OUT = music_player

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -f $(OUT)
