library(ggplot2)
library(dplyr)
library(RColorBrewer)
library(reshape2)

theme.all <- theme(text = element_text(size=8, family="Helvetica"),
                   panel.grid.minor = element_blank(),
                   panel.grid.major = element_blank(),
                   legend.position = "none",
                   #legend.text=element_text(size=4),
                   #legend.margin = margin(-4, 4, -1, -1),
                   plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))

setwd("./data/test_cp/")
##### G ######
getwd()
setwd("./g")
folders <- dir()
glim <- length(folders) - 1
spp.mn.g <- tibble(.rows = 2001)
spp.sd.g <- tibble(.rows = 2001)
for(f in 1:glim){
  setwd(paste0("./", f, "/species"))
  file.names <- dir()
  
  number.spp <- data.frame()
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
  spp.sd.g <- cbind(spp.sd.g, sumario$sp.sd)
}
setwd("../")

colnames(spp.mn.g) <- seq(1,glim,1)
colnames(spp.sd.g) <- seq(1,glim,1)
spp.mn.g <- cbind(sumario$gen, spp.mn.g)
spp.sd.g <- cbind(sumario$gen, spp.sd.g)

colnames(spp.mn.g)[1] <- c("gen")
colnames(spp.sd.g)[1] <- c("gen")

melted <- melt(spp.mn.g, c("gen"))
melted2 <- melt(spp.sd.g, c("gen"))

melted <- cbind(melted, melted2$value)
colnames(melted)[3] <- c("sp")
colnames(melted)[4] <- c("sd")

spp.g <- ggplot(melted, aes(x=gen, y=sp, group=variable, colour=factor(variable))) + 
        geom_line() +
        labs (x = "Geração", y = "Número de espécies", color = "g (%)") +
        theme_bw() +
        theme.all
spp.g
#spp.g <- spp.g + ggtitle("Especies x tempo para diferentes valores de g")
#ggsave("../../figs/test/comparative/allsp_g.png", spp.g)

