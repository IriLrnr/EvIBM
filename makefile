run : main
	./out
	-rm *.o out

main :
	gcc -c main.c
	gcc -o out main.o
