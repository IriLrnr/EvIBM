# Load the libraries
library(ggplot2)
library(gridExtra)

# read the csv files for distribution
dis.twentyfivepc <- read.csv("./data/position/indlocV3_25.csv", sep = ";")
dis.fiftypc <- read.csv("./data/position/indlocV3_50.csv", sep = ";")
dis.seventyfivepc <- read.csv("./data/position/indlocV3_75.csv", sep = ";")
dis.hundredpc <- read.csv("./data/position/indlocV3_100.csv", sep = ";")

# create each individual image
individuals.fig.twentyfive <- 
  ggplot() +  
  geom_point(data = subset(dis.twentyfivepc), aes(x = x, y = y, color = factor(sp)), size=0.2, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y="") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(), 
        plot.margin = unit(c(0.1,1,0.1,0.1), "cm"), 
        plot.title = element_text(size = 10)) +
  ggtitle("Dispersal rate 25%")

individuals.fig.fifty <- 
  ggplot() +  
  geom_point(data = dis.fiftypc, aes(x = x, y = y, color = factor(sp)), size=0.2, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y="") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(), 
        plot.margin = unit(c(0.1,1,0.1,0.1), "cm"), 
        plot.title = element_text(size = 10)) +
  ggtitle("Dispersal rate 50%")

individuals.fig.seventyfive <- 
  ggplot() +  
  geom_point(data = dis.seventyfivepc, aes(x = x, y = y, color = factor(sp)), size=0.2, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y="") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(), 
        plot.margin = unit(c(0.1,1,0.1,0.1), "cm"), 
        plot.title = element_text(size = 10)) +
  ggtitle("Dispersal rate 75%")

individuals.fig.hundred <- 
  ggplot() +  
  geom_point(data = dis.hundredpc, aes(x = x, y = y, color = factor(sp)), size=0.2, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y="") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(), 
        plot.margin = unit(c(0.1,1,0.1,0.1), "cm"), 
        plot.title = element_text(size = 10)) +
  ggtitle("Dispersal rate 100%")

multi <- grid.arrange(individuals.fig.twentyfive, individuals.fig.fifty, individuals.fig.seventyfive, individuals.fig.hundred, nrow = 2)

# Create the multiple image
ggsave("./figs/position/final_distribution_V3_multi.png", multi, width=5.5, height=4.5)


# read the csv files for number of species
nsp.twentyfivepc <- read.csv("./data/species/numspV3_25.csv", sep = ";")
nsp.fiftypc <- read.csv("./data/species/numspV3_50.csv", sep = ";")
nsp.seventyfivepc <- read.csv("./data/species/numspV3_75.csv", sep = ";")
nsp.hundredpc <- read.csv("./data/species/numspV3_100.csv", sep = ";")

number.fig.twentyfive <-
  ggplot() +  
  geom_point(data = subset(nsp.twentyfivepc), aes(x = gen, y = sp), size=0.2, color="darkgreen", alpha=0.3)+
  guides(fill=FALSE, shape="none") +
  labs(x = "Generation", y="Number of species") +  
  xlim(0, nrow(nsp.twentyfivepc)) +
  ylim(0, 20) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.5,1,0.1,0.1), "cm"), 
        plot.title = element_text(size = 10),
        axis.title.x = element_text(size = 7),
        axis.title.y = element_text(size = 7)) +
  ggtitle("Dispersal rate 25%")

number.fig.fifty <-
  ggplot() +  
  geom_point(data = subset(nsp.fiftypc), aes(x = gen, y = sp), size=0.2, color="turquoise", alpha=0.3)+
  guides(fill=FALSE, shape="none") +
  labs(x = "Generation", y="Number of species") +  
  xlim(0, nrow(nsp.fiftypc)) +
  ylim(0, 80) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.5,1,0.1,0.1), "cm"), 
        plot.title = element_text(size = 10),
        axis.title.x = element_text(size = 7),
        axis.title.y = element_text(size = 7)) +
  ggtitle("Dispersal rate 50%")

number.fig.seventyfive <-
  ggplot() +  
  geom_point(data = subset(nsp.seventyfivepc), aes(x = gen, y = sp), size=0.2, color="orange", alpha=0.3)+
  guides(fill=FALSE, shape="none") +
  labs(x = "Generation", y="Number of species") +  
  xlim(0, nrow(nsp.seventyfivepc)) +
  ylim(0, 80) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.5,1,0.1,0.1), "cm"), 
        plot.title = element_text(size = 10),
        axis.title.x = element_text(size = 7),
        axis.title.y = element_text(size = 7)) +
  ggtitle("Dispersal rate 75%")

number.fig.hundred <-
  ggplot() +  
  geom_point(data = subset(nsp.hundredpc), aes(x = gen, y = sp), size=0.2, color="deeppink", alpha=0.3)+
  guides(fill=FALSE, shape="none") +
  labs(x = "Generation", y="Number of species") +  
  xlim(0, nrow(nsp.hundredpc)) +
  ylim(0, 80) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.5,1,0.1,0.1), "cm"), 
        plot.title = element_text(size = 10),
        axis.title.x = element_text(size = 7),
        axis.title.y = element_text(size = 7)) +
  ggtitle("Dispersal rate 100%")

multisp <- grid.arrange(number.fig.twentyfive, number.fig.fifty, number.fig.seventyfive, number.fig.hundred, nrow = 2)

ggsave("./figs/species/number_spp_V3_multi.png", multisp, width=5.5, height=4.5)

