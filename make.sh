#!/bin/bash

gcc -c bus.c $(sdl-config --cflags --libs) -g
gcc -c events.c $(sdl-config --cflags --libs) -g
gcc -c main.c $(sdl-config --cflags --libs) -g
gcc -c map.c $(sdl-config --cflags --libs) -g
gcc -c outil.c $(sdl-config --cflags --libs) -g
gcc -c passager.c $(sdl-config --cflags --libs) -g
gcc -c point.c $(sdl-config --cflags --libs) -g
gcc -c polygone.c $(sdl-config --cflags --libs) -g
gcc -c segment.c $(sdl-config --cflags --libs) -g

gcc -o bus bus.o events.o main.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm

rm bus.o events.o main.o map.o outil.o passager.o point.o polygone.o segment.o
