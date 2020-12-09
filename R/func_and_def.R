library(ggplot2)
library(dplyr)
library(RColorBrewer)
library(reshape2)
library(viridis)

theme.all <- theme(text = element_text(size=10, family="Helvetica"),
                   panel.grid.minor = element_blank(),
                   panel.grid.major = element_blank(),
                   title = element_text(size = 9),
                   legend.text=element_text(size=9),
                   legend.margin = margin(-1, 1, -1, -1),
                   plot.margin = unit(c(0.1,0.5,0.1,0.1), "cm"))

versions <- c("V0", "V1", "V2")
genomes <- c(150, 1500, 15000, 150000)

create.tbl <- function (interval, type) {
  spp.tbl <- tibble()
  sumario <- tibble()
  for(f in interval) {
    file.names <- paste0("./data/test_cp/", type, "/", f, "/species/", dir(paste0("./data/test_cp/", type, "/", f, "/species/"))[])
    number.spp <- do.call(rbind, lapply(file.names, FUN = read.csv, head = T, sep=";"))
    
    # Read data
    number.spp <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
    sumario <- cbind(do.call (data.frame, number.spp[,-3]), rep(f, nrow(number.spp)))
    colnames(sumario)[4] = "variable"
    spp.tbl <- rbind(spp.tbl, sumario)
  }
  return (spp.tbl)
}

