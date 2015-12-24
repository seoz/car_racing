all:
	gcc main.c -o main `pkg-config --cflags --libs elementary` -g
