all: cache

cache: cache_1.o
	gcc -o cache cache_1.o -lm

cache.o: cache_1.c
	gcc -c cache_1.c -lm

clean:
	rm *o cache 
