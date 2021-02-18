#!/bin/sh

for r in  10
do
	for l in 100 #200 300 400
	do
		dir=./data/sizes_tests//$r/$l
		mkdir -p $dir/species
		mkdir -p $dir/sizes
		mkdir -p $dir/distances
		echo "real;usr;sys" > $dir/performance_$l.txt

		gcc -g -c main.c source/*.c -I /usr/include/gsl/
		gcc -ansi -pedantic -Wall *.o -lgsl -lgslcblas -lm -o out

		for i in $(seq -f "%02g" 1 4)
		do 
			echo "gen;sp;pop;sim" > $dir/species/numsp_$i.csv
			echo "sim;gen;sp;size;pop" > $dir/sizes/sizes_$i.csv
			echo "sim;i;dg;ds" > $dir/distances/distances_$i.csv
			/usr/bin/time -o ./data/sizes_tests/$r/$l/performance_$l.txt -a -f "%E; %U; %S" ./out 4 $l $i $r
			#gdb out
		done
	done
done

