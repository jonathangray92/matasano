HEADERS = base64.h hex.h string.h xor.h
GCC_FLAGS = -O2
ENCODING_LIB = base64.o hex.o string.o
XOR_LIB = xor.o

%.o: %.c $(HEADERS)
	gcc -c $(GCC_FLAGS) $< -o $@

challenge1: challenge1.o $(ENCODING_LIB)
	gcc $+ -o $@

challenge2: challenge2.o $(ENCODING_LIB) $(XOR_LIB)
	gcc $+ -o $@

clean:
	rm -f *.o challenge1 challenge2
