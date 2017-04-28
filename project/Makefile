all: cache

cache: cache_1.o 
	gcc -o cache cache_1.o -lm

cache.o: cache_1.c cache_1.h
	gcc -c cache_1.c -o cache_1.h -lm

clean:
	rm *o cache 
