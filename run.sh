#!/bin/sh

for r in 7 15
do
	for l in 200
	do
		dir=./data/sizes_tests//$r/$l
		mkdir -p $dir/species
		mkdir -p $dir/sizes
		mkdir -p $dir/distances
		mkdir -p $dir/position
		echo "real;usr;sys" > $dir/performance_$l.txt

		gcc -g -c main.c source/*.c -I /usr/include/gsl/
		gcc -ansi -pedantic -Wall *.o -lgsl -lgslcblas -lm -o out

		for i in $(seq -f "%02g" 1)
		do 
			/usr/bin/time -o ./data/sizes_tests/$r/$l/performance_$l.txt -a -f "%E; %U; %S" ./out 4 $l $i $r
		done
	done
done
rm *.o out
