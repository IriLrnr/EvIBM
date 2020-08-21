main : run
	
run :
	./run.sh

R:
	Rscript ./R/space.R
	Rscript ./R/species.R
	Rscript ./R/sizes.R

clean:
	rm *.o out* run