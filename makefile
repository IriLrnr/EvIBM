run : main
	./out
	rm *.o out
	cd ../ProjetoFinalJB; Rscript ./R/space.R;
main :
	gcc -c -Wall main.c -g
	gcc -o out main.o