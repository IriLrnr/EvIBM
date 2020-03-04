run : main
	./out
	rm *.o out
	cd ../ProjetoFinalJB/R; Rscript space.R;
	cd ../ProjetoFinalJB/figs/position/; ls; convert *.png ../../gifs/agglutination.gif; rm *.png
	cd ../ProjetoFinalJB/data/position/

main :
	gcc -c -Wall main.c -g
	gcc -o out main.o