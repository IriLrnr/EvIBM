run : main
	./out
	-rm *.o out

main :
	gcc -c main.c -g
	gcc -o out main.o
