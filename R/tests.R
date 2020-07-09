library(ggplot2)
options(scipen = 999)
setwd("./data/test_cp")
######################### B tests #####################################
setwd("./B")
Bs <- c("1500")
for (b in Bs) {
  setwd(paste0("./", b))
  color.sp <- c("skyblue1", "slateblue4", "turquoise3", "steelblue4")
  source("~/EvIBM/R/species.R")
  number.fig <- number.fig + ggtitle(paste("Genoma", b))
  ggsave(paste0("~/EvIBM/figs/test/B/nspp_B", b, ".png"), number.fig)
  source("~/EvIBM/R/sizes.R")
  sizes.hist <- sizes.hist + ggtitle(paste("Tamanho das espécies para genoma", b))
  sizes.hist.200 <- sizes.hist.200 + ggtitle(paste("Tamanho das espécies para genoma", b, "zoom"))
  ggsave(paste0("~/EvIBM/figs/test/B/sizes_B", b, ".png"), sizes.hist)
  ggsave(paste0("~/EvIBM/figs/test/B/sizes_zoom_B", b, ".png"), sizes.hist)
  title = paste("Genoma", b)
  source("~/EvIBM/R/space.R")
  ggsave(paste0("~/EvIBM/figs/test/B/position_B", b, ".png"), position, height = 6.2, width = 7)
  setwd("../")
}
setwd("../")
#######################################################################

######################### MU tests #####################################
setwd("./mu")
mu <- seq(0.0001, 0.001, 0.0001)
for (m in 1:length(mu)) {
  setwd(paste0("./", m))
  color.sp <- c("thistle3", "darkorchid4", "darkorchid", "plum3")
  source("~/EvIBM/R/species.R")
  number.fig <- number.fig + ggtitle(paste("Mutação", mu[m]))
  ggsave(paste0("~/EvIBM/figs/test/mu//nspp_mu", mu[m], ".png"), number.fig)
  source("~/EvIBM/R/sizes.R")
  sizes.hist <- sizes.hist + ggtitle(paste("Tamanho das espécies para mu", mu[m]))
  sizes.hist.200 <- sizes.hist.200 + ggtitle(paste("Tamanho das espécies para mu", mu[m], "zoom"))
  ggsave(paste0("~/EvIBM/figs/test/mu/sizes_mu", mu[m], ".png"), sizes.hist)
  ggsave(paste0("~/EvIBM/figs/test/mu/sizes_zoom_mu", mu[m], ".png"), sizes.hist)
  title = paste("Mutação", mu[m])
  source("~/EvIBM/R/space.R")
  ggsave(paste0("~/EvIBM/figs/test/mu/position_mu", mu[m], ".png"), position, height = 6.2, width = 7)
  setwd("../")
}
setwd("../")
#######################################################################

######################### G tests #####################################
setwd("./g")
Gs <- seq(0.001, 0.01, 0.001)
for (dg in 1:length(Gs)) {
  setwd(paste0("./", dg))
  color.sp <- c("greenyellow", "green4", "olivedrab1", "lightgreen")
  source("~/EvIBM/R/species.R")
  number.fig <- number.fig + ggtitle(paste("Distância Reprodutiva", Gs[dg]))
  ggsave(paste0("~/EvIBM/figs/test/g/nspp_g", Gs[dg], ".png"), number.fig)
  source("~/EvIBM/R/sizes.R")
  sizes.hist + ggtitle(paste("Tamanho das espécies para G", Gs[dg]))
  sizes.hist.200 + ggtitle(paste("Tamanho das espécies para G", Gs[dg], "zoom"))
  ggsave(paste0("~/EvIBM/figs/test/g/sizes_g", Gs[dg], ".png"), sizes.hist)
  ggsave(paste0("~/EvIBM/figs/test/g/sizes_zoom_g", Gs[dg], ".png"), sizes.hist)
  title = paste("Distância Genética", Gs[dg])
  source("~/EvIBM/R/space.R")
  ggsave(paste0("~/EvIBM/figs/test/g/position_g", Gs[dg], ".png"), position, height = 6.2, width = 7)
  setwd("../")
}
setwd("../")
#######################################################################

######################### rho tests #####################################
setwd("./rho")
rho <- seq(7, 14, 1)
for (p in rho) {
  setwd(paste0("./", p))
  color.sp <- c("salmon", "indianred4", "red1", "indianred1")
  source("~/EvIBM/R/species.R")
  number.fig
  number.fig <- number.fig + ggtitle(paste("Population", p))
  ggsave(paste0("~/EvIBM/figs/test/rho/nspp_rho", p, ".png"), number.fig)
  source("~/EvIBM/R/sizes.R")
  sizes.hist <- sizes.hist + ggtitle(paste("Tamanho das espécies para população", p))
  sizes.hist.200 <- sizes.hist.200 + ggtitle(paste("Tamanho das espécies para população", p, "zoom"))
  ggsave(paste0("~/EvIBM/figs/test/rho/sizes_p", p, ".png"), sizes.hist)
  ggsave(paste0("~/EvIBM/figs/test/g/sizes_zoom_p", p, ".png"), sizes.hist)
  title = paste("População", p)
  source("~/EvIBM/R/space.R")
  ggsave(paste0("~/EvIBM/figs/test/rho/position_rho", p, ".png"), position, height = 6.2, width = 7)
  setwd("../")
}
setwd("../")
#######################################################################