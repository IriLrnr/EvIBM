# Load the libraries
library(ggplot2)
library(gridExtra)
library(RColorBrewer)

# Read data
ind.loc <- read.csv(file = "./indloc_00.csv", head = TRUE, sep = ";")

loc.data <- data.frame()
max.space=100
breaks <- seq(1, 1000, by = 50)

fig1 <- ggplot() +
  geom_point(data = subset(ind.loc, gen == 0), aes(x = x, y = y,color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 0")

fig2 <- ggplot() +
  geom_point(data = subset(ind.loc, gen == 200), aes(x = x, y = y,color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw() +
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 200")

fig3 <- ggplot() +  
  geom_point(data = subset(ind.loc, gen == 400), aes(x = x, y = y,color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 400")

fig4 <- ggplot() +  
  geom_point(data = subset(ind.loc, gen == 600), aes(x = x, y = y,color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 600")

fig5 <- ggplot() +
  geom_point(data = subset(ind.loc, gen == 800), aes(x = x, y = y,color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 800")

fig6 <- ggplot() +  
  geom_point(data = subset(ind.loc, gen == 1000), aes(x = x, y = y,color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 1000")

fig7 <- ggplot() +  
  geom_point(data = subset(ind.loc, gen == 1200), aes(x = x, y = y,color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 1200")

fig8 <- ggplot() +  
  geom_point(data = subset(ind.loc, gen == 1400), aes(x = x, y = y,color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 1400")

fig9 <- ggplot() +  
  geom_point(data = subset(ind.loc, gen == 1600), 
                          aes(x = x, y = y, color= factor(sp)), 
                          size=0.5, alpha=0.5, 
                          show.legend = FALSE) +
  guides(fill=FALSE, shape="none") +
  labs(x = "", y = "") +  
  xlim(0, 100) +
  ylim(0, 100) +
  theme_bw()+
  theme(text = element_text(size=7, family="Helvetica"),
        panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
        plot.margin = unit(c(0,1,0,0), "cm"))+
  ggtitle("geração 1600")

position <- grid.arrange(fig1, fig2, fig3, fig4, fig5, fig6, fig7, fig8, fig9, ncol = 3)

#ggsave("./figs/base/position.png", position, height = 6, width = 7)
