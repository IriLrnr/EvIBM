# EvIBM

This program is a scientific iniciation project. It simulates an Individual Based Model created by Marcus Aguiar (Aguiar _et al_, 2009). The project is funded by FAPESP - Fundação de apoio a pesquisa do estado de São Paulo.

## How to compile
```bash
$ gcc main.c -o out
$ ./out
```
### With make
After cloning the folder, go in it and compile with the command
```bash
$ make
```
If you need, here's how to install make
```bash
$ sudo apt install build.essentials
```
## Exploring the output
The program's output is a list of numerated files, that contains a table of the individuals with their respective species and positions. To explore the output, first, save all the output files in a separated folder, open the script printposition.R, change the paths inside it and run it. In the plots folder, if you want to make a gif, type
```bash
$ convert *.png out.gif
```
This step may take a while.

To read the output, in Linux, you may have to download sxiv to open the gif, so if you need:
```bash
$ sudo apt install sxiv
```
To open the gif type
```bash
$ sxiv out.gif
```

## CHANGING PROBABILITY OF OFFSPRING MOVEMENT BEFORE MERGE

0% probability of moving:
	VERY fast formation, with 58 species at the "end"

1% probability of moving:
	This is supposed to be the right one. In this case we have collapse, in ten generations, fast formation, and stabilization of the final number of species.

10% probability of moving:
	A little collapse in the beggining. Fast formation. Forms 25 species, doesn't stabilize in 1000 gen

25% probability of moving:
	Formation of species begin at 200, Forms 44 species, doesn't stabilize in 1000 gen.

50% probability of moving:
	Formation of species begin at 500, but forms 5 species.

100% probability of moving:
	In this case, there's no fast collapse, no species and THE FINAL PLOT IS SO SO SO SO WEIRD.

Position
## References

DE AGUIAR, Marcus Aloizo Martinez et al. Global patterns of speciation and diversity. **Nature**, v. 460, n. 7253, p. 384-387, 2009.
