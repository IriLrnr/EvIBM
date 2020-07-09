library(ggplot2)
library(dplyr)
library(RColorBrewer)

## Quero fazer um gráfico que compara as curvas médias com varias cores
getwd()
setwd("./data/test_cp/g/")
spp.mn.g <- tibble(.rows = 201)
for(f in 1:10){
  setwd(paste0("./", f, "/species"))
  file.names <- dir()
  
  number.spp=data.frame()
  for (i in 1:(length(file.names)-1)){
    dados <- read.csv(paste(file.names[i]), head=TRUE, sep=";")
    number.spp <- rbind(number.spp, dados)
  }
  setwd("../../")
  
  # Read data
  number.spp <- data.frame(number.spp)
  number.data <- aggregate( . ~ gen, FUN=function(x) c(mn=mean(x), sd=sd(x)), data=number.spp)
  sumario <- do.call (data.frame, number.data)
  
  spp.mn.g <- cbind(spp.mn.g, sumario$sp.mn)
}
setwd("../../")

colnames(number.spp) <- c("gen","sp", "sim")
