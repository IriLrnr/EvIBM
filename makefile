run : main
	./out
	rm *.o out
	cd ../ProjetoFinalJB; Rscript ./R/space.R; Rscript ./R/species.R

main :
	gcc -c main.c -I /usr/include/gsl/
	gcc main.o -lgsl -lgslcblas -lm -o out -g 