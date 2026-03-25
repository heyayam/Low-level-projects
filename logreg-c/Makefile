CC = gcc
CFLAGS = -Wall -O2

SRC = src/main.c src/logistic_regression.c
OUT = logreg

all:
	$(CC) $(CFLAGS) $(SRC) -lm -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
