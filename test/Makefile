GEN_INCLUDE=/home/ozlatior/genetic
GEN_LIB=/home/ozlatior/genetic

CC=g++
CFLAGS=-fPIC
CFLAGS+=-I$(GEN_INCLUDE)
LDFLAGS+=-lgen -L$(GEN_LIB)
OBJ=util.o basic.o crossover.o all.o

RM=rm -f

all: run_all

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

run_all: $(OBJ)
	$(CC) -o run_all $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJ) run_all

.PHONY: all clean
