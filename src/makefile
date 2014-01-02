CC = g++
CFLAGS = -c -Wall
LIBS = -lm -lpthread -L/usr/X11R6/lib -lX11
EXE = linklist

$(EXE): main.o
	$(CC) $(LIBS) main.o -o $(EXE)
	
main.o: main.cpp
	$(CC) -c main.cpp

all: $(EXE)

clean:
	@rm -f $(EXE) *.o
