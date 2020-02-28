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

## Where I stopped at 28/02/2020

What I've been doing is trying to fix de collapse problem. After a long time stuck, I found memory leaks errors in linkedlist.h and a problem of construction in Choose_Mate function. I fixed both. The individuals are still collapsing, less than before, I also finnished a first version of DETAILED.md. The next step is correcting the libraries, and analising what I have so far, to look for more problems to fix.


## References

DE AGUIAR, Marcus Aloizo Martinez et al. Global patterns of speciation and diversity. **Nature**, v. 460, n. 7253, p. 384-387, 2009.
