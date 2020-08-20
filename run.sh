#!/bin/sh

read -p "Enter Genome size:" genome
genome_dir=./data/performance_tests/B/$genome
mkdir -p $genome_dir/species
touch ./data/performance_tests/B/performance_$genome.txt

gcc -g -c *.c -I /usr/include/gsl/
gcc *.o -lgsl -lgslcblas -lm -o out_$genome

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do 
	/usr/bin/time -o  ./data/performance_tests/B/performance_$genome.txt -a -f "%E; %U; %S" ./out_$genome 3 $genome $i
done
	rm out_$genome