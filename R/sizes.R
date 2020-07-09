library(RColorBrewer)

setwd("./sizes")
file.names <- dir()

pop.info <- data.frame()

for (i in 1:length(file.names)){
  dados <- read.csv(paste(file.names[i]), head=TRUE, sep=";")
  pop.info <- rbind(pop.info, dados)
}
setwd("../")

breaks <- seq(1, 1000, 2)
g = 500

pop.info.gen <- subset(pop.info, gen%%200 == 0, select = c("gen", "size"))
gens <- seq(0, 2000, 200)

myPalette <- colorRampPalette(rev(brewer.pal(11, "Spectral")))
sc <- scale_fill_gradientn(colours = myPalette(100), limits=c(0, 2000))

sizes.hist <- ggplot(pop.info, aes(x = size, fill = gen)) +
  geom_histogram(data = subset(pop.info, gen==0), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==200), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==400), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==600), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==800), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1000), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1200), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1400), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1600), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1800), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==2000), breaks = breaks, position = "dodge") +
  sc +
  labs(x = "size", y = "") +  
  xlim(0, 1000) +
  ggtitle("Species sizes in different generations") +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),
        panel.grid.major = element_blank(), 
        legend.title=element_text("geração", size = 8),
        legend.position = c(1.10,0.365),
        legend.text=element_text(size=5),
        #legend.box.background = element_rect(),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))


sizes.hist

sizes.hist.200 <- ggplot(pop.info, aes(x = size, fill = gen)) +
  geom_histogram(data = subset(pop.info, gen==0), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==200), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==400), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==600), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==800), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1000), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1200), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1400), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1600), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==1800), breaks = breaks, position = "dodge") +
  geom_histogram(data = subset(pop.info, gen==2000), breaks = breaks, position = "dodge") +
  sc +
  labs(x = "size", y = "") +  
  xlim(0, 200) +
  ggtitle("Species sizes in different generations") +
  theme_bw()+
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),
        panel.grid.major = element_blank(), 
        legend.title=element_text("geração", size = 8),
        legend.position = c(1.10,0.365),
        legend.text=element_text(size=5),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))

sizes.hist.200

#ggsave(sizes.hist, "./figs/base/histogram.png")
