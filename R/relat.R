source ("./R/func_and_def.R")

## Species comparison ##
compare.spp <- plot.parameter(perf.tbl, "B", "B")
compare.spp

perf.150.tbl <- create.B.tbl(150)
comp.150 <- plot.B.parameter(perf.150.tbl, "versão")
comp.150

perf.1500.tbl <- create.B.tbl(1500)
comp.1500 <- plot.B.parameter(perf.1500.tbl, "versão")
comp.1500

perf.15000.tbl <- create.B.tbl(15000)
comp.15000 <- plot.B.parameter(perf.15000.tbl, "versão")
comp.15000

perf.150000.tbl <- create.B.tbl(150000)
comp.150000 <- plot.B.parameter(perf.150000.tbl, "versão")
comp.150000

#### PERFORMANCE COMPARISON ######
comp.boxplot <- PerformanceBoxplot()
comp.boxplot 
ggsave ("./figs/performance_J.png", comp.boxplot)

##### G ######
spp.g.tbl <- create.tbl ((1:10), "g")
spp.g <- plot.parameter (spp.g.tbl, "g", "G (%)") 
spp.g 
#g.fig <- weird.plot (spp.g.tbl, "g", "Distância genética")
#g.fig

##### MU ######
spp.mu.tbl <- create.tbl ((1:7), "mu")
spp.mu <- plot.parameter (spp.mu.tbl, "mu", "mu x 100")
spp.mu

#mu.fig <- weird.plot (spp.mu.tbl, "mu", "Taxa de mutação")
#mu.fig

##### RHO ######
spp.rho.tbl <- create.tbl ((7:15), "rho")
spp.rho <- plot.parameter (spp.rho.tbl, "rho", "pop/100")
spp.rho

#mu.fig <- weird.plot (spp.rho.tbl, "rho", "Tamanho da população")
#mu.fig

##### B falta acabar ######
spp.b.tbl <- create.tbl (c(150, 1500), "B")
spp.b <- plot.parameter (spp.b.tbl, "B", "Tamanho do Genoma")
spp.b

#b.fig <- weird.plot (spp.b.tbl, "B", "Tamanho do genoma")
#b.fig

## Species comparison ##
perf.tbl <- create.tbl.pt (c(150, 1500), "B")
perf.tbl2 <- create.tbl.pt(c(15000), "B")
