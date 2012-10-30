CC=g++
OPTS=-O3 -Wall
CFLAGS=`pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 \
	allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_primitives-5.0`
TWODPATH=../../twoD
TARGET=movement

all: $(TARGET)

exec: all 
	./$(TARGET)

# example code
$(TARGET): $(TARGET).cpp engine.o image.o color.o background.o square.o sprite.o \
	text.o sound.o primitive.o movement.o wall.o
	$(CC) $(OPTS) $(CFLAGS) -o $(TARGET) $(TARGET).cpp engine.o image.o \
		color.o background.o square.o sprite.o text.o sound.o primitive.o \
		movement.o wall.o

square.o: square.h square.cpp
	$(CC) $(OPTS) -c -o square.o square.cpp

wall.o: wall.h wall.cpp
	$(CC) $(OPTS) -c -o wall.o wall.cpp

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

clean:
	rm -f *.o

purge: clean
	rm -f $(TARGET)

