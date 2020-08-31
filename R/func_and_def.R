library(ggplot2)
library(dplyr)
library(RColorBrewer)
library(reshape2)

theme.all <- theme(text = element_text(size=10, family="Helvetica"),
                   panel.grid.minor = element_blank(),
                   panel.grid.major = element_blank(),
                   legend.text=element_text(size=8),
                   legend.margin = margin(-4, 4, -1, -1),
                   plot.margin = unit(c(0.1,2,0.1,0.1), "cm"))


plot.parameter <- function (spp.info, type, legend, c) {
  spp.info$variable <- as.factor(spp.info$variable)
  spp <- ggplot(spp.info) +
    geom_ribbon(aes(x = gen, ymin=sp.mn-sp.sd, ymax=sp.mn+sp.sd, group=variable, fill=variable), alpha = 0.25, show.legend=F) +
    geom_line (aes(x=gen, y=sp.mn, group=variable, colour=variable)) + 
    labs (x = "Geração", y = "Número de espécies", color = legend) +
    scale_alpha(guide = 'none') +
    scale_color_brewer(palette = c) + 
    scale_fill_brewer(palette = c) +
    theme_bw() +
    theme.all
  #ggsave(paste0("./figs/report/spp_", type, ".png"), spp)
  return (spp)
}


weird.plot <- function (spp.info, type, legend, c) {
  fig <- ggplot(spp.info, aes(x=as.factor(variable), y=sp.mn, group = gen, color = factor(gen))) + 
    geom_point() + geom_line() + geom_errorbar(aes(ymin = sp.mn-sp.sd, ymax = sp.mn+sp.sd), width = 0.2) + 
    #scale_x_discrete(labels=seq(1,10,by=1)) +
    labs (x = legend, y = "Número de espécies", color = "geração") +
    scale_color_brewer(palette = c) + 
    theme_bw() +
    theme.all
  #ggsave(paste0("./figs/report/", type, "_fig.png"), spp)
  return (fig)
}

create.tbl <- function (interval, type) {
  spp.tbl <- tibble(.rows = 2001*length(interval))
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

PerformanceBoxplot <- function (list1, list2, list3) {
  df <- do.call(rbind,list1)
  df$name <- rep(names(list1),times=sapply(list1,nrow))
  version <- rep("sem otimização", nrow(df))
  df <- cbind(version, df)
  df2 <- do.call(rbind,list2)
  df2$name <- rep(names(list2),times=sapply(list2,nrow))
  version <- rep("otimização no genoma", nrow(df2))
  df2 <- cbind(version, df2)
  df3 <- do.call(rbind,list3)
  df3$name <- rep(names(list3),times=sapply(list3,nrow))
  version <- rep("remove grafo", nrow(df3))
  df3 <- cbind(version, df3)
  df <- rbind (df, df2)
  df <- rbind (df, df3)
  
  #df$real = as.difftime(df$real)
  df$usr = as.numeric(df$usr)
  df$sys = as.numeric(df$sys)
  
  fig <- ggplot(df, aes(x = name, y = usr+sys, color = version)) +
    geom_boxplot(outlier.shape=16, outlier.size=2, notch=FALSE, fill = "lightgray") +
    theme_bw()+
    theme.all 
  fig <- fig + labs (x = "Tamanho do genoma B", y = "Tempo (usr + sys)", color ="versão")
  return (fig)
}
