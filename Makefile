CC=g++
CFLAGS=-fPIC -Werror -Wall -Wextra -std=c++11
DEP=*.h
OBJ=Gene.o Chromosome.o BoolGene.o Crossover.o Genotype.o Phaenotype.o
CURDIR=$(shell pwd)

RM=rm -f

all: libgen.so test run_test

%.o: %.cpp $(DEP)
	$(CC) -c -o $@ $< $(CFLAGS)

libgen.so: $(OBJ)
	$(CC) -shared -o libgen.so $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ) libgen.so

test:
	$(MAKE) -C ./test

test-clean:
	$(MAKE) -C ./test clean

run_test:
	./test/run_all

demo:
	$(MAKE) -C $(CURDIR)/demo/

demo-clean:
	$(MAKE) -C $(CURDIR)/demo/ clean

.PHONY: all clean test run_test demo demo-clean
