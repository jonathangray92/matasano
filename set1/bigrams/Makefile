GCC_FLAGS = -O2 

bigram: bigram.c
	gcc bigram.c fmemopen.c ../string.c -o bigram

%.o: %.c
		gcc -c $(GCC_FLAGS) $< -o $@

clean:
	rm -f bigram *.o
