library (gridExtra)

source("./R/comparative_tests.R")
source("./R/comparative_tests_marcus.R")

comparative <- grid.arrange(spp.mu, spp.mu.m, spp.g, spp.g.m, spp.p, spp.p.m, spp.b, spp.b.m, ncol = 2)
comparative2 <- grid.arrange(mu.fig, mu.fig.m, g.fig, g.fig.m, rho.fig, rho.fig.m, B.fig, B.fig.m, ncol = 2)

ggsave("./figs/test/comparative/comparative1.png", comparative)
ggsave("./figs/test/comparative/comparative2.png", comparative2)
