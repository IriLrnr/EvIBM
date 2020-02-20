# EvIBM
IC

##How to compile
~~~bash
$ gcc main.c -o out
$ ./out
~~~
###With make
After cloning the folder, go in it and compile with the command
~~~bash
$ make
~~~
If you need, here's how to install make
~~~bash
$ sudo apt install build.essentials
~~~
After cloning the folder, go in it and compile with the command
~~~bash
$ make
~~~

CHANGING PROBABILITY OF OFFSPRING MOVEMENT

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




TO VISUALIZE WHAT IS HAPPENING I NEED GIFS OF THE FOLLOWING PROCESSES:

 - The collapse with different probabilities of movement
 - The final plot for those different simulations
 - Discover wich parameters change distribution and plot varying them

 To do that, I need to learn GNU plot. Of automatization of the R plot. But how??

 WHERE I STOPPED
 	I was varying the probability of movement in "Offspring_position" and plotting in R the first 10 generations (to see if the collapse is early) and the last one. I found ont weird patterns for the final distribution, and some but not complete correlation with this value and the problem of the collapse. I want to make gifs to show Fla and Carlinhos whats going on. 


 ALTERATIONS SUGGESTED BY FLÁVIA

 	- Mortalidade 37% - mimetização de sorteio com reposição
 	- INDIVIDUOS COM DENSIDADE BAIXA - TIRAR MORTALIDADE

 	I think I didn't understand what I have to change to test...

 	ficou bem zoado tirando o loop para substituir o parceiro

 	Dúvida: quando eu devo sortear uma nova posição, durante a resposição, para um individuo?

Suggestions by PhD Candidate Juan
 	- Ident input arguments in functions (code styler/ formater)
 	- 

