# EvIBM

This program is a scientific iniciation project. It simulates an Individual Based Model created by Marcus Aguiar (Aguiar _et al_, 2009). The project is funded by FAPESP - Fundação de apoio a pesquisa do estado de São Paulo.

HELLO!

Welcome to my developing code for this Evolutionary Model! If you are VERY interested in the code and the model behind it, please read the DETAILED.md file.

This branch is used to test and analise the situation of the aglutination of individuals in the model. If you want to run the program and see the results, follow the instructions below

## How to compile

To compile this code you may have to install some programs before. See [instalation](#install) for more information.

## Installation <a name="install"></a>

Here's how to install make

### Just compile with gcc

This won't create the cvs, png and gifs, just print out the generation and number of species.

```bash
$ gcc main.c -I /usr/include/gsl/ -o -lgsl -lgslcblas -lm out
$ ./out
```

The best way to compile is with `make`:
```bash
$ make
```

## Installation <a name="install"></a>

First, install GLS

~~~bash
$ sudo apt update
$ sudo apt install libgsl-dev
~~~

Here's how to install make

```bash
$ sudo apt install build.essentials
```

To compile the R script you may need to install R, here is a tutorial: https://cran.r-project.org/

## References

DE AGUIAR, Marcus Aloizo Martinez et al. Global patterns of speciation and diversity. **Nature**, v. 460, n. 7253, p. 384-387, 2009.
