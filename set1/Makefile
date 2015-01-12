HEADERS = base64.h hex.h string.h
GCC_FLAGS = -O2
ENCODING_LIB = base64.o hex.o string.o

%.o: %.c $(HEADERS)
	gcc -c $(GCC_FLAGS) $< -o $@

challenge1: challenge1.o $(ENCODING_LIB)
	gcc challenge1.o $(ENCODING_LIB) -o $@

clean:
	rm -f *.o challenge1
