TARGET = healkristin
CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = main.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o 

clean:
	rm -f $(OBJS) $(TARGET)