melted.gen <- subset(melted, gen%%500 == 0)
g.fig <- ggplot(melted.gen, aes(x=variable, y=sp, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() + geom_errorbar(aes(ymin = sp-sd, ymax = sp+sd), width = 0.2) + 
  labs (x = "Distância genética (%)", y = "Número de espécies", color = "geração") +
  theme_bw() +
  theme.all
g.fig
#g.fig <- g.fig + ggtitle("Número de especies x distância genética")
#ggsave("../../figs/test/comparative/gxn.png", g.fig)

###### MU ########

getwd()
setwd("./mu")
folders <- dir()
mulim <- length(folders)
spp.mn.mu <- tibble(.rows = 2001)
spp.sd.mu <- tibble(.rows = 2001)
for(f in 1:mulim){
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
  spp.sd.mu <- cbind(spp.sd.mu, sumario$sp.sd)
}
setwd("../")

colnames(spp.mn.mu) <- seq(1,mulim,1)
colnames(spp.sd.mu) <- seq(1,mulim,1)
spp.mn.mu <- cbind(sumario$gen, spp.mn.mu)
spp.sd.mu <- cbind(sumario$gen, spp.sd.mu)
colnames(spp.mn.mu)[1] <- c("gen")
colnames(spp.sd.mu)[1] <- c("gen")

melted <- melt(spp.mn.mu, c("gen"))
melted2 <- melt(spp.sd.mu, c("gen"))

melted <- cbind(melted, melted2$value)
colnames(melted)[3] <- c("sp")
colnames(melted)[4] <- c("sd")

spp.mu <- ggplot(melted, aes(x=gen, y=sp, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = expression(mu*10^3)) +
  theme_bw() +
  theme.all
#spp.mu <- spp.mu + ggtitle(paste("Especies x tempo para diferentes valores de mu"))
spp.mu
#ggsave("../../figs/test/comparative/allsp_mu.png", spp.mu)

melted.gen <- subset(melted, gen%%400 == 0)
mu.fig <- ggplot(melted.gen, aes(x=variable, y=sp, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() + geom_errorbar(aes(ymin = sp-sd, ymax = sp+sd), width = 0.2) + 
  labs (x = expression(mu*10^3), y = "Número de espécies", color = "geração") +
  theme_bw() +
  theme.all
mu.fig
#mu.fig <- mu.fig + ggtitle("Número de espécies x mutação")
#ggsave("../../figs/test/comparative/muxn.png", mu.fig)

###### RHO ########
getwd()
setwd("./rho")
folders <- dir()
rholim <- length(folders) - 1 + 7
spp.mn.p <- tibble(.rows = 2001)
spp.sd.p <- tibble(.rows = 2001)
for(f in 7:rholim){
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
  spp.sd.p <- cbind(spp.sd.p, sumario$sp.sd)
}
setwd("../")

colnames(spp.mn.p) <- seq(7,rholim,1)
colnames(spp.sd.p) <- seq(7,rholim,1)
spp.mn.p <- cbind(sumario$gen, spp.mn.p)
spp.sd.p <- cbind(sumario$gen, spp.sd.p)
colnames(spp.mn.p)[1] <- c("gen")
colnames(spp.sd.p)[1] <- c("gen")

melted <- melt(spp.mn.p, c("gen"))
melted2 <- melt(spp.sd.p, c("gen"))

melted <- cbind(melted, melted2$value)
colnames(melted)[3] <- c("sp")
colnames(melted)[4] <- c("sd")

spp.p <- ggplot(melted, aes(x=gen, y=sp, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = "Pop/100") +
  theme_bw() +
  theme.all
#spp.p <- spp.p + ggtitle(paste("Especies x tempo para diferentes valores de rho"))
spp.p
#ggsave("../../figs/test/comparative/allsp_rho.png", spp.p)

melted.gen <- subset(melted, gen%%400 == 0)
rho.fig <- ggplot(melted.gen, aes(x=variable, y=sp, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() + geom_errorbar(aes(ymin = sp-sd, ymax = sp+sd), width = 0.2) +
  labs (x = "População (pop/100) ", y = "Número de espécies", color = "geração") +
  theme_bw() +
  theme.all
#rho.fig <- rho.fig + ggtitle("Número de espécies x densidade")
rho.fig
#ggsave("../../figs/test/comparative/rhoxn.png", rho.fig)

######## B ######
getwd()
setwd("./B")
spp.mn.b <- tibble(.rows = 1001)
spp.sd.b <- tibble(.rows = 1001)
bvec <- as.vector(dir())
for(f in bvec[1:3]){
  setwd(paste0("./", f, "/species"))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.csv(paste(file.names[i]), head=TRUE, sep=";")
    number.spp <- rbind(number.spp, dados[1:1001,])
  }
  setwd("../../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.b <- cbind(spp.mn.b, sumario$sp.mn)
  spp.sd.b <- cbind(spp.sd.b, sumario$sp.sd)
}
setwd("../")

colnames(spp.mn.b) <- c(150)
colnames(spp.sd.b) <- c(150)
spp.mn.b <- cbind(sumario$gen, spp.mn.b)
spp.sd.b <- cbind(sumario$gen, spp.sd.b)
colnames(spp.mn.b)[1] <- c("gen")
colnames(spp.sd.b)[1] <- c("gen")

melted <- melt(spp.mn.b, c("gen"))
melted2 <- melt(spp.sd.b, c("gen"))

melted <- cbind(melted, melted2$value)
colnames(melted)[3] <- c("sp")
colnames(melted)[4] <- c("sd")

spp.b <- ggplot(melted, aes(x=gen, y=sp, group=variable, colour=factor(variable))) + 
  geom_line() +
  labs (x = "Geração", y = "Número de espécies", color = "B") +
  theme_bw() +
  theme.all
#spp.b <- spp.b + ggtitle(paste("Especies x tempo para diferentes valores de B"))
spp.b
#ggsave("../../figs/test/comparative/allsp_B.png", spp.b)

melted.gen <- subset(melted, gen%%400 == 0)
B.fig <- ggplot(melted.gen, aes(x=variable, y=sp, group = gen, color = factor(gen))) + 
  geom_point() + geom_line() + geom_errorbar(aes(ymin = sp-sd, ymax = sp+sd), width = 0.2)  +
  labs (x = "Tamanho do genoma", y = "Número de espécies", color = "geração") +
  theme_bw() +
  theme.all
#B.fig <- B.fig + ggtitle("Número de espécies x tamanho do genoma")
B.fig
#ggsave("../../figs/test/comparative/Bxn.png", B.fig)

setwd("../../")


