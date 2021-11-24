CC = g++
CFLAGS = -I.
DEPS = Statistics.h ran1.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o Statistics.o ran1.o
	$(CC) -o main main.o Statistics.o ran1.o

.PHONY: clean
clean:
	rm -rf *.o main
