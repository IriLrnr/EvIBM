run : main

main :
	./run.sh


R:
	Rscript ./R/space.R
	Rscript ./R/species.R
	Rscript ./R/sizes.R