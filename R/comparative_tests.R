library(ggplot2)
library(dplyr)
library(RColorBrewer)
library(reshape2)

setwd("./data/test_cp")
## Quero fazer um gráfico que compara as curvas médias com varias cores
getwd()
setwd("./g")
spp.mn.g <- tibble(.rows = 201)
for(f in 1:10){
  setwd(paste0("./", f, "/species"))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.csv(paste(file.names[i]), head=TRUE, sep=";")
    number.spp <- rbind(number.spp, dados)
  }
  setwd("../../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.g <- cbind(spp.mn.g, sumario$sp.mn)
}
setwd("../")

colnames(spp.mn.g) <- seq(1,10,1)
spp.mn.g <- cbind(sumario$gen, spp.mn.g)
colnames(spp.mn.g)[1] <- c("gen")

melted <- melt(spp.mn.g, c("gen"))

spp.g <- ggplot(melted, aes(x=gen, y=value, group=variable, colour=factor(variable))) + 
        geom_line() +
        labs (x = "Geração", y = "Número de espécies", color = "g (%)") +
        theme_bw() +
        theme(text = element_text(size=12, family="Helvetica"),
               panel.grid.minor = element_blank(),
               panel.grid.major = element_blank(),
               legend.position = c(1.10,0.365),
               legend.text=element_text(size=5),
               legend.margin = margin(-4, 4, -1, -1),
               plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))
spp.g <- spp.g + ggtitle("Especies x tempo para diferentes valores de g")
ggsave("../../figs/test/comparative/allsp_g.png", spp.g)

melted.gen <- subset(melted, gen%%200 == 0)
g.fig <- ggplot(melted.gen, aes(x=variable, y=value, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() +
  labs (x = "Distância genética (%)", y = "Número de espécies", color = "geração") +
  theme_bw() +
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),
        panel.grid.major = element_blank(),
        #legend.position = c(1.10,0.365),
        #legend.text=element_text(size=5),
        #legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))
g.fig <- g.fig + ggtitle("Número de especies x distância genética")
ggsave("../../figs/test/comparative/gxn.png", g.fig)

### MU

getwd()
setwd("./mu")
spp.mn.mu <- tibble(.rows = 201)
for(f in 1:9){
  setwd(paste0("./", f, "/species"))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.csv(paste(file.names[i]), head=TRUE, sep=";")
    number.spp <- rbind(number.spp, dados)
  }
  setwd("../../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.mu <- cbind(spp.mn.mu, sumario$sp.mn)
}
setwd("../")

colnames(spp.mn.mu) <- seq(1,9,1)
spp.mn.mu <- cbind(sumario$gen, spp.mn.mu)
colnames(spp.mn.mu)[1] <- c("gen")

melted <- melt(spp.mn.mu, c("gen"))
spp.mu <- ggplot(melted, aes(x=gen, y=value, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = expression(mu*10^3)) +
  theme_bw() +
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),
        panel.grid.major = element_blank(), 
        legend.position = c(1.10,0.365),
        legend.text=element_text(size=5),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))
spp.mu <- spp.mu + ggtitle(paste("Especies x tempo para diferentes valores de mu"))
spp.mu
ggsave("../../figs/test/comparative/allsp_mu.png", spp.mu)

melted.gen <- subset(melted, gen%%200 == 0)
mu.fig <- ggplot(melted.gen, aes(x=variable, y=value, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() +
  labs (x = expression(mu*10^3), y = "Número de espécies", color = "geração") +
  theme_bw() +
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),
        panel.grid.major = element_blank(),
        #legend.position = c(1.10,0.365),
        #legend.text=element_text(size=5),
        #legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))
mu.fig <- mu.fig + ggtitle("Número de espécies x mutação")
ggsave("../../figs/test/comparative/muxn.png", mu.fig)

### RHO

getwd()
setwd("./rho")
spp.mn.p <- tibble(.rows = 201)
for(f in 7:14){
  setwd(paste0("./", f, "/species"))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.csv(paste(file.names[i]), head=TRUE, sep=";")
    number.spp <- rbind(number.spp, dados)
  }
  setwd("../../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.p <- cbind(spp.mn.p, sumario$sp.mn)
}
setwd("../")

colnames(spp.mn.p) <- seq(7,14,1)
spp.mn.p <- cbind(sumario$gen, spp.mn.p)
colnames(spp.mn.p)[1] <- c("gen")

melted <- melt(spp.mn.p, c("gen"))

spp.p <- ggplot(melted, aes(x=gen, y=value, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = "Pop/100") +
  theme_bw() +
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),
        panel.grid.major = element_blank(), 
        legend.title = element_text("Rho", size = 8),
        legend.position = c(1.10,0.365),
        legend.text=element_text(size=5),
        legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))


spp.p <- spp.p + ggtitle(paste("Especies x tempo para diferentes valores de rho"))

spp.p
ggsave("../../figs/test/comparative/allsp_rho.png", spp.p)

melted.gen <- subset(melted, gen%%200 == 0)
rho.fig <- ggplot(melted.gen, aes(x=variable, y=value, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() +
  labs (x = "População (pop/100) ", y = "Número de espécies", color = "geração") +
  theme_bw() +
  theme(text = element_text(size=12, family="Helvetica"),
        panel.grid.minor = element_blank(),
        panel.grid.major = element_blank(),
        #legend.position = c(1.10,0.365),
        #legend.text=element_text(size=5),
        #legend.margin = margin(-4, 4, -1, -1),
        plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))
rho.fig <- rho.fig + ggtitle("Número de espécies x densidade")
ggsave("../../figs/test/comparative/rhoxn.png", rho.fig)

getwd()
setwd("../../")


