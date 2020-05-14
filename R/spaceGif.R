# Load the libraries
library(gapminder)
library(ggplot2)
library(gganimate)
library(stringr)
library(gifski)
library(png)

# Catch table with location values
ind.loc <- read.csv(file = "./data/position/indlocV0_pmates.csv", sep = ";")

# Find the needed number of frames, the last value of the data frame
x <- ind.loc[,1]
ngen <- ind.loc[length(x), 5]
ngen

# Set the space size
max.space=100

# Plot every dot in ind.loc in a ggplot
individuals.fig <- 
  ggplot() +  
  geom_point(data = ind.loc, aes(x = x, y = y, color = factor(sp)), size=1.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y="") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(), 
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))

# animate the ggplot to become a gif
anim <- individuals.fig + 
  transition_time(gen) + ggtitle("Generation {frame}")

anim

# save gif
anim_save("complete_position_pmates.gif", animate(anim, nframes=ngen, height=450, width=550), path = "./gifs")
