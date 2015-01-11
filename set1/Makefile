HEADERS = base64.h hex.h
GCC_FLAGS = -O2

%.o: %.c $(HEADERS)
	gcc -c $(GCC_FLAGS) $< -o $@

challenge1: challenge1.o base64.o hex.o
	gcc challenge1.o base64.o hex.o -o $@

clean:
	rm -f *.o challenge1
