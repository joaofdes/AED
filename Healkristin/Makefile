TARGET = healkristin
CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = main.o tasks.o list.o aux.o union_find.o position.o
TEST_DIR = BabyOnes

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c position.h tasks.h
	$(CC) $(CFLAGS) -c main.c -o main.o 

position.o: position.c position.h
	$(CC) $(CFLAGS) -c position.c -o position.o

tasks.o: tasks.c tasks.h union_find.h
	$(CC) $(CFLAGS) -c tasks.c -o tasks.o

aux.o: aux.c aux.h 
	$(CC) $(CFLAGS) -c aux.c -o aux.o

list.o: list.c list.o 
	$(CC) $(CFLAGS) -c list.c -o list.o

union_find.o: union_find.c union_find.h
	$(CC) $(CFLAGS) -c union_find.c -o union_find.o

clean:
	rm -f $(OBJS) $(TARGET)

test-all: $(TARGET)
	@for f in $(TEST_DIR)/*.quests; do \
		base=$${f%.quests}; \
		echo "A executar teste: $$base"; \
		./$(TARGET) $$base.quests $$base.map $$base.position; \
	done

run: $(TARGET)
	./$(TARGET) $(TEST_DIR)/$(t).quests $(TEST_DIR)/$(t).map $(TEST_DIR)/$(t).position