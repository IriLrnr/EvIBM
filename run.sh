#!/bin/sh

#read -p "Enter Genome size:" genome
genome=150
genome_dir=./data/performance_tests/B/$genome
mkdir -p $genome_dir/species
touch ./data/performance_tests/B/performance_$genome.txt

gcc -g -c main.c source/*.c -I /usr/include/gsl/
gcc -ansi -pedantic -Wall *.o -lgsl -lgslcblas -lm -o out_$genome

for i in 1
do 
	/usr/bin/time -o ./data/performance_tests/B/performance_$genome.txt -a -f "%E; %U; %S" ./out_$genome 3 $genome $i
done
	rm *.o out_$genome
