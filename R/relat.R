library(gridExtra)

source ("./R/func_and_def.R")

## Compare stabilization time ##
stabfig <- StabTimePlot (create.stab.tbl(10))+
stabfig
ggsave("./figs/relat/TempoEquilib_R.png", stabfig, width = 6, height = 4)

## Species comparison ##
comp.150 <- plot.B.parameter(create.B.tbl(150))
comp.150 <- comp.150 + ggtitle("(A) B = 150") + theme(legend.position = "none", axis.title.x = element_blank())
comp.1500 <- plot.B.parameter(create.B.tbl(1500))
comp.1500 <- comp.1500 + ggtitle("(B) B = 1500") + theme(legend.position = "none", axis.title.y = element_blank(), axis.title.x = element_blank())
comp.15000 <- plot.B.parameter(create.B.tbl(15000))
comp.15000 <- comp.15000 + ggtitle("(C) B = 15000") + theme(legend.position = "none")
comp.150000 <- plot.B.parameter(create.B.tbl(150000))
comp.150000 <- comp.150000 + ggtitle("(D) B = 150000") + theme(axis.title.y = element_blank())
series.comp <- grid.arrange(comp.150, comp.1500, comp.15000, comp.150000, ncol = 2)
ggsave("./figs/relat/series_comp.png", series.comp)

#### PERFORMANCE COMPARISON ######
comp.boxplot <- PerformancePlot() + theme(axis.title = element_text(size = 10))
comp.boxplot 
ggsave ("./figs/relat/performance_J.png", comp.boxplot)

##### G ######
spp.g <- plot.parameter (create.tbl ((1:10), "g"), "g", "g (%)") 
spp.g <- spp.g + ggtitle("B")
spp.g
#g.fig <- weird.plot (spp.g.tbl, "g", "Distância genética")
##### MU ######
spp.mu <- plot.parameter (create.tbl ((1:10), "mu"), "mu", expression(paste(mu, "*1000")))
spp.mu <- spp.mu + ggtitle("A")
spp.mu
#mu.fig <- weird.plot (spp.mu.tbl, "mu", "Taxa de mutação")
##### RHO ######
spp.rho <- plot.parameter (create.tbl ((7:15), "rho"), "rho", "pop/100")
spp.rho <- spp.rho + coord_cartesian(ylim = c(0,30)) + ggtitle("C")
#rho.fig <- weird.plot (spp.rho.tbl, "rho", "Tamanho da população")
##### B  ######
spp.b <- plot.parameter (create.tbl (c(150, 1500, 15000), "B"), "B", "B")
spp.b <- spp.b + coord_cartesian(ylim = c(0,32)) + ggtitle("D")
#b.fig <- weird.plot (spp.b.tbl, "B", "Tamanho do genoma")
tests <- grid.arrange(spp.mu, spp.g, spp.rho, spp.b)
ggsave("./figs/relat/tests.png", tests, width = 8, height = 6)

## ESPAÇO ## colocar geração 0, 100, 300, 500
ind.loc <- read.csv(file = "./data/test_cp/B/150/indloc_00.csv", head = TRUE, sep = ";")
ind.loc <- ind.loc[,-c(4, 5)]
s0 <- SpacePlot(ind.loc, 0)
s100 <- SpacePlot(ind.loc, 200)
s300 <- SpacePlot(ind.loc, 400)
s500 <- SpacePlot(ind.loc, 800)
space <- grid.arrange(s0, s100, s300, s500, ncol = 2)
ggsave ("./figs/relat/space.png", space, width=4, height=3.2)
