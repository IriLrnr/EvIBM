library(gridExtra)

source ("./R/func_and_def.R")

# Histograms
c <- brewer.pal(9, "Set1")
g <- seq(200, 1000, 100)

for (i in 1:9) {
  hist <- grid.arrange(sizes.histogram(120, g[i], c[i]), 
                           sizes.histogram(150, g[i], c[i]),
                           sizes.histogram(180, g[i], c[i]),
                           sizes.histogram(200, g[i], c[i]),
                           sizes.histogram(220, g[i], c[i]), 
                           sizes.histogram(250, g[i], c[i]),
                           sizes.histogram(300, g[i], c[i]),
                           sizes.histogram(350, g[i], c[i]),
                           name = paste("generation", g[i]),
                           ncol = 2)
  ggsave(paste0("./figs/sizes/hist_", g[i], ".png"), hist)
}

# I still need to re-simulate everything saving sizes each 20 gen. Up to gen 600
# Also need equilibrium time calc 

c <- "darkgoldenrod2"
g <- 300
hist.g300<- grid.arrange(sizes.histogram(120, g, c), 
                         sizes.histogram(150, g, c),
                         sizes.histogram(180, g, c),
                         sizes.histogram(200, g, c),
                         sizes.histogram(220, g, c), 
                         sizes.histogram(250, g, c),
                         sizes.histogram(300, g, c),
                         sizes.histogram(350, g, c),
                         name = paste("generation", g),
                         ncol = 2)


c <- brewer.pal(9, "Set1")

g <- 300
hist.g300<- grid.arrange(sizes.histogram(120, g, c), 
                         sizes.histogram(150, g, c),
                         sizes.histogram(180, g, c),
                         sizes.histogram(200, g, c),
                         sizes.histogram(220, g, c), 
                         sizes.histogram(250, g, c),
                         sizes.histogram(300, g, c),
                         sizes.histogram(350, g, c),
                         ncol = 2)



1# Plot species x time
L = c(120, 150, 180, 220, 200, 250, 300, 350)
L.plot <- plot.L.parameter(create.L.tbl(L), "L")
ggsave("./figs/sizes/sizes_spp.png", L.plot)
