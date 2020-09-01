library(ggplot2)
library(dplyr)
library(RColorBrewer)
library(reshape2)
library(viridis)

theme.all <- theme(text = element_text(size=10, family="Helvetica"),
                   panel.grid.minor = element_blank(),
                   panel.grid.major = element_blank(),
                   legend.text=element_text(size=8),
                   legend.margin = margin(-4, 4, -1, -1),
                   plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))


plot.parameter <- function (spp.info, type, legend) {
  spp.info <- subset(spp.info, as.numeric(spp.info$variable)%%2 == 0, c(1, 2, 3, 4))
  spp.info$variable <- as.factor(spp.info$variable)
  spp <- ggplot(spp.info) +
    geom_ribbon(aes(x = gen, ymin=sp.mn-sp.sd, ymax=sp.mn+sp.sd, group=variable, fill=variable), alpha = 0.25, show.legend=F) +
    geom_line (aes(x=gen, y=sp.mn, group=variable, colour=variable)) +
    scale_alpha(guide = 'none') +
    scale_color_viridis_d() +
    scale_fill_viridis_d() +
    labs (x = "Geração", y = "Número de espécies", color = legend) +
    theme_bw() +
    #theme (legend.title = element_text(legend)) +
    theme.all
  #ggsave(paste0("./figs/report/spp_", type, ".png"), spp)
  return (spp)
}

plot.B.parameter <- function (spp.info, legend) {
  #spp.info <- subset(spp.info, as.numeric(spp.info$variable)%%2 == 0, c(1, 2, 3, 4))
  spp.info$variable <- as.factor(spp.info$variable)
  spp <- ggplot(spp.info) +
    geom_ribbon(aes(x = gen, ymin=sp.mn-sp.sd, ymax=sp.mn+sp.sd, group=variable, fill=variable), alpha = 0.25, show.legend=F) +
    geom_line (aes(x=gen, y=sp.mn, group=variable, colour=variable)) +
    scale_alpha(guide = 'none') +
    scale_color_viridis_d() +
    scale_fill_viridis_d() +
    labs (x = "Geração", y = "Número de espécies", color = legend) +
    theme_bw() +
    #theme (legend.title = element_text(legend)) +
    theme.all
  #ggsave(paste0("./figs/report/spp_", type, ".png"), spp)
  return (spp)
}


weird.plot <- function (spp.info, type, legend) {
  spp.info <- subset (spp.info, spp.info$gen%%400 == 0)
  spp.info <- subset (spp.info, spp.info$gen != 0)
  
  fig <- ggplot(spp.info, aes(x=as.factor(variable), y=sp.mn, group = gen, color = factor(gen))) + 
    geom_point() + geom_line() + geom_errorbar(aes(ymin = sp.mn-sp.sd, ymax = sp.mn+sp.sd), width = 0.2) + 
    #scale_x_discrete(labels=seq(1,10,by=1)) +
    labs (x = legend, y = "Número de espécies", color = "geração") +
    scale_color_viridis_d() + 
    theme_bw() +
    theme.all
  #ggsave(paste0("./figs/report/", type, "_fig.png"), spp)
  return (fig)
}

create.tbl <- function (interval, type) {
  spp.tbl <- tibble()
  for(f in interval) {
    file.names <- paste0("./data/test_cp/", type, "/", f, "/species/", dir(paste0("./data/test_cp/", type, "/", f, "/species/"))[])
    number.spp <- do.call(rbind, lapply(file.names, FUN = read.csv, head = T, sep=";"))
    
    # Read data
    number.spp <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
    sumario <- cbind(do.call (data.frame, number.spp[,-3]), rep(f, 2001))
    colnames(sumario)[4] = "variable"
    spp.tbl <- rbind(spp.tbl, sumario)
  }
  return (spp.tbl)
}

create.B.tbl <- function (B) {
  spp.tbl <- tibble()
  versions <- c("not_optimized", "genomic_lists", "Union_Find")
  
  for(v in versions) {
    file.names <- paste0("./data/performance_tests/B/", v, "/", B, "/species/", dir(paste0("./data/performance_tests/B/", v, "/", B, "/species/")))
    number.spp <- do.call(rbind, lapply(file.names, FUN = read.csv, head = T, sep=";"))
    
    # Read data
    number.spp <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
    sumario <- cbind(do.call (data.frame, number.spp[,-3]), rep(v, nrow(number.spp)))
    colnames(sumario)[4] = "variable"
    spp.tbl <- rbind(spp.tbl, sumario)
  }
  return (spp.tbl)
}

PerformanceBoxplot <- function () {
  genomes <- c(150, 1500, 15000)
  versions <- c("not_optimized", "genomic_lists", "Union_Find")
  
  df <- data.frame()
  for (v in versions) {
    files.path <- paste0("./data/performance_tests/B/", v, "/performance_", genomes, ".txt")
    list <- lapply(files.path, FUN = read.table, sep = ";", header = T)
    names(list) <- genomes
    temp <- do.call(rbind,list)
    temp$name <- rep(names(list),times=sapply(list,nrow))
    version <- rep(v, nrow(temp))
    temp <- cbind(version, temp)
    df <- rbind (df, temp)
  }
  
  #df$real = as.difftime(df$real)
  df$usr = as.numeric(df$usr)
  df$sys = as.numeric(df$sys)
  
  fig <- ggplot(df, aes(x = name, y = log(usr+sys), color = version)) +
    #geom_boxplot(outlier.shape=16, outlier.size=2, notch=FALSE) +
    geom_jitter(aes(color=version),position = position_jitter(width = .2)) +
    scale_color_brewer(palette = "Dark2") +
    #scale_fill_viridis_d() +
    labs (x = "Tamanho do genoma B", y = "Tempo (log(usr + sys))", color ="versão") +
    theme_bw()+
    theme.all 
  fig <- fig +
  return (fig)
}
