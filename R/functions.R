library(ggplot2)
library(dplyr)
library(RColorBrewer)
library(reshape2)
library(viridis)
library(MASS)
library(gridExtra)
library(readr)
library(stringr)
library(data.table)
library(drc)


# A theme for all plots to look alike
theme.all <- theme(text             = element_text(size=10, family="Helvetica"),
                   title            = element_text(size = 9),
                   legend.text      = element_text(size=9),
                   legend.margin    = margin(-1, 1, -1, -1),
                   panel.grid.minor = element_blank(),
                   panel.grid.major = element_blank(),
                   plot.margin      = unit(c(0.1,0.5,0.1,0.1), "cm"))

# definitions used
versions <- c("V0", "V1", "V2")
genomes  <- c(150, 1500, 15000, 150000)

create.tbl <- function (interval, type) {
  spp.tbl <- tibble()
  sumario <- tibble()
  for(f in interval) {
    file.names <- paste0("./data/Completed/test_cp/", type, "/", f, "/species/", dir(paste0("./data/Completed/test_cp/", type, "/", f, "/species/"))[])
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
    labs (x = "Generation", y = "Number of species", color = legend) +
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

performance.plot <- function () {
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

stab.time.plot <- function (tbl) {
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

space.plot <- function (loc, ger) {
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

compare.L.parameter <- function (L, n) {
  spp.info <- tibble()
  sumario <- tibble()
  for(f in 1:length(L)) {
    file.names <- paste0("./data/Completed/sizes_tests/", L[f], "/species/", dir(paste0("./data/Completed/sizes_tests/", L[f], "/species/"))[])
    number.spp <- do.call(rbind, lapply(file.names[1:n[f]], FUN = read.csv, head = T, sep=";"))
    number.spp <- number.spp
    # Read data
    number.spp <- aggregate( . ~ gen, FUN=function(x) c(s=sum(x)), data=number.spp)
    sumario <- cbind(do.call (data.frame, number.spp), rep(L[f], nrow(number.spp)))
    colnames(sumario)[5] = "variable"
    #colnames(spp.info)[5] = "variable"
    spp.info <- rbind(spp.info, sumario)
  }
  
  max.spp = max(spp.info$sp)
  #spp.info <- subset(spp.info, as.numeric(spp.info$variable)%%2 == 0, c(1, 2, 3, 4))
  spp.info$variable <- as.factor(spp.info$variable)
  spp <- ggplot(spp.info) +
    #geom_ribbon(aes(x = gen, ymin=(sp.mn-sp.sd[]), ymax=sp.mn+sp.sd, group=variable, fill=variable), alpha = 0.25, show.legend=F) +
    geom_line (aes(x=gen, y=sp, group=variable, colour=variable)) +
    #scale_alpha(guide = 'none') +
    scale_color_viridis_d() +
    scale_fill_viridis_d() +
    ylim (0, max.spp) +
    labs (x = "Geração", y = "Número de espécies", color = "L") +
    theme_bw() +
    #theme (legend.title = element_text(legend)) +
    theme.all
  #ggsave(paste0("./figs/report/spp_", type, ".png"), spp)
  return (spp)
}

sizes.histogram <- function (L, g, c) {
  file.names <- paste0("./data/Completed/sizes_tests/", L, "/sizes/", dir(paste0("./data/Completed/sizes_tests/", L, "/sizes/"))[])
  pop.info <- do.call(rbind, lapply(file.names, FUN = read.csv, head = T, sep=";"))
  breaks <- seq(1, 1000, 1)
  pop.info <- subset(pop.info, gen == g)
  fit <- fitdistr(pop.info$size, "lognormal")
  sizes.hist <- ggplot(pop.info, aes(x = size)) +
    geom_histogram(aes(y=..density..), breaks = breaks, position = "identity", fill = c) +
    stat_function(fun = dlnorm, size = 0.5, color = 'darkgrey',
                  args = list(mean = fit$estimate[1], sd = fit$estimate[2])) +
    labs(x = "size", y = "") +
    xlim(0, 150) +
    ggtitle(paste("N =", L^2*0.1)) +
    theme_bw()+
    theme.all + theme(legend.position = "none")

  return (sizes.hist)
}

sizes.histogram.compare <- function (L, g, c, n) {
  file.names <- paste0("./data/Completed/sizes_tests/", L, "/sizes/", dir(paste0("./data/Completed/sizes_tests/", L, "/sizes/"))[])
  pop.info <- do.call(rbind, lapply(file.names[1:n], FUN = read.csv, head = T, sep=";"))
  breaks <- seq(1, 1000, 1)
  pop.info <- subset(pop.info, gen == g)
  fit <- fitdistr(pop.info$size, "lognormal")
  sizes.hist <- ggplot(pop.info, aes(x = size)) +
    geom_histogram(aes(y=..density..), breaks = breaks, position = "identity", fill = c) +
    stat_function(fun = dlnorm, size = 0.5, color = 'darkgrey',
                  args = list(mean = fit$estimate[1], sd = fit$estimate[2])) +
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

# Again, equilibration time for varying pop size <- I don't know if this is right
equilibration.times <- function (interval) {
  sim <- seq(1, 20, 1)
  equilibria.times <- data.frame(matrix(ncol = 3, nrow = 0))
  for(f in interval) {
    file.names <- paste0("./data/Completed/sizes_tests/", f, "/species/", dir(paste0("./data/Completed/sizes_tests/", f, "/species/"))[])
    eq.times <- vector()
    for (j in sim) {
      number.spp <- read.csv(file.names[j], header = T, sep = ";")
      eq.spp <- mean(number.spp[900:1001,2])
      i = 1
      while (number.spp[i,2] < eq.spp) {
        i <- i+1
      }
      begin = number.spp[i,1]
      while (number.spp[i,2] > eq.spp) {
        i <- i+1
      }
      end = number.spp[i,1]
      eq.times[j] <- (end+begin)/2
    }
    row <- c(f^2*0.1, mean(eq.times), sd(eq.times))
    equilibria.times <- rbind (equilibria.times, row)
  }
  colnames(equilibria.times) <- c("pop", "eq.times.mn", "eq.times.sd")
  return (equilibria.times)
}

plot.boxplot <- function (diameters) {
  p <- ggplot(diameters) +
    geom_boxplot(aes(x=as.factor(spp), y=d, fill=as.factor(spp))) +
    labs(x = "Species", y = "Species diameter") +
    ggtitle(paste("oi", "(B = 150k)")) +
    theme_bw() +
    theme.all +
    theme(legend.position = "none")
  return (p)
}

diameter.boxplot <- function (interval, g){
  files <- list.files(path       = "./data/Completed/diameter", # directory to search within
                      pattern    = ".*()distances_01.csv$",     # regex pattern
                      recursive  = TRUE,                        # search subdirectories
                      full.names = TRUE)                        # return the full path
  
  # extracts S and L and store in list
  variables <- get.variables(files, "./data/Completed/diameter/", "/distances/distances_01.csv")
  
  diameters.list <- lapply(files, read.csv, header = T, sep = ";")
  names(diameters.list) <- files
  
  rep (variables[[i]][1], 3)
  
  for (i in names(diameters.list)) {
    diameters.list[[i]] <- cbind(diameters.list[[i]], rep(variables[[i]][1], nrow(diameters.list[[i]])), rep(variables[[i]][2], nrow(diameters.list[[i]]))) 
  }
  
  diameters.list <- lapply (diameters.list, apply )
  
  plots <- lapply(diameters.list, plot.boxplot)
}

# Modified and better functions
get.variables <- function (files, begin, end) {
  variables           <- lapply(files, str_replace, begin, "")
  variables           <- lapply(variables, str_replace, end, "")
  variables           <- lapply(variables, str_replace, "/", ", ")
  names(variables)    <- files
  variable.list       <- lapply(variables, function(x){
      return (transpose(as.data.frame(as.numeric(strsplit(x, split = ", ", fixed = TRUE)[[1]]))))
    })
  return (variable.list)
} #ok

diameter.data <- function () {
  # read all files used in plot
  files <- list.files(path       = "./data/Completed/diameter", # directory to search within
                      pattern    = ".*()distances_01.csv$",     # regex pattern
                      recursive  = TRUE,                        # search subdirectories
                      full.names = TRUE)                        # return the full path
  
  # extracts S and L and store in list
  variables <- get.variables(files, "./data/Completed/diameter/", "/distances/distances_01.csv")
  
  # read all files
  diameters.list <- lapply(files, read.csv, header = T, sep = ";")
  names(diameters.list) <- files
  
  # Exclude unused variables and 
  var.size <- mapply(c, variables, lapply(diameters.list, nrow), SIMPLIFY=FALSE)
  variables.column <- lapply(var.size, function(x){
    out <- data.frame(cbind(rep(x[[1]], x[[3]]), rep(x[[2]], x[[3]])))
    colnames(out) <- c("S", "L")
    return (out)
  })
  
  return(do.call(rbind, Map(data.frame, diameters.list, variables.column)))
  
} # ok

# nomes confusos e você precisa comentar seu código
regression.L.S <- function (data) {
  S <- sort(unique(data$S))
  regressions <- tibble()
  intercept.y = mean(subset(data, S == 3)$d)
  intercept.x = 3
    
  for(s in S[-1]) {
    temp <- subset(data, data$S == s, c("gen", "d", "S", "L"))
    lin.reg <- summary(lm( I(temp$d-intercept.y) ~ I(temp$S-intercept.x) + 0))
    regressions <- rbind(regressions, c(lin.reg$coefficients[1],
                                        lin.reg$coefficients[2],
                                        lin.reg$coefficients[3],
                                        lin.reg$adj.r.squared, 
                                        s, temp[1,4]))
    print(lin.reg$regressions)
    
  }
  colnames(regressions) <- c("intercept", "slope","error", "adjusted.R.squared", "S", "L")
  return (regressions)
}

regression.L.Smax <- function(data) {
  Smax <- sort(unique(data$S))
  regressions <- tibble()
  for(s in Smax[-1]) {
    temp <- subset(data, data$S <= s, c("gen", "d", "S", "L"))
    lin.reg <- summary(lm(temp$d~temp$S))
    regressions <- rbind(regressions, c(lin.reg$coefficients[1],
                                        lin.reg$coefficients[2],
                                        lin.reg$coefficients[3],
                                        lin.reg$adj.r.squared, 
                                        s, temp[1,4]))
    
  }
  colnames(regressions) <- c("intercept", "slope", "error", "adjusted.R.squared", "Smax", "L")
  return (regressions)
}

regression.Smax.plot <- function (g) {
  data <- diameter.data()
  data <- subset(data, gen == g)
  by.L <- split (data, data$L)
  
  all.regs <- lapply (by.L, regression.L.Smax)
  reg.data <- do.call(rbind, all.regs)
  
  regression.plot <- ggplot(reg.data, aes(Smax, adjusted.R.squared, color = as.factor(L))) +
                     geom_point(size=1.5, alpha = 0.7) + theme_bw() + theme.all +
                     geom_errorbar(aes(ymin=adjusted.R.squared-error, ymax=adjusted.R.squared+error), width=.2) +
                     ggtitle("Smax") +
                     #scale_y_continuous(breaks = seq(0, 0.85, 0.1)) +
                     scale_x_continuous(breaks = unique(reg.data$Smax)) +
                     scale_color_viridis_d() +
                     labs (x = "Smax", y = "R²", color = "L")
  regression.plot
  #all.regs.all.L <- regression.L(data) #regs for all L
  #all.regs.all.L <- all.regs.all.L[,-5]  
}

plot.dxS <- function (diameters) {
  dxS <- ggplot (diameters, aes(x=S, y=d, color=factor(L))) +
    #stat_smooth(data = subset(diameters, (S/L < 0.1)), method='lm', formula = y~x, color="black", size=0.5, se = F, fullrange = T) +
    geom_point() + theme_bw() + theme.all +
    geom_errorbar(aes(ymin=d-sd, ymax=d+sd), width=.2) +
    scale_x_continuous(breaks = seq(0,25,5)) +
    scale_y_continuous(breaks = seq(0, 200, 25), limits = c(0, max(diameters$d+diameters$sd))) +
    scale_color_viridis_d() +
    labs (x = "Radius", y = "Mean species diameter", color = "L")
}

diameter.vs.radius.complete <- function(g){
  files <- list.files(path       = "./data/Completed/diameter", # directory to search within
                      pattern    = ".*()distances_01.csv$",     # regex pattern
                      recursive  = TRUE,                        # search subdirectories
                      full.names = TRUE)                        # return the full path
  
  # extracts S and L and store in list
  variables <- get.variables(files, "./data/Completed/diameter/", "/distances/distances_01.csv")
  
  # read all files
  diameters.list <- lapply(files, read.csv, header = T, sep = ";")
  names(diameters.list) <- files
    
  # Take mean and sd from each table
  mean.sd.d <- lapply(diameters.list, function(x) {
                  out <- subset(x, (gen == g & d > 0), 6)
                  out <- sapply (out, as.numeric)
                return (transpose(as.data.frame(c(mean(out), sd(out)))))})
  
  # unify values and variables 
  diameters <- do.call(rbind, Map(data.frame, mean=mean.sd.d, R=variables))
  colnames(diameters) <- c("d", "sd", "S", "L")
  
  # plot the graph and return
  return(plot.dxS(diameters))
}

sp.vs.radius.complete <- function(){
  # read all files used in plot
  files <- list.files(path       = "./data/Completed/diameter", # directory to search within
                      pattern    = ".*()numsp_01.csv$",         # regex pattern
                      recursive  = TRUE,                        # search subdirectories
                      full.names = TRUE)                        # return the full path
  
  # extracts S and L and store in list
  variables <- get.variables(files, "./data/Completed/diameter/", "/species/numsp_01.csv")
  
  # read all files
  numsp.list <- lapply(files, read.csv, header = T, sep = ";")
  names(numsp.list) <- files
  
  # take diameters from desired generation. Exclude diameters = 0. Transform in numeric
  numsp.g <- lapply(numsp.list, subset, (gen == g), 2)
  numsp.g <- lapply (numsp.g, as.numeric)
  
  # unify values and variables 
  species <- do.call(rbind, Map(data.frame, sp = numsp.g, V = variables))
  colnames(species) <- c("sp", "S", "L")
  
  spxS <- ggplot (species, aes(x=S, y=sp, color=factor(L))) +
    geom_point() + theme_bw() + theme.all +
    scale_color_viridis_d() +
    labs (x = "S", y = "Number of Species", color = "L")
  spxS
  return(spxS)
}

slope.Smax.plot <- function (g) {
  #get data an split in tables by L
  data <- diameter.data()
  data <- subset(data, gen == g)
  by.L <- split (data, data$L)
  
  all.regs <- lapply (by.L, regression.L.Smax)
  reg.data <- do.call(rbind, all.regs)
  
  slope.plot <- ggplot(reg.data, aes(Smax, slope, color = as.factor(L))) +
    geom_point(size=1.2, alpha = 0.8) + theme_bw() + theme.all + geom_line(size=0.7) +
    geom_errorbar(aes(ymin=slope-error, ymax=slope+error), width=.2) +
    #scale_y_continuous(breaks = seq(0, 0.85, 0.1)) +
    scale_x_continuous(breaks = unique(reg.data$Smax)) +
    scale_color_viridis_d() +
    labs (x = "Smax", y = "Slope", color = "L")
  slope.plot
  #all.regs.all.L <- regression.L(data) #regs for all L
  #all.regs.all.L <- all.regs.all.L[,-5]  
}

slope.L.plot <- function (g) {
  #get data an split in tables by L
  data <- diameter.data()
  data <- subset(data, gen == g)
  by.L <- split (data, data$L)
  
  all.regs <- lapply (by.L, regression.L.Smax)
  max.regs <- lapply (all.regs, function(x) {
    return (subset(x, adjusted.R.squared == max(x$adjusted.R.squared)))
    })
  reg.data <- do.call(rbind, max.regs)

  slope.plot <- ggplot(reg.data, aes(L, slope, color = as.factor(Smax))) +
    geom_point(size=3, alpha = 0.8) + theme_bw() + theme.all +
    geom_errorbar(aes(ymin=slope-error, ymax=slope+error), width=.2) +
    #scale_y_continuous(breaks = seq(0, 0.85, 0.1)) +
    scale_x_continuous(breaks = unique(reg.data$L)) +
    scale_color_viridis_d() +
    labs (x = "L", y = "Slope", color = "Smax")
  slope.plot
}

interpolation.plot <- function (g) {
  data <- diameter.data()
  data <- subset(data, gen == g)
  by.L <- split (data, data$L)
  
  all.regs <- lapply (by.L, regression.L.S)
  reg.data <- do.call(rbind, all.regs)
  
  slope.plot <- ggplot(reg.data, aes(S, slope, color = as.factor(L))) +
    geom_point(size=1.2, alpha = 0.8) + theme_bw() + theme.all + geom_line(size=0.7) +
    geom_errorbar(aes(ymin=slope, ymax=slope), width=.2) +
    #scale_y_continuous(breaks = seq(0, 0.85, 0.1)) +
    scale_x_continuous(breaks = unique(reg.data$S)) +
    scale_color_viridis_d() +
    labs (x = "S", y = "Slope", color = "L")
  slope.plot
  #all.regs.all.L <- regression.L(data) #regs for all L
  #all.regs.all.L <- all.regs.all.L[,-5]  
}

