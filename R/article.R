library(gridExtra)

source ("./R/func_and_def.R")

# species diameter
distance.info <- tibble()
f = 5
dist <- read.csv(paste0("./data/sizes_tests/", f, "/100/distances/distances_01.csv"), header = T, sep = ";")
#dist <- cbind(dist[,-1], rep(f, nrow(dist)))
#colnames(dist)[4] <- "variable"
distance.info <- rbind(distance.info, dist)

diameter_boxplot <- ggplot(distance.info) +
  geom_boxplot(aes(x=as.factor(spp), y=d, color=as.factor(spp))) +
  theme_bw() +
  theme.all +
  theme(legend.position = "none")
diameter_boxplot
# dg x ds
R = c(5, 10, 15, 20, 30, 40, 50)
R = 5
for (r in R) {
  dgxds <- plot.dgxds(r)
  dgxds <- dgxds + ggtitle(paste("S =", r))
  ggsave(paste0("./figs/sizes/dgxds_", r, ".png"), dgxds)
}
dgxds

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

