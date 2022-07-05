#!/bin/bash

trap signal_handler INT
signal_handler() {
    echo ""
    echo "Found an interruption. Aborting..."
    exit
}

for l in 200 175 150 125 100 75 50
do
	for r in 50 40 30 25 20 15 12 10 7 5 3
	do
		dir="./data/article/$r/$l"
		mkdir -p "$dir/"{species,sizes,distances,status}

		echo "real;usr;sys" > "$dir/performance_$l.txt"

		for i in $(seq -f "%02g" 5)
		do 
			$(which time) -o "$dir/performance_$l.txt" \
			    -a -f "%E; %U; %S" ./build/EvIBM 4 "$l" "$i" "$r"
		done
	done
done
