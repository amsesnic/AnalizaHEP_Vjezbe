CC = g++
CFLAGS = -I.
DEPS = ElementaryParticle.h ran1.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analyzer: analyzer.o ElementaryParticle.o ran1.o
	$(CC) -o analyzer analyzer.o ElementaryParticle.o ran1.o

.PHONY: clean
clean:
	rm -rf *.o analyzer
