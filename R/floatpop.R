# Load the libraries
library(ggplot2)

# Read data
float.pop <- read.csv(file ="./data/fluctuation/floatpopV3.csv", head = TRUE, sep=";")

# plot
max.x <- nrow(float.pop)
max.y <- max(float.pop[,2])
min.y <- min(float.pop[,2])

float.fig <-
  ggplot() +  
  geom_line(data = subset(float.pop), aes(x = gen, y = size), size=0.5, color="darkgoldenrod2", alpha=0.6)+
  guides(fill=FALSE, shape="none") +
  labs(x = "Generation", y="Population size") +  
  xlim(0, max.x) +
  ylim(min.y, max.y) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.5,1.5,0.1,0.1), "cm"))

float.fig

ggsave("./figs/fluctuation/float_pop_V3.png", float.fig, width=5.5, height=4.5)
