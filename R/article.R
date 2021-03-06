source ("./R/functions.R")

g <- 300

# Diameters x S
dxS <- diameter.vs.radius.complete(g)
dxS
ggsave(paste0("./figs/sizes/diameter/diameter_s25_", g, ".png"), dxS)

# spp x S
spxS <- sp.vs.radius.complete()
spxS
ggsave(paste0("./figs/sizes/diameter/spp_s25_", g, ".png"), spxS)

#regression
reg <- regression.S(g)
reg
ggsave(paste0("./figs/sizes/diameter/regression_", g, ".png"), reg)

# estamos organizados até aqui!

# species diameter
R <- c(5, 10, 15, 20, 30, 40, 50)
diameter.boxplot(R, g) # automatizar o diametro em uma lista de ggplots?

# Plot species x time
L = c(100, 120, 150, 180, 220, 200, 250, 300, 350)
L.plot <- plot.L.parameter(create.L.tbl(L), "L")
ggsave("./figs/sizes/sizes_spp.png", L.plot)

# Equilibrium time
eq.times <- equilibration.times (L)

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

  # Grouping analysis - see if 4 times N=1000 is equivalent to one 4000

# between 4 * 1000 and 4000

for (i in 1:n) {
  hist <- grid.arrange(sizes.histogram.compare(100, g[i], c[i], 4) + ylim(0,0.1),
                       sizes.histogram.compare(200, g[i], c[i], 1) + ylim(0,0.1),
                       ncol = 2, top=(paste("generation", g[i])))
  ggsave(paste0("./figs/sizes/compared/hist_compare_1x4_", g[i], ".png"), hist, height = 3.5)
}
compared.Lplot_1x4 <- compare.L.parameter(c(100, 200), c(4,1))
ggsave("./figs/sizes/compared/nspp_compared_1x4.png", compared.Lplot_1x4)

for (i in 1:n) {
  hist <- grid.arrange(sizes.histogram.compare(100, g[i], c[i], 9) + ylim(0,0.1),
                       sizes.histogram.compare(300, g[i], c[i], 1) + ylim(0,0.1),
                       ncol = 2, top=(paste("generation", g[i])))
  ggsave(paste0("./figs/sizes/compared/hist_compare_1x9_", g[i], ".png"), hist, height = 3.5)
}
compared.Lplot_1x9 <- compare.L.parameter(c(100, 300), c(9,1))
ggsave("./figs/sizes/compared/nspp_compared_1x9.png", compared.Lplot_1x9)

for (i in 1:n) {
  hist <- grid.arrange(sizes.histogram.compare(100, g[i], c[i], 12) + ylim(0,0.1),
                       sizes.histogram.compare(350, g[i], c[i], 1) + ylim(0,0.1),
                       ncol = 2, top=(paste("generation", g[i])))
  ggsave(paste0("./figs/sizes/compared/hist_compare_1x12_", g[i], ".png"), hist, height = 3.5)
}
compared.Lplot_1x12 <- compare.L.parameter(c(100, 350), c(12,1))
ggsave("./figs/sizes/compared/nspp_compared_1x12.png", compared.Lplot_1x12)



######### temp #############

# Example:
x=rep(seq(1,20),10)
y=rnorm(length(x),x, rep(2,length(x)))
plot(y~x)
lin.reg = lm(y~x) #linear regression
sum.lin.reg=summary(lin.reg)

sum.lin.reg$coefficients[1] # intercept
sum.lin.reg$coefficients[2] # slope
sum.lin.reg$adj.r.squared   #adjusted R-squared

