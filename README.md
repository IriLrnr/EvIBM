# EvIBM

This program is a scientific iniciation project. It simulates an Individual Based Model created by Marcus Aguiar (Aguiar _et al_, 2009). The project is funded by FAPESP - Fundação de apoio a pesquisa do estado de São Paulo.

HELLO!

Welcome to my developing code for this Evolutionary Model! If you are VERY interested in the code and the model behind it, please read the DETAILED.md file.

This branch is used to test and analise the situation of the aglutination of individuals in the model. If you want to run the program and see the results, follow the instructions below

## How to compile

To compile this code you may have to install some programs before. See [instalation](#install) for more information.

The simplest way is with make.

```bash
$ make
```
If you want the exec files deleted, type
```bash
$ make clean
```

## Installation <a name="install"></a>

First, install Gnu Scientific Library

~~~bash
$ sudo apt update
$ sudo apt install libgsl-dev
~~~

Here's how to install make

```bash
$ sudo apt install build.essentials
```

To compile the R scripts you may need to install R, here is a tutorial: https://cran.r-project.org/, but if you don't want the graphics, you won't need R.

## Situation

The program works perfectly for G >= 1500, but it still lacks interface.

Currently, I am updating the documentation. Some functions are missing and the function's descriptions are poor.

In this branch I'm trying to keep changes when the simulation is in the middle so it wont be time wasted if the simulation is incomplete.
It is lacking the parts where I specify if it's from the beginning or the middle, and I need to save the parameters separatedly, so I can review it and take it to start the simulation again

## References

DE AGUIAR, Marcus Aloizo Martinez et al. Global patterns of speciation and diversity. **Nature**, v. 460, n. 7253, p. 384-387, 2009.
