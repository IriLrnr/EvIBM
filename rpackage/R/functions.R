#' Call EvIBM
#'
#' This function calls and runs EvIBM program.
#' @keywords EvIBM
#' @export
#' @examples
#' cat_function()

EvIBM <-function() {
  setwd("../")
  command <- paste("make")
  system(command)
  setwd("./rpackage")
}
