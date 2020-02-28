run : main
	./out
	-rm *.o out
	Rscript printposition.R
	cd plots; echo "I'm in plots, converting images to a gif. This may take a while..."; convert *.png out.gif; sxiv out.gif -a; cd ..\

main :
	gcc -c -Wall main.c -g
	gcc -o out main.o