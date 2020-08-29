library (gridExtra)
library(reshape)

source ("./R/func_and_def.R")

##### G ######
spp.g.tbl <- create.tbl ((1:10), "g")

spp.half <- subset(spp.g.tbl, as.numeric(spp.g.tbl$variable)%%2 == 0, c(1, 2, 3, 4))
pal = "Dark2"
spp.g <- plot.parameter (spp.half, "g", "G (%)", pal) 
spp.g 

spp.gen <- subset (spp.g.tbl, spp.g.tbl$gen%%400 == 0)
spp.gen <- subset (spp.gen, spp.gen$gen != 0)
pal = "Set1"
g.fig <- weird.plot (spp.gen, "g", "Distância genética", pal)
g.fig

##### MU ######
spp.mu.tbl <- create.tbl ((1:5), "mu")

spp.half <- subset(spp.mu.tbl, as.numeric(spp.mu.tbl$variable)%%2 == 0, c(1, 2, 3, 4))
pal = "Dark2"
spp.mu <- plot.parameter (spp.mu.tbl, "mu", "mu x 100", pal)
spp.mu

spp.gen <- subset (spp.mu.tbl, spp.mu.tbl$gen%%400 == 0)
spp.gen <- subset (spp.gen, spp.gen$gen != 0)
mu.fig <- weird.plot (spp.gen, "mu", "Taxa de mutação", pal)
mu.fig

##### RHO ######
spp.rho.tbl <- create.tbl ((7:15), "rho")

spp.half <- subset(spp.rho.tbl, as.numeric(spp.rho.tbl$variable)%%2 == 0, c(1, 2, 3, 4))
spp.rho <- plot.parameter (spp.rho.tbl, "rho", "pop/100", pal)
spp.rho

spp.gen <- subset (spp.rho.tbl, spp.rho.tbl$gen%%400 == 0)
spp.gen <- subset (spp.gen, spp.gen$gen != 0)
mu.fig <- weird.plot (spp.gen, "rho", "Tamanho da população", pal)
mu.fig

##### B ######
spp.b.tbl <- create.tbl (c(150, 1500), "B")


spp.half <- subset(spp.b.tbl, as.numeric(spp.b.tbl$variable)%%2 == 0, c(1, 2, 3, 4))
spp.b <- plot.parameter (spp.b.tbl, "B", "Tamanho do Genoma", pal)
spp.b

spp.gen <- subset (spp.b.tbl, spp.b.tbl$gen%%400 == 0)
spp.gen <- subset (spp.gen, spp.gen$gen != 0)
b.fig <- weird.plot (spp.gen, "B", "Tamanho do genoma", pal)
b.fig


#### PERFORMANCE COMPARISON
genomes = c(150, 1500, 15000)

files.path <- paste0("./data/performance_tests/B/done/correct!/validation/performance_", genomes, ".txt")
no.opt <- lapply(files.path, FUN = read.table, sep = ";", header = T)

files.path <- paste0("./data/performance_tests/B/done/correct!/binomial_mut/performance_", genomes, ".txt")
opt.1 <- lapply(files.path, FUN = read.table, sep = ";", header = T)

data.no.opt <- cbind (rep(150, 20), no.opt[[1]])
colnames(data.no.opt)[1] <- c("id")
data.no.opt <- melt (data.no.opt, id.vars = c("id"))

p.150 <- ggplot(melt(data.no.opt, id.vars = c("id")), aes(factor(variable), value)) +
    geom_boxplot() + facet_wrap(~variable, scale="free")
p.150
