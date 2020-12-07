library(gridExtra)

source ("./R/func_and_def.R")

# Plot species x time
L = c(120, 150, 180, 220, 200, 250, 300, 350)
L.plot <- plot.L.parameter(create.L.tbl(L), "L")
ggsave("./figs/sizes/sizes_spp.png", L.plot)

# Plot sizes histogram
legend <- get.legend(sizes.histogram(120))
hists <- grid.arrange(sizes.histogram(120) + theme(legend.position = "none"), 
                      sizes.histogram(150) + theme(legend.position = "none"), 
                      sizes.histogram(180) + theme(legend.position = "none"),
                      sizes.histogram(200) + theme(legend.position = "none"),
                      sizes.histogram(220) + theme(legend.position = "none"),
                      sizes.histogram(250) + theme(legend.position = "none"),
                      sizes.histogram(300) + theme(legend.position = "none"),
                      sizes.histogram(350) + theme(legend.position = "none"), 
                      ncol = 2)
ggsave("./figs/sizes/sizes.histogram.png", hists)
ggsave("./figs/sizes/hist_subt.png", legend)
