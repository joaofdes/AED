TARGET = healkristin
CC = gcc
CFLAGS = -Wall -std=c99 -O3
OBJS = main.o tasks.o list.o aux.o union_find.o position.o
TEST_DIR ?= BabyOnes
TEST_DIRS = BabyOnes ChildOnes PreTeenOnes TeenOnes

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

# corre todos os testes das duas pastas, acho q n funciona super bem lowkey
test-all: $(TARGET)
	@for d in $(TEST_DIRS); do \
		for f in $$d/*.quests; do \
			base=$${f%.quests}; \
			echo "A executar teste: $$base"; \
			./$(TARGET) $$base.quests $$base.map $$base.position; \
		done; \
	done

# corre os testes duma pasta em específico, usas tipo make test-dir TEST_DIR=ChildOnes
test-dir: $(TARGET)
	@for f in $(TEST_DIR)/*.quests; do \
		base=$${f%.quests}; \
		echo "A executar teste: $$base"; \
		./$(TARGET) $$base.quests $$base.map $$base.position; \
	done

# corre um teste, make run t=Child01 TEST_DIR=ChildOnes
run: $(TARGET)
	./$(TARGET) $(TEST_DIR)/$(t).quests $(TEST_DIR)/$(t).map $(TEST_DIR)/$(t).position
