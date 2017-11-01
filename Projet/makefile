GCC=gcc -g -Wall -Wextra -std=c99

all: encode decode

encode: encode.o encode_function.o ppm.o
	$(GCC) $^ -o $@

encode.o: encode.c
	$(GCC) $< -c

encode_function.o: encode_function.c encode_function.h
	$(GCC) $< -c

decode: decode.o decode_function.o ppm.o
	$(GCC) $^ -o $@

decode.o: decode.c
	$(GCC) $< -c

decode_function.o: decode_function.c decode_function.h
	$(GCC) $< -c

pm.o: ppm.c ppm.h
		$(GCC) $< -c

clean:
	rm -f *.o encode decode
