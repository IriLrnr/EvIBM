library(ggplot2)
library(dplyr)
library(RColorBrewer)
library(reshape2)

theme.all <- theme(text = element_text(size=8, family="Helvetica"),
                   panel.grid.minor = element_blank(),
                   panel.grid.major = element_blank(),
                   #legend.position = c(1.10,0.365),
                   legend.position = "none",
                   #legend.text=element_text(size=4),
                   #legend.margin = margin(-4, 4, -1, -1),
                   plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))

setwd("./data/marcus_data")
##### G ######
getwd()
setwd("./g")
spp.mn.g <- tibble(.rows = 200)
spp.sd.g <- tibble(.rows = 200)
for(f in 1:10){
  setwd(paste0("./", f))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.table(paste(file.names[i]), head=F)
    colnames(dados) <- c("gen", "spp")
    number.spp <- rbind(number.spp, dados)
  }
  setwd("../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.g <- cbind(spp.mn.g, sumario$spp.mn)
  spp.sd.g <- cbind(spp.sd.g, sumario$spp.sd)
}
setwd("../")

colnames(spp.mn.g) <- seq(1,10,1)
colnames(spp.sd.g) <- seq(1,10,1)
spp.mn.g <- cbind(sumario$gen, spp.mn.g)
spp.sd.g <- cbind(sumario$gen, spp.sd.g)

colnames(spp.mn.g)[1] <- c("gen")
colnames(spp.sd.g)[1] <- c("gen")

melted <- melt(spp.mn.g, c("gen"))
melted2 <- melt(spp.sd.g, c("gen"))

melted <- cbind(melted, melted2$value)
colnames(melted)[3] <- c("sp")
colnames(melted)[4] <- c("sd")

