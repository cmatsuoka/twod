CC=g++
OPTS=-O3 -Wall -std=gnu++11
CFLAGS=`pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 \
	allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_primitives-5.0`
TWODPATH=../../twoD
TARGET=parallax

all: $(TARGET)

exec: all 
	./$(TARGET)

# example code
$(TARGET): $(TARGET).cpp engine.o image.o color.o background.o sprite.o \
	text.o sound.o primitive.o movement.o border.o map.o spaceship.o info.o
	$(CC) $(OPTS) $(CFLAGS) -o $(TARGET) $(TARGET).cpp engine.o image.o \
		color.o background.o sprite.o text.o sound.o primitive.o \
		movement.o border.o map.o spaceship.o info.o

spaceship.o: spaceship.h spaceship.cpp
	$(CC) $(OPTS) -c -o spaceship.o spaceship.cpp

info.o: info.h info.cpp
	$(CC) $(OPTS) -c -o info.o info.cpp

# twoD engine code
engine.o: $(TWODPATH)/engine.h $(TWODPATH)/engine.cpp
	$(CC) $(OPTS) -c -o engine.o $(TWODPATH)/engine.cpp

image.o: $(TWODPATH)/base/image.h $(TWODPATH)/base/image.cpp
	$(CC) $(OPTS) -c -o image.o $(TWODPATH)/base/image.cpp

color.o: $(TWODPATH)/base/color.h $(TWODPATH)/base/color.cpp
	$(CC) $(OPTS) -c -o color.o $(TWODPATH)/base/color.cpp

background.o: $(TWODPATH)/base/background.h $(TWODPATH)/base/background.cpp
	$(CC) $(OPTS) -c -o background.o $(TWODPATH)/base/background.cpp

sprite.o: $(TWODPATH)/base/sprite.h $(TWODPATH)/base/sprite.cpp
	$(CC) $(OPTS) -c -o sprite.o $(TWODPATH)/base/sprite.cpp

text.o: $(TWODPATH)/base/text.h $(TWODPATH)/base/text.cpp
	$(CC) $(OPTS) -c -o text.o $(TWODPATH)/base/text.cpp

sound.o: $(TWODPATH)/base/sound.h $(TWODPATH)/base/sound.cpp
	$(CC) $(OPTS) -c -o sound.o $(TWODPATH)/base/sound.cpp

primitive.o: $(TWODPATH)/base/primitive.h $(TWODPATH)/base/primitive.cpp
	$(CC) $(OPTS) -c -o primitive.o $(TWODPATH)/base/primitive.cpp

movement.o: $(TWODPATH)/base/movement.h $(TWODPATH)/base/movement.cpp
	$(CC) $(OPTS) -c -o movement.o $(TWODPATH)/base/movement.cpp

border.o: $(TWODPATH)/objects/border.h $(TWODPATH)/objects/border.cpp
	$(CC) $(OPTS) -c -o border.o $(TWODPATH)/objects/border.cpp

map.o: $(TWODPATH)/objects/map.h $(TWODPATH)/objects/map.cpp
	$(CC) $(OPTS) -c -o map.o $(TWODPATH)/objects/map.cpp

clean:
	rm -f *.o

purge: clean
	rm -f $(TARGET)

