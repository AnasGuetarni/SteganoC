GCC=gcc -g -Wall -Wextra -std=c99 -Werror

all: encode decode

encode: encode.o encode_function.o ppm.o
	$(GCC) $^ -o $@ -lpthread

encode.o: encode.c
	$(GCC) $< -c -lpthread

encode_function.o: encode_function.c encode_function.h
	$(GCC) $< -c -lpthread

decode: decode.o decode_function.o ppm.o
	$(GCC) $^ -o $@ -lpthread

decode.o: decode.c
	$(GCC) $< -c -lpthread

decode_function.o: decode_function.c decode_function.h
	$(GCC) $< -c -lpthread

pm.o: ppm.c ppm.h
		$(GCC) $< -c -lpthread

clean:
	rm -f *.o encode
	rm -f *.o decode