spp.g.m <- ggplot(melted, aes(x=gen, y=sp, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = "g (%)") +
  scale_color_brewer(name = "g(%)", palette = "Set1") +
  theme_bw() +
  theme.all
#spp.g.m <- spp.g.m + ggtitle("Especies x tempo para diferentes valores de g")
spp.g.m
#ggsave("../../figs/test/comparative/MARCUSallsp_g.png", spp.g.m)

melted.gen <- subset(melted, gen%%400 == 0)
g.fig.m <- ggplot(melted.gen, aes(x=variable, y=sp, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() + geom_errorbar(aes(ymin = sp-sd, ymax = sp+sd), width = 0.2) + 
  labs (x = "Distância genética (%)", y = "Número de espécies", color = "geração") +
  scale_color_brewer(name= "geração", palette = "Set1") +
  theme_bw() +
  theme.all
g.fig.m
#g.fig.m <- g.fig.m + ggtitle("Número de especies x distância genética")
#ggsave("../../figs/test/comparative/MARCUSgxn.png", g.fig.m)

###### MU ########
getwd()
setwd("./mu")
spp.mn.mu <- tibble(.rows = 200)
spp.sd.mu <- tibble(.rows = 200)
for(f in 1:10){
  setwd(paste0("./", f))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.table(paste(file.names[i]), head=F)
    colnames(dados) <- c("gen", "spp")
    number.spp <- rbind(number.spp, dados)
  }
  setwd("../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.mu <- cbind(spp.mn.mu, sumario$spp.mn)
  spp.sd.mu <- cbind(spp.sd.mu, sumario$spp.sd)
}
setwd("../")

colnames(spp.mn.mu) <- seq(1,10,1)
colnames(spp.sd.mu) <- seq(1,10,1)
spp.mn.mu <- cbind(sumario$gen, spp.mn.mu)
spp.sd.mu <- cbind(sumario$gen, spp.sd.mu)
colnames(spp.mn.mu)[1] <- c("gen")
colnames(spp.sd.mu)[1] <- c("gen")

melted <- melt(spp.mn.mu, c("gen"))
melted2 <- melt(spp.sd.mu, c("gen"))

melted <- cbind(melted, melted2$value)
colnames(melted)[3] <- c("sp")
colnames(melted)[4] <- c("sd")

spp.mu.m <- ggplot(melted, aes(x=gen, y=sp, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = "mu*1000") +
  scale_color_brewer(name = expression(mu*10^3), palette = "Set1") +
  theme_bw() +
  theme.all
#spp.mu.m <- spp.mu.m + ggtitle(paste("Especies x tempo para diferentes valores de mu"))
spp.mu.m
#ggsave("../../figs/test/comparative/MARCUSallsp_mu.png", spp.mu.m)

melted.gen <- subset(melted, gen%%400 == 0)
mu.fig.m <- ggplot(melted.gen, aes(x=variable, y=sp, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() + geom_errorbar(aes(ymin = sp-sd, ymax = sp+sd), width = 0.2) + 
  labs (x = expression(mu*10^3), y = "Número de espécies", color = "geração") +
  scale_color_brewer(name = "geração", palette = "Set1") +
  theme_bw() +
  theme.all
#mu.fig.m <- mu.fig.m + ggtitle("Número de espécies x mutação")
mu.fig.m
#ggsave("../../figs/test/comparative/MARCUSmuxn.png", mu.fig.m)

###### RHO ########
getwd()
setwd("./rho")
spp.mn.p <- tibble(.rows = 200)
spp.sd.p <- tibble(.rows = 200)
for(f in 7:15){
  setwd(paste0("./", f))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.table(paste(file.names[i]), head=F)
    colnames(dados) <- c("gen", "spp")
    number.spp <- rbind(number.spp, dados)
  }
  setwd("../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.p <- cbind(spp.mn.p, sumario$spp.mn)
  spp.sd.p <- cbind(spp.sd.p, sumario$spp.sd)
}
setwd("../")

colnames(spp.mn.p) <- seq(7,15,1)
colnames(spp.sd.p) <- seq(7,15,1)
spp.mn.p <- cbind(sumario$gen, spp.mn.p)
spp.sd.p <- cbind(sumario$gen, spp.sd.p)
colnames(spp.mn.p)[1] <- c("gen")
colnames(spp.sd.p)[1] <- c("gen")

melted <- melt(spp.mn.p, c("gen"))
melted2 <- melt(spp.sd.p, c("gen"))

melted <- cbind(melted, melted2$value)
colnames(melted)[3] <- c("sp")
colnames(melted)[4] <- c("sd")

spp.p.m <- ggplot(melted, aes(x=gen, y=sp, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = "Pop/100") +
  scale_color_brewer(name = "pop/100", palette = "Set1") +
  theme_bw() +
  theme.all
#spp.p.m <- spp.p.m + ggtitle(paste("Especies x tempo para diferentes valores de rho"))
spp.p.m
#ggsave("../../figs/test/comparative/MARCUSallsp_rho.png", spp.p.m)

melted.gen <- subset(melted, gen%%400 == 0)
rho.fig.m <- ggplot(melted.gen, aes(x=variable, y=sp, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() + geom_errorbar(aes(ymin = sp-sd, ymax = sp+sd), width = 0.2) + 
  labs (x = "População (pop/100) ", y = "Número de espécies", color = "geração") +
  scale_color_brewer(name = "geração", palette = "Set1") +
  theme_bw() +
  theme.all
#rho.fig.m <- rho.fig.m + ggtitle("Número de espécies x densidade")
rho.fig.m
#ggsave("../../figs/test/comparative/rhoxn.png", rho.fig.m)

######## B ######
getwd()
setwd("./B")
spp.mn.b <- tibble(.rows = 100)
spp.sd.b <- tibble(.rows = 100)
bvec <- c(150, 1500)
for(f in bvec){
  setwd(paste0("./", f))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.table(paste(file.names[i]), head=F)
    colnames(dados) <- c("gen", "spp")
    number.spp <- rbind(number.spp, dados)
  }
  setwd("../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.b <- cbind(spp.mn.b, sumario$spp.mn)
  spp.sd.b <- cbind(spp.sd.b, sumario$spp.sd)
}
setwd("../")

colnames(spp.mn.b) <- c(150, 1500)
colnames(spp.sd.b) <- c(150, 1500)
spp.mn.b <- cbind(sumario$gen, spp.mn.b)
spp.sd.b <- cbind(sumario$gen, spp.sd.b)
colnames(spp.mn.b)[1] <- c("gen")
colnames(spp.sd.b)[1] <- c("gen")

melted <- melt(spp.mn.b, c("gen"))
melted2 <- melt(spp.sd.b, c("gen"))

melted <- cbind(melted, melted2$value)
colnames(melted)[3] <- c("sp")
colnames(melted)[4] <- c("sd")

spp.b.m <- ggplot(melted, aes(x=gen, y=sp, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = "B") +
  scale_color_brewer(name= "genoma", palette = "Set1") +
  theme_bw() +
  theme.all
#spp.b.m <- spp.b.m + ggtitle(paste("Especies x tempo para diferentes valores de B"))
spp.b.m
#ggsave("../../figs/test/comparative/MARCUSallsp_B.png", spp.b.m)

melted.gen <- subset(melted, gen%%400 == 0)
B.fig.m <- ggplot(melted.gen, aes(x=variable, y=sp, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() + geom_errorbar(aes(ymin = sp-sd, ymax = sp+sd), width = 0.2) + 
  labs (x = "Tamanho do genoma", y = "Número de espécies", color = "geração") +
  scale_color_brewer(name = "geração", palette = "Set1") +
  theme_bw() +
  theme.all
#B.fig.m <- B.fig.m + ggtitle("Número de espécies x tamanho do genoma")
B.fig.m
#ggsave("../../figs/test/comparative/MARCUSBxn.png", B.fig.m)

setwd("../../")
