P=tn
OBJECTS=$(P).o
CFLAGS = -g -Wall -std=c11 -pedantic -O3
LDLIBS =

$(P): $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(P)

install: $(P)
	cp tn $(HOME)/bin/tn

.PHONY: clean
