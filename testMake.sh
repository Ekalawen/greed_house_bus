#!/bin/bash

gcc -c testBus.c $(sdl-config --cflags --libs) -g 
gcc -c testEvents.c $(sdl-config --cflags --libs) -g 
gcc -c testMap.c $(sdl-config --cflags --libs) -g 
gcc -c testOutil.c $(sdl-config --cflags --libs) -g 
gcc -c testPassager.c $(sdl-config --cflags --libs) -g 
gcc -c testPoint.c $(sdl-config --cflags --libs) -g 
gcc -c testPolygone.c $(sdl-config --cflags --libs) -g 
gcc -c testSegment.c $(sdl-config --cflags --libs) -g 

gcc -c bus.c $(sdl-config --cflags --libs) -g 
gcc -c events.c $(sdl-config --cflags --libs) -g 
gcc -c map.c $(sdl-config --cflags --libs) -g 
gcc -c outil.c $(sdl-config --cflags --libs) -g 
gcc -c passager.c $(sdl-config --cflags --libs) -g 
gcc -c point.c $(sdl-config --cflags --libs) -g 
gcc -c polygone.c $(sdl-config --cflags --libs) -g 
gcc -c segment.c $(sdl-config --cflags --libs) -g 


gcc -o runTestsBus testBus.o bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm
gcc -o runTestsEvents testEvents.o bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm
gcc -o runTestsMap testMap.o bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm
gcc -o runTestsOutil testOutil.o bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm
gcc -o runTestsPassager testPassager.o bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm
gcc -o runTestsPoint testPoint.o bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm
gcc -o runTestsPolygone testPolygone.o bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm
gcc -o runTestsSegment testSegment.o bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o $(sdl-config --cflags --libs) -lSDL_image -lSDL_ttf -lSDL_gfx -lm

./runTestsBus
./runTestsEvents
./runTestsMap
./runTestsOutil
./runTestsPassager
./runTestsPoint
./runTestsPolygone
./runTestsSegment

rm testBus.o testEvents.o testMap.o testOutil.o testPassager.o testPoint.o testPolygone.o testSegment.o

rm bus.o events.o map.o outil.o passager.o point.o polygone.o segment.o

rm runTestsBus runTestsEvents runTestsMap runTestsOutil runTestsPassager runTestsPoint runTestsPolygone runTestsSegment
