HEADERS = base64.h hex.h string.h xor.h
GCC_FLAGS = -g
ENCODING_LIB = base64.o hex.o string.o
XOR_LIB = xor.o
BIGRAM_LIB = bigrams/bigram.o bigrams/fmemopen.o

all: challenge1 challenge2 challenge3

%.o: %.c $(HEADERS)
	gcc -c $(GCC_FLAGS) $< -o $@

challenge1: challenge1.o $(ENCODING_LIB)
	gcc $+ -o $@

challenge2: challenge2.o $(ENCODING_LIB) $(XOR_LIB)
	gcc $+ -o $@

challenge3: challenge3.o $(ENCODING_LIB) $(XOR_LIB) $(BIGRAM_LIB)
	gcc $+ -o $@

clean:
	rm -f *.o challenge1 challenge2 challenge3
