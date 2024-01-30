CC = gcc
CFLAGS = -Wall -Wextra

all: exprConverter.out

exprConverter.out: main.o convert.o error.o expr.o precedence.o result.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c convert.h error.h expr.h precedence.h result.h
	$(CC) $(CFLAGS) -c $<

convert.o: convert.c convert.h
	$(CC) $(CFLAGS) -c $<

error.o: error.c error.h
	$(CC) $(CFLAGS) -c $<

expr.o: expr.c expr.h
	$(CC) $(CFLAGS) -c $<

precedence.o: precedence.c precedence.h
	$(CC) $(CFLAGS) -c $<

result.o: result.c result.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o exprConverter.out
