// for Rcpp
// [[Rcpp::interfaces(r, cpp)]]
#include <Rcpp.h>
using namespace Rcpp;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/features2d.hpp>

//  c/o Jeroen Ooms from {opencv} <https://raw.githubusercontent.com/ropensci/opencv/master/src/opencv_types.h>
#define R_NO_REMAP
#define STRICT_R_HEADERS

#if CV_VERSION_EPOCH >= 3 || (!defined(CV_VERSION_EPOCH) && CV_VERSION_MAJOR >= 3)
#define HAVE_OPENCV_3
#endif

#if !defined(CV_VERSION_EPOCH) && CV_VERSION_MAJOR >= 4
#define HAVE_OPENCV_4
#endif

void finalize_mat(cv::Mat *frame);
typedef Rcpp::XPtr<cv::Mat, Rcpp::PreserveStorage, finalize_mat, true> XPtrMat;

//  c/o Jeroen Ooms from {opencv} <https://raw.githubusercontent.com/ropensci/opencv/master/src/utils.h>
cv::Mat get_mat(XPtrMat image);
XPtrMat cvmat_xptr(cv::Mat *frame);
XPtrMat cvmat_xptr(cv::Mat orig);
XPtrMat cvmat_markers(XPtrMat ptr);

#define xstr(s) str(s)
#define str(s) #s

// rvfc methods
std::vector<int> compare(XPtrMat x, XPtrMat y);
XPtrMat mask(XPtrMat x, XPtrMat y);


