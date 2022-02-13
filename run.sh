#!/bin/bash

trap signal_handler INT
signal_handler() {
    echo ""
    echo "Found an interruption. Aborting..."
    exit
}

for r in 5
do
	for l in 100
	do
		dir="./data/article/$r/$l"
		mkdir -p "$dir/"{species,sizes,distances,status}

		echo "real;usr;sys" > "$dir/performance_$l.txt"

		for i in $(seq -f "%02g" 1)
		do 
			$(which time) -o "$dir/performance_$l.txt" \
			    -a -f "%E; %U; %S" ./build/EvIBM 4 "$l" "$i" "$r"
		done
	done
done

rm ./*.o out
