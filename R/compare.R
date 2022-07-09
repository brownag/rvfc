
#' Compare Two Matrices by 'Vector Field Consensus'
#'
#' Compare two matrices to identify indices of point correspondence by 'Vector Field Consensus'
#'
#' @param x matrix.
#' @param y matrix.
#'
#' @return numeric.
#' @export
compare <- function(x, y) {
  .Call("_rvfc_compare", x, y)
}
