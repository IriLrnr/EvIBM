#!/bin/sh

for r in  10
do
	for l in 100 200 300 400
	do
		l_dir=./data/sizes_tests//$r/$l
		mkdir -p $l_dir/species
		mkdir -p $l_dir/sizes
		touch ./data/sizes_tests/$r/performance_$l.txt

		gcc -g -c main.c source/*.c -I /usr/include/gsl/
		gcc -ansi -pedantic -Wall *.o -lgsl -lgslcblas -lm -o out

		for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
		do 
			/usr/bin/time -o ./data/sizes_tests/$r/performance_$l.txt -a -f "%E; %U; %S" ./out 4 $l $i $r
		done
	done
done
rm *.o out

