run : main
	./test
	-rm *.o test

main :
	gcc -c main.c
	gcc -o test main.o
