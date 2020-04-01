# Load the libraries
library(ggplot2)

# Read data
number.spp <- read.csv(file ="./data/species/numspV2_4.csv", head = TRUE, sep=";")

# Define limits for the 
max.spp <- max(number.spp[,2])
max.time <- max(number.spp[,1])

number.fig <-
  ggplot() +  
  geom_point(data = subset(number.spp), aes(x = gen, y = sp), size=1.5, color="darkgreen", alpha=0.3)+
  guides(fill=FALSE, shape="none") +
  labs(x = "Generation", y="Number of species") +  
  xlim(0, max.time) +
  ylim(0, max.spp) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.5,1.5,0.1,0.1), "cm"))

ggsave("./figs/species/number_spp_V2_4.png", number.fig, width=5.5, height=4.5)

