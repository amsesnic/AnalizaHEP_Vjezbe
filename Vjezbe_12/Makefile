CC = g++
CFLAGS = -I. $(shell root-config --cflags) -lTMVA
LDFLAGS = $(shell root-config --libs) -lTMVA
DEPS = Analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

main: main.o Analyzer.o
	$(CC) $(LDFLAGS) -o main main.o Analyzer.o

.PHONY: clean
clean:
	rm -rf *.o main
