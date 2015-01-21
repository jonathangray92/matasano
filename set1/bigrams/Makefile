GCC_FLAGS = -g

all: bigram.o

%.o: %.c 
		gcc -c $(GCC_FLAGS) $< -o $@

clean:
	rm -f bigram *.o
