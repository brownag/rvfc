#include "vfc.h"

// c/o Jeroen Ooms from {opencv} <https://raw.githubusercontent.com/ropensci/opencv/master/src/base.h>
void finalize_mat(cv::Mat *frame){
  delete frame;
  frame = NULL;
}

//assume ownership
XPtrMat cvmat_xptr(cv::Mat *frame){
  XPtrMat ptr(frame);
  ptr.attr("class") = Rcpp::CharacterVector::create("opencv-image");
  return ptr;
}

//copy from stack to heap
XPtrMat cvmat_xptr(cv::Mat orig){
  cv::Mat *frame = new cv::Mat();
  orig.copyTo(*frame);
  return cvmat_xptr(frame);
}

//opencv has internal refcount system
cv::Mat get_mat(XPtrMat image){
  if(!image.inherits("opencv-image"))
    throw std::runtime_error("Image is not a opencv-image object");
  if(image.get() == NULL)
    throw std::runtime_error("Image has been destroyed");
  return *image.get();
}

