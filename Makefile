all: tp.o hash.o indiceInvertido.o
	@gcc tp.o hash.o indiceInvertido.o -o exe
	@rm -r *.o
tp.o: tp.c
	@gcc tp.c -c
indiceInvertido.o: indiceInvertido.c
	@gcc indiceInvertido.c -c
hash.o: hash.c
	@gcc hash.c -c
run:
	@./exe
