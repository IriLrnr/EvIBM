# Load the libraries'
library(ggplot2)

setwd("./data/species/v1")
file.names <- dir()

number.spp=data.frame()

for (i in 1:length(file.names)){
  dados=read.csv(paste(file.names[i]), head=TRUE, sep=";")
  number.spp=rbind(number.spp, dados)
}
setwd("../../../")

colnames(number.spp)=c("gen","sp", "singles", "sim")

# Read data
nuber.spp <- as.numeric(c(1, 2, 3))

# Define limits for the graph
max.spp <- max(number.spp[,2])
max.time <- max(number.spp[,1])

number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
sumario <- do.call (data.frame, number.data)
singles <- number.spp[,3]

number.fig <-
  ggplot() +  
  geom_point(data = subset(number.spp), aes(x = gen, y = sp), size=0.5, color="orange", alpha=0.3)+
  geom_line(data = subset(sumario), aes(x = gen, y = sp.mn), size=0.5, color="orangered3")+
  geom_ribbon(data = subset(sumario), aes(x = gen, ymin=sp.mn-sp.sd, ymax=sp.mn+sp.sd),alpha=0.3, color = "darkorange2")+
  geom_line(data = subset(sumario), aes(x = gen, y = singles.mn), color = "darkred", size = 0.5) +
  guides(fill=FALSE, shape="none") +
  labs(x = "generation", y = "Number of species") +  
  xlim(0, max.time) +
  ylim(0, max.spp) +
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

number.fig
ggsave("./figs/species/nspp_v1.png")

