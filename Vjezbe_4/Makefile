CC = g++
CFLAGS = -I.
DEPS = Analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analyze: analyze.o Analyzer.o
	$(CC) -o analyze analyze.o Analyzer.o

.PHONY: clean
clean:
	rm -rf *.o analyze
