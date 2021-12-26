#!/bin/sh

trap signal_handler INT
signal_handler() {
    echo ""
    echo "Found an interruption. Aborting..."
    exit
}

gcc-9 -g -c main.c source/*.c -I /usr/include/gsl/
gcc-9 -ansi -pedantic -Wall ./*.o -lgsl -lgslcblas -lm -o out

for r in $(seq 50)
do
	for l in $(seq 200)
	do
		dir="./data/article/$r/$l"
		mkdir -p "$dir/{species,sizes,distances,position}"

		echo "real;usr;sys" > "$dir/performance_$l.txt"

		for i in $(seq -f "%02g" 1)
		do 
			$(which time) -o "$dir/performance_$l.txt" \
			    -a -f "%E; %U; %S" ./out 4 "$l" "$i" "$r"
		done
	done
done

rm ./*.o out
