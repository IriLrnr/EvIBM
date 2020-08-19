run : main
	@#gdb out
	@/usr/bin/time -o  performance.txt -a -f "%E real,%U user,%S sys" ./out
	@rm *.o out

main :
	@gcc -g -c *.c -I /usr/include/gsl/
	@gcc *.o -lgsl -lgslcblas -lm -o out
	@#gcc -g -c *.c
	@#gcc *.o -lm -o out

R:
	Rscript ./R/space.R
	Rscript ./R/species.R
	Rscript ./R/sizes.R