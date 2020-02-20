library(ggplot2)
library(stringr)

# Set directory to a folder that stores the output of the program (the folder must contain only .csv files) 
setwd("/home/irinalerner/EvIBM/position") 
file.names=dir()

file.names
ind.loc=data.frame()

for (i in 1:length(file.names)){
  data.loc=read.csv(paste(file.names[i]), head=FALSE, sep=";")
  data.loc=cbind(data.loc,rep(i,dim(data.loc)[1])) # indexing time as a sequence of 1 to the number of files of individuals locations
  ind.loc=rbind(ind.loc, data.loc)
}

data.loc

colnames(ind.loc)=c("id","x","y","sp","time")
ind.loc
max.space=100

for (i in 1:length(file.names)) {
  individuals.fig=
    ggplot() +  
    geom_point(data = subset(ind.loc, time == i), aes(x = x, y = y,color= factor(sp)), size=1.5, alpha=0.5)+
    guides(fill=FALSE, shape="none") +
    labs(x = "", y="") +  
    xlim(0, 100) +
    ylim(0, 100) +
    theme_bw()+
    theme(text = element_text(size=12, family="Helvetica"),
          panel.grid.minor = element_blank(),panel.grid.major = element_blank(), 
          legend.title=element_blank(),
          legend.position = c(1.12,0.365), 
          legend.background = element_rect(fill="transparent",size=0.01, linetype="solid",colour ="black"),
          legend.key = element_rect(fill = "transparent", colour = "transparent"),
          legend.text=element_text(size=5),
          legend.box.background = element_rect(),
          legend.margin = margin(-4, 4, -1, -1),
          plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))
  
  individuals.fig
  # Set here to a place to save the images
  ggsave(paste("/home/irinalerner/EvIBM/plots/offsMove001_ind_location_aa-", str_pad(i, 4, pad="0"), ".png", sep = ""), individuals.fig,width=6, height=5)
}
# Para fazer o gif, acesse a pasta das imagens pelo terminal, e digite
# $ convert -monitor *.png out.gif
# Para visualizar, baixe sxiv
# $ sudo apt sxiv
# $ sxiv out.gif