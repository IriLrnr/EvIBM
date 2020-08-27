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


plot.parameter <- function (spp.info, type, legend) {
  spp.info$variable <- as.factor(spp.info$variable)
  spp <- ggplot(spp.info) +
    geom_ribbon(aes(x = gen, ymin=sp.mn-sp.sd, ymax=sp.mn+sp.sd, group=variable, fill=variable), alpha = 0.25, show.legend=F) +
    geom_line (aes(x=gen, y=sp.mn, group=variable, colour=variable)) + 
    labs (x = "Geração", y = "Número de espécies", color = legend) +
    scale_alpha(guide = 'none') +
    theme_bw() +
    theme.all
  #ggsave(paste0("./figs/report/spp_", type, ".png"), spp)
  return (spp)
}


weird.plot <- function (spp.info, type, legend) {
  fig <- ggplot(spp.info, aes(x=as.factor(variable), y=sp.mn, group = gen, color = factor(gen))) + 
    geom_point() + geom_line() + geom_errorbar(aes(ymin = sp.mn-sp.sd, ymax = sp.mn+sp.sd), width = 0.2) + 
    #scale_x_discrete(labels=seq(1,10,by=1)) +
    labs (x = legend, y = "Número de espécies", color = "geração") +
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
