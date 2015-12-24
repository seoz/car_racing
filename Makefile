all:
	gcc car.c -o car `pkg-config --cflags --libs elementary` -g
