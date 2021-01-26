library(gridExtra)

source ("./R/func_and_def.R")

# Histograms
n <- 21
qual_col_pals = brewer.pal.info[brewer.pal.info$category == 'qual',]
c = unlist(mapply(brewer.pal, qual_col_pals$maxcolors, rownames(qual_col_pals)))

g <- seq(100, 500, 20)

for (i in 1:n) {
  hist <- grid.arrange(sizes.histogram(100, g[i], c[i]),
                           sizes.histogram(120, g[i], c[i]), 
                           sizes.histogram(150, g[i], c[i]),
                           sizes.histogram(180, g[i], c[i]),
                           sizes.histogram(200, g[i], c[i]),
                           sizes.histogram(220, g[i], c[i]), 
                           sizes.histogram(250, g[i], c[i]),
                           sizes.histogram(300, g[i], c[i]),
                           sizes.histogram(350, g[i], c[i]),
                           ncol = 3, top=(paste("generation", g[i])))
  ggsave(paste0("./figs/sizes/hist_ln_", g[i], ".png"), hist, height = 6)
}

# Plot species x time
L = c(100, 120, 150, 180, 220, 200, 250, 300, 350)
L.plot <- plot.L.parameter(create.L.tbl(L), "L")
ggsave("./figs/sizes/sizes_spp.png", L.plot)

# Equilibrium time
eq.times <- equilibration.times (L)
