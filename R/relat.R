source ("./R/func_and_def.R")

##### G ######
spp.g.tbl <- create.tbl ((1:10), "g")

spp.half <- subset(spp.g.tbl, as.numeric(spp.g.tbl$variable)%%2 == 0, c(1, 2, 3, 4))
spp.g <- plot.parameter (spp.half, "g", "G (%)")
spp.g

spp.gen <- subset (spp.g.tbl, spp.g.tbl$gen%%200 == 0)
spp.gen <- subset (spp.gen, spp.gen$gen != 0)
g.fig <- weird.plot (spp.gen, "g", "Distância genética")
g.fig

##### MU ######
spp.mu.tbl <- create.tbl ((1:5), "mu")

spp.half <- subset(spp.mu.tbl, as.numeric(spp.mu.tbl$variable)%%2 == 0, c(1, 2, 3, 4))
spp.mu <- plot.parameter (spp.mu.tbl, "mu", "mu x 100")
spp.mu

spp.gen <- subset (spp.mu.tbl, spp.mu.tbl$gen%%200 == 0)
spp.gen <- subset (spp.gen, spp.gen$gen != 0)
mu.fig <- weird.plot (spp.gen, "mu", "Taxa de mutação")
mu.fig

##### RHO ######
spp.rho.tbl <- create.tbl ((7:15), "rho")

spp.half <- subset(spp.rho.tbl, as.numeric(spp.rho.tbl$variable)%%2 == 0, c(1, 2, 3, 4))
spp.rho <- plot.parameter (spp.rho.tbl, "rho", "pop/100")
spp.rho

spp.gen <- subset (spp.rho.tbl, spp.rho.tbl$gen%%200 == 0)
spp.gen <- subset (spp.gen, spp.gen$gen != 0)
mu.fig <- weird.plot (spp.gen, "rho", "Tamanho da população")
mu.fig

##### B ######
spp.b.tbl <- create.tbl (c(150, 1500), "B")

spp.half <- subset(spp.b.tbl, as.numeric(spp.b.tbl$variable)%%2 == 0, c(1, 2, 3, 4))
spp.b <- plot.parameter (spp.b.tbl, "B", "Tamanho do Genoma")
spp.b

spp.gen <- subset (spp.rho.tbl, spp.rho.tbl$gen%%200 == 0)
spp.gen <- subset (spp.gen, spp.gen$gen != 0)
mu.fig <- weird.plot (spp.gen, "rho", "Tamanho da população")
mu.fig
