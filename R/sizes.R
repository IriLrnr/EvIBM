# Load the libraries'
library(ggplot2)

setwd("./data/sizes")
file.names <- dir()

pop.info <- data.frame()

for (i in 1:length(file.names)){
  dados <- read.csv(paste(file.names[i]), head=TRUE, sep=";")
  pop.info <- rbind(pop.info, dados)
}
setwd("../../")

breaks <- seq(1, 1000, 1)
g = 500

sizes.hist <- ggplot(subset(pop.info, gen == g), aes(x = size)) +
  geom_histogram(color = "black", fill = "lightseagreen", breaks = breaks) +
  guides(fill=FALSE, shape="none") +
  labs(x = "size", y = "") +  
  xlim(0, 200) +
  ggtitle(paste("Species size in generation", g)) +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),
        panel.grid.major = element_blank(), 
        legend.title=element_blank(),
        legend.position = c(1.12,0.365), 
        #legend.background = element_rect(fill="transparent",size=0.01, linetype="solid",colour ="orange"),
        #legend.key = element_rect(fill = "transparent", colour = "transparent"),
        legend.text=element_text(size=5),
        legend.box.background = element_rect(),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))


sizes.hist
ggsave()
