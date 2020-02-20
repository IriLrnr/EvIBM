run : main
	./test

main :
	gcc -c main.c -I /usr/include/gsl/
	gcc main.o -l gsl -o test -g
