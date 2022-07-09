#include "vfc.h"

// [[Rcpp::export]]
std::vector<int> compare(XPtrMat x, XPtrMat y) {
  VFC myvfc;
  cv::Mat xm = get_mat(x);
  cv::Mat ym = get_mat(y);

  // TODO: wrappers for other feature detectors e.g. SURF
  Ptr<FeatureDetector> detector = ORB::create();
  Ptr<DescriptorExtractor> extractor = ORB::create();
  BFMatcher matcher(NORM_L2);

  std::vector<cv::KeyPoint> keypointsx;
  std::vector<cv::KeyPoint> keypointsy;
  cv::Mat descriptors_1, descriptors_2;
  std::vector<cv::DMatch> matches;

  detector->detect(xm, keypointsx);
  detector->detect(ym, keypointsy);

  extractor->compute(xm, keypointsx, descriptors_1);
  extractor->compute(ym, keypointsy, descriptors_2);

  matcher.match(descriptors_1, descriptors_2, matches);

  std::vector<Point2f> X;
  std::vector<Point2f> Y;
  X.clear();
  Y.clear();
  for (unsigned int i = 0; i < matches.size(); i++) {
    int idx1 = matches[i].queryIdx;
    int idx2 = matches[i].trainIdx;
    X.push_back(keypointsx[idx1].pt);
    Y.push_back(keypointsy[idx2].pt);
  }
  myvfc.setData(X, Y);
  myvfc.optimize();
  std::vector<int> matchIdx = myvfc.obtainCorrectMatch();

  return(matchIdx);
}

// [[Rcpp::export]]
XPtrMat mask(XPtrMat x, XPtrMat y) {

  // TODO: finish this idea; doesnt do anything yet

  std::vector<int> z = compare(x, y);
  cv::Mat m = get_mat(x);
  cv::Mat xx = m.reshape(1, m.total() * m.channels());
  cv::Mat mask = cv::Mat::zeros(xx.rows, xx.cols, CV_8UC1);
  CV_Assert(mask.isContinuous());
  cv::Mat result = cv::Mat(xx.rows, xx.cols, xx.type(), xx.type()).setTo(0);

  // pointer to data, or clone of data if discontinuous
  uchar *arr = mask.isContinuous() ? mask.data : mask.clone().data;
  uint arrlen = mask.total() * mask.channels();

  // apply mask based on z (VFC)
  // updating references via operator[]
  for (int i = 0; i < (int)z.size(); ++i) {
    if (z[i] < (int)arrlen) {
      arr[z[i]] = 255;
    }
  }

  // copy updated arr back to update mask
  std::memcpy(mask.data, arr, arrlen * sizeof(uchar));

  // copy image x to result, using mask
  xx.copyTo(result, mask);
  return(cvmat_xptr(result));
}
