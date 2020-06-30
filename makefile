run : main
	#gdb out
	./out
	rm *.o out

main :
	#gcc -c *.c -I /usr/include/gsl/
	#gcc *.o -lgsl -lgslcblas -lm -o out -g 
	gcc -g -c *.c
	gcc *.o -lm -o out

R:
	Rscript ./R/space.R
	Rscript ./R/species.R
	Rscript ./R/sizes.R