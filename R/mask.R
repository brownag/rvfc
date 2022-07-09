
#' Mask Two Images by 'Vector Field Consensus'
#'
#' Mask two images to identify indices of point correspondence by 'Vector Field Consensus'
#'
#' @param x matrix.
#' @param y matrix.
#'
#' @return numeric.
#' @export
mask <- function(x, y) {
  .Call("_rvfc_mask", x, y)
}
