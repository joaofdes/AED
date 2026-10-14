TARGET = healkristin
CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = main.o
TEST_DIR = BabyOnes

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o 

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