# EvIBM
IC

I added mortality to low-density individuals, but it didn't help (even got worse). The individuals are collapsing.

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



I think I got wrong the reproduction. Variation in the movement of the offspring shows that the collapse isn't dependent of it, but it changes the pattern of the collapse. Is always stabilizes at a number of species, and the smaller the probability of movement, the bigger is the number of species.


TO VISUALIZE WHAT IS HAPPENING I NEED GIFS OF THE FOLLOWING PROCESSES:

 - The collapse with different probabilities of movement
 - The final plot for those different simulations
 - Discover wich parameters change distribution and plot varying them

 To do that, I need to learn GNU plot. Of automatization of the R plot. But how??

 WHERE I STOPPED
 	I was varying the probability of movement in "Offspring_position" and plotting in R the first 10 generations (to see if the collapse is early) and the last one. I found ont weird patterns for the final distribution, and some but not complete correlation with this value and the problem of the collapse. I want to make gifs to show Fla and Carlinhos whats going on. 