plot.parameter <- function (spp.info, type, legend) {
  #spp.info <- subset(spp.info, as.numeric(spp.info$variable)%%2 == 0, c(1, 2, 3, 4))
  spp.info$variable <- as.factor(spp.info$variable)
  spp <- ggplot(spp.info) +
    geom_ribbon(aes(x = gen, ymin=(sp.mn-sp.sd), ymax=sp.mn+sp.sd, group=variable, fill=variable), alpha = 0.25, show.legend=F) +
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

create.B.tbl <- function (B) {
  spp.tbl <- tibble()
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

plot.B.parameter <- function (spp.info) {
  spp.info$variable <- as.factor(spp.info$variable)
  spp <- ggplot(spp.info) +
    geom_ribbon(aes(x = gen, ymin=sp.mn-sp.sd, ymax=sp.mn+sp.sd, group=variable, fill=variable), alpha = 0.25, show.legend=F) +
    geom_line (aes(x=gen, y=sp.mn, group=variable, colour=variable)) +
    scale_alpha(guide = 'none') +
    ylim(0,35)+
    scale_color_brewer(palette = "Dark2") +
    scale_fill_brewer(palette = "Dark2") +
    labs (x = "Geração", y = "Número de espécies", color = "Versão") +
    theme_bw() +
    #theme (legend.title = element_text(legend)) +
    theme.all
  #ggsave(paste0("./figs/report/spp_", type, ".png"), spp)
  return (spp)
}

PerformancePlot <- function () {
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
    geom_jitter(aes(color=version),position = position_jitter(width = 0.3), size = 0.7) +
    scale_color_brewer(palette = "Dark2") +
    #scale_fill_viridis_d() +
    labs (x = "Tamanho do genoma", y = "Tempo de processamento em CPU (log(usr+sys))", color ="Versão") +
    theme_bw()+
    theme.all 
  fig <- fig +
    return (fig)
}

create.stab.tbl <- function (ngen) {
  gs <- genomes
  all.eq.time <- tibble()
  for (g in gs) {
    eq.times <- tibble()
    for(v in versions) {
      file.names <- paste0("./data/performance_tests/B/", v, "/", g, "/species/", dir(paste0("./data/performance_tests/B/", v, "/", g, "/species/")))
      files <- lapply(file.names, FUN = read.csv, head = T, sep=";")
      gen <- files[[1]]$gen
      files <- lapply(files, FUN = select, c("sp"))
      number.spp <- do.call(cbind, files)
      colnames(number.spp) <- seq(1:length(files))
      #number.spp <- cbind(gen, number.spp)
      
      number.spp.eq <- number.spp[(nrow(number.spp) - (ngen - 1)):nrow(number.spp),]  
      equilibria <- apply (number.spp.eq, 2, FUN = sum) %/% ngen
      
      eq.time <- vector()
      for (i in 1:ncol(number.spp)) {
        occurences <- which(number.spp[,i] == equilibria[i])
        eq <- equilibria[i]
        if (length(occurences) < 2) {
          equilibria[i] = equilibria[i] - 3
        }
        while (length(occurences) < 2) {
          equilibria[i] = equilibria[i] + 1
          occurences <- which(number.spp[,i] == equilibria[i])
        }
        element <- ((gen[occurences[2]] + gen[occurences[1]]) / 2)
        eq.time <- c(eq.time, element)
      }
      version <- rep(v, length(eq.time))
      genome <- rep(g, length(eq.time))
      eq.times <- rbind(eq.times, cbind(as.data.frame(version), as.data.frame(eq.time), genome))
    }
    all.eq.time <- rbind (all.eq.time, eq.times)
  }
  return (all.eq.time)
}

StabTimePlot <- function (tbl) {
  fig <- ggplot(tbl, aes(x = as.factor(genome), y = eq.time)) +
    geom_boxplot(aes(color = version, fill = version, alpha=0.4), outlier.shape=16, outlier.size=1, notch=F) +
    #geom_jitter(aes(color=version),position = position_jitter(width = .2)) +
    scale_fill_brewer(palette = "Dark2") +
    scale_color_brewer(palette = "Dark2") +
    scale_alpha(guide = 'none') +
    labs (x = "Tamanho do genoma", y = "Tempo de equilibração", color ="Versão") +
    guides(fill = F) +
    theme_bw()+
    theme.all 
  fig
  return (fig)
}

SpacePlot <- function (loc, ger) {
  max.space=100
  fig1 <- ggplot() +
    geom_point(data = subset(loc, gen == ger), aes(x = x, y = y, color= factor(sp)), size=0.5, alpha=0.5, show.legend = FALSE)+
    guides(fill=FALSE, shape="none") +
    labs(x = "", y = "") +  
    xlim(0, 100) +
    ylim(0, 100) +
    theme_bw()+
    theme(text = element_text(size=7, family="Helvetica"),
          panel.grid.minor = element_blank(),panel.grid.major = element_blank(),
          plot.margin = unit(c(0,1,0,0), "cm"))+
    ggtitle(paste("geração", ger))
}

create.L.tbl <- function (interval) {
  spp.tbl <- tibble()
  sumario <- tibble()
  for(f in interval) {
    file.names <- paste0("./data/Completed/sizes_tests/", f, "/species/", dir(paste0("./data/Completed/sizes_tests/", f, "/species/"))[])
    number.spp <- do.call(rbind, lapply(file.names, FUN = read.csv, head = T, sep=";"))
    number.spp <- number.spp[,-3]
    # Read data
    number.spp <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
    sumario <- cbind(do.call (data.frame, number.spp[,-3]), rep(f, nrow(number.spp)))
    colnames(sumario)[4] = "variable"
    spp.tbl <- rbind(spp.tbl, sumario)
  }
  return (spp.tbl)
}

plot.L.parameter <- function (spp.info, legend) {
  max.spp = max(spp.info$sp.mn)
  #spp.info <- subset(spp.info, as.numeric(spp.info$variable)%%2 == 0, c(1, 2, 3, 4))
  spp.info$variable <- as.factor(spp.info$variable)
  spp <- ggplot(spp.info) +
    geom_ribbon(aes(x = gen, ymin=(sp.mn-sp.sd), ymax=sp.mn+sp.sd, group=variable, fill=variable), alpha = 0.25, show.legend=F) +
    geom_line (aes(x=gen, y=sp.mn, group=variable, colour=variable)) +
    scale_alpha(guide = 'none') +
    scale_color_viridis_d() +
    scale_fill_viridis_d() +
    #ylim (0, max.spp) +
    labs (x = "Geração", y = "Número de espécies", color = legend) +
    theme_bw() +
    #theme (legend.title = element_text(legend)) +
    theme.all
  #ggsave(paste0("./figs/report/spp_", type, ".png"), spp)
  return (spp)
}

sizes.histogram <- function (L, g, c) {
  file.names <- paste0("./data/Completed/sizes_tests/", L, "/sizes/", dir(paste0("./data/Completed/sizes_tests/", L, "/sizes/"))[])
  pop.info <- do.call(rbind, lapply(file.names, FUN = read.csv, head = T, sep=";"))
  
  breaks <- seq(1, 1000, 2)
  sizes.hist <- ggplot(pop.info, aes(x = size)) +
    geom_histogram(data = subset(pop.info, gen == g), breaks = breaks, position = "identity", fill = c) +
    labs(x = "size", y = "") +
    xlim(0, 150) +
    ggtitle(paste("N =", L^2*0.1)) +
    theme_bw()+
    theme.all + theme(legend.position = "none")
  
  return (sizes.hist)
}

get.legend<-function(myggplot){
  tmp <- ggplot_gtable(ggplot_build(myggplot))
  leg <- which(sapply(tmp$grobs, function(x) x$name) == "guide-box")
  legend <- tmp$grobs[[leg]]
  return(legend)
}