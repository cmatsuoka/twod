CC=g++
OPTS=-O3 -Wall
CFLAGS=`pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 \
	allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0 allegro_primitives-5.0`
TARGET=example

all: $(TARGET)

exec: all 
	./$(TARGET)

# example code
$(TARGET): $(TARGET).cpp engine.o image.o color.o background.o test.o sprite.o \
	text.o sound.o primitive.o
	$(CC) $(OPTS) $(CFLAGS) -o $(TARGET) $(TARGET).cpp engine.o image.o \
		color.o background.o test.o sprite.o text.o sound.o primitive.o

test.o: test.h test.cpp
	$(CC) $(OPTS) -c -o test.o test.cpp

# twoD engine code'
engine.o: twoD/engine.h twoD/engine.cpp
	$(CC) $(OPTS) -c -o engine.o twoD/engine.cpp

image.o: twoD/base/image.h twoD/base/image.cpp
	$(CC) $(OPTS) -c -o image.o twoD/base/image.cpp

color.o: twoD/base/color.h twoD/base/color.cpp
	$(CC) $(OPTS) -c -o color.o twoD/base/color.cpp

background.o: twoD/base/background.h twoD/base/background.cpp
	$(CC) $(OPTS) -c -o background.o twoD/base/background.cpp

sprite.o: twoD/base/sprite.h twoD/base/sprite.cpp
	$(CC) $(OPTS) -c -o sprite.o twoD/base/sprite.cpp

text.o: twoD/base/text.h twoD/base/text.cpp
	$(CC) $(OPTS) -c -o text.o twoD/base/text.cpp

sound.o: twoD/base/sound.h twoD/base/sound.cpp
	$(CC) $(OPTS) -c -o sound.o twoD/base/sound.cpp

primitive.o: twoD/base/primitive.h twoD/base/primitive.cpp
	$(CC) $(OPTS) -c -o primitive.o twoD/base/primitive.cpp

clean:
	rm -f *.o

purge: clean
	rm -f $(TARGET)

