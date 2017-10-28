GCC=gcc -g -Wall -Wextra -std=gnu11

encode: encode.o encode_function.o ppm.o
	$(GCC) $^ -o $@

encode.o: encode.c
	$(GCC) $< -c

encode_function.o: encode_function.c encode_function.h
	$(GCC) $< -c

pm.o: ppm.c ppm.h
	$(GCC) $< -c

clean:
	rm -f *.o encode
