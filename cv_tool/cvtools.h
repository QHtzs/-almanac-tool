#ifndef CVTOOLS_H
#define CVTOOLS_H

#include "opencv2/core.hpp"
#include <vector>
#include <list>
#include <algorithm>

#define _isin_range(mat, roi, ok) do{ \
    ok = (0 <= roi.x   \
    && 0 <= roi.width   \
    && roi.x + roi.width <= mat.cols \
    && 0 <= roi.y  \
    && 0 <= roi.height  \
    && roi.y + roi.height <= mat.rows \
    ) ; \
}while(0)

#define _is_resizeable(mat, size, ok) do{ \
    ok = true;  \
    if(mat.rows <=0 || mat.cols <=0) ok = false;  \
    else if(size.width <=0 || size.height <=0) ok= false; \
}while(0)

/// 简单的对opencv一些要用的方法做封装
namespace tools {

/// 轴方向，0数值轴
enum AXIS {
    HIST,
    VERT
};

typedef void auto_detect(std::vector<int> const& vec, int &minFitPx,  int &minSpace);

///Default flags cv::INTER_LINEAR
bool ResizeMat(cv::Mat const& src, cv::Mat&dst,  cv::Size size, int flags=1);

/// get mat roi
bool RoiMat(const cv::Mat &src, cv::Mat &dst, cv::Rect const &roi);

/// load image
cv::Mat ReadImage(const char* file, int flags);

/// reshape mat
cv::Mat ReShapeMat(cv::Mat const &src, int cn=0, int rows=1);

/// U8C1 to 32FC1
bool MatUF2FF(cv::Mat &src, cv::Mat &dst);

/// cout no zero along axis, mat: U8C1
std::vector<int> CountNoZero(cv::Mat &mat, AXIS axis);

/// cout zero along axis, mat: U8C1
std::vector<int> CountZero(cv::Mat &mat, AXIS axis);

/// flat mat vector
bool FlatMat(std::vector<cv::Mat> &mats, cv::Mat &dst);

/// Rotate
bool RotateMat(cv::Mat &src, cv::Mat &dst, double degree, cv::Scalar bordFill);


void auto_detect_threshold(std::vector<int> const& vec, int &minFitPx, int &minSpace);

/// minFitPx: number of fit px(black or white), black: [black/white].
/// minSpace: min not fit px.
/// axis: vert or hist axis.
/// detector: auto detect minFitP and minSpace.
/// use_fall_drop: use dropfall algorithm.
void SplitMat(cv::Mat &src,
              std::vector<cv::Mat> &dst,
              AXIS axis,
              int minFitPx=3, bool black=true, int minSpace=3,
              auto_detect detector = &auto_detect_threshold, bool use_fall_drop=false);


/// drop fall algorithm
void DropFall(cv::Mat &src, std::vector<cv::Mat> &dst);

///  default flags cv::INTER_LINEAR
cv::Mat MatTo32X32(cv::Mat &src, int flags = 1);

/// extend mat
cv::Mat ExtendWidthOrHeight(cv::Mat &src);

}

#endif // CVTOOLS_H
