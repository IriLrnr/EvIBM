# Load the libraries
library(ggplot2)

# Read data
number.spp <- read.csv(file ="./data/species/numspV2_4.csv", head = TRUE, sep=";")

# Define limits for the 
max.spp <- max(number.spp[,2])
max.time <- max(number.spp[,1])


