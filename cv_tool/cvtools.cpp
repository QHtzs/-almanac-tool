#include "cvtools.h"

namespace tools {

bool ResizeMat(cv::Mat const& src, cv::Mat&dst,  cv::Size size, int flags)
{
    bool ok;
    _is_resizeable(src, size, ok);
    if(!ok) return ok;
    cv::resize(src, dst, size, flags);
    return ok;
}

bool RoiMat(const cv::Mat &src, cv::Mat &dst, cv::Rect const &roi)
{
    bool ok;
    _isin_range(src, roi, ok);
    if(!ok) return ok;
    dst = src(roi);
    return ok;
}

cv::Mat ReadImage(const char* file, int flags)
{
    return cv::imread(file, flags);
}

cv::Mat ReShapeMat(cv::Mat const &src, int cn, int rows){
    return src.reshape(cn, rows);
}

bool MatUF2FF(cv::Mat &src, cv::Mat &dst){
    if(src.rows<=0||src.cols<=0) return false;
    dst = cv::Mat(src.rows,src.cols,CV_32FC1);
    for(int j=0;j<src.rows;j++){
        float* arr = dst.ptr<float>(j);
        for(int i=0;i<src.cols;i++){
            arr[i] = src.ptr<uchar>(j)[i] <126 ? -0.5f:0.5f;
        }
    }
    return true;
}

std::vector<int> CountNoZero(cv::Mat &mat, AXIS axis)
{
    std::vector<int> ret(axis==VERT?mat.rows:mat.cols, 0);
    int i, j;
    int &index = axis == VERT? j: i;
    for(j=0; j<mat.rows;j++){
        uchar *data = mat.ptr<uchar>(j);
        for(i=0;i<mat.cols;i++){
            if(data[i]) ret[index] += 1;
        }
    }
    return ret;
}

std::vector<int> CountZero(cv::Mat &mat, AXIS axis)
{
    std::vector<int> ret(axis==VERT?mat.rows:mat.cols, 0);
    int i, j;
    int &index = axis == VERT? j: i;
    for(j=0; j<mat.rows;j++){
        uchar *data = mat.ptr<uchar>(j);
        for(i=0;i<mat.cols;i++){
            if(data[i] == 0) ret[index] += 1;
        }
    }
    return ret;
}

bool FlatMat(std::vector<cv::Mat> &mats, cv::Mat &dst)
{
    if(mats.empty()) return false;
    std::vector<cv::Mat>::iterator ite;

    // warnning erase while iterating
    for(ite = mats.begin();ite != mats.end();){
        if(ite->empty()) ite = mats.erase(ite);
        else ite++;
    }

    int rows = static_cast<int>(mats.size());
    int cols = mats.at(0).rows * mats.at(0).cols;
    dst = cv::Mat(rows,cols,CV_32FC1);
    for(int i=0;i<rows;i++){
        cv::Mat mat = ReShapeMat(mats.at(i), 0, 1);
        cv::Mat _mat;
        if(MatUF2FF(mat,_mat)){
            _mat.copyTo(dst.rowRange(i,i+1));
        }
    }
    return true;
}

bool RotateMat(cv::Mat &src, cv::Mat &dst, double degree, cv::Scalar bordFill)
{
    if(src.empty()) return false;
    int chnel = src.channels();
    if(!(chnel==1 || chnel==3)) return false;
    cv::Point2f center(src.cols/2.0f,src.rows/2.0f);
    float angle = 0.0f - static_cast<float>(degree);
    cv::Mat rot = cv::getRotationMatrix2D(center,angle,1);
    cv::Rect bbox = cv::RotatedRect(center,src.size(), angle).boundingRect();
    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
    cv::warpAffine(src,dst,rot,bbox.size(),1,0,bordFill);
    return true;
}

void auto_detect_threshold(std::vector<int> const& vec, int &minFitPx, int &minSpace)
{
    std::vector<size_t> has_true;
    for(size_t i=0; i<vec.size(); i++){
        if(vec[i]) has_true.push_back(i);
    }
    if(has_true.empty()) return;
    std::sort(has_true.begin(), has_true.end());
    int step=1, count = 1;
    size_t minx=has_true.at(0), sum = has_true.at(0);
    for(size_t i=0; i<has_true.size(); i++){
        if(minx < has_true.at(i)){ // ignore duplicated values
            step++;
            minx = has_true.at(i);
        }
        if(step > 2) break;
        count ++ ;
        sum += minx;
    }
    minFitPx = 1 + sum/count;
    std::vector<size_t> no_fit;
    for(size_t i=0; i<vec.size(); i++){
        if(vec.at(i) < minFitPx) no_fit.push_back(i);
    }

    int end = static_cast<int>(no_fit.size()) - 1;
    for(; end > 0; end--){
        if(no_fit.at(end) - no_fit.at(end-1) > 1) break;
    }
    sum = 0;
    step = 0;
    for(int i=0; i<end; i++){
        //no_fit.at(i) > no_fit.at(i-1) is always true
        if(no_fit.at(i) - no_fit.at(i-1) > 1){
            step ++;
            sum += no_fit.at(i) - no_fit.at(i-1);
        }
    }
    minSpace = step == 0 ? 2: 2 + sum/step;
}


void SplitMat(cv::Mat &src,
              std::vector<cv::Mat> &dst,
              AXIS axis,
              int minFitPx, bool black, int minSpace,
              auto_detect detector, bool use_fall_drop)
{
    if(use_fall_drop && axis==HIST){
        DropFall(src, dst);
    }else{
        std::vector<int> vec = black ? CountZero(src, axis): CountNoZero(src, axis);
        if(detector) detector(vec, minFitPx, minSpace);
        if(axis == VERT) minSpace = 3;
        std::vector<int> no_blank;
        std::vector<std::pair<int,int>> pairs;
        for(size_t i=0;i<vec.size();i++){
            if(vec.at(i) >= minFitPx) no_blank.push_back(i);
        }
        if(no_blank.empty()) return;
        no_blank.push_back(no_blank.back()+minSpace+1);
        int begin = std::max(0, no_blank.at(0)-1);
        for(size_t i=0; i<no_blank.size()-1;i++){
            if(no_blank.at(i+1) - no_blank.at(i) > minSpace){
                pairs.push_back(std::make_pair(begin,no_blank.at(i)+1));
                begin = std::max(0,no_blank.at(i+1)-1);
            }
        }
        if(axis == HIST){
            int height = src.rows;
            for(size_t i=0; i < pairs.size();i++){
                int width = pairs.at(i).second - pairs.at(i).first;
                cv::Rect rect(pairs.at(i).first,0,width,height);
                cv::Mat ROI;
                if(RoiMat(src,ROI,rect)){
                    cv::Mat m = ROI.clone();
                    dst.push_back(m);
                }
            }
        }else{
            int width = src.cols;
            for(size_t i=0; i < pairs.size();i++){
                int height = pairs.at(i).second - pairs.at(i).first;
                cv::Rect rect(0, pairs.at(i).first, width, height);
                cv::Mat ROI;
                if(RoiMat(src,ROI,rect)){
                    cv::Mat m = ROI.clone();
                    dst.push_back(m);
                }
            }

        }
    }

}

static int DropFall(cv::Mat const& src, cv::Mat &left, cv::Mat &right, int x0)
{
    uchar COLOR_BLACK = 0;
    if(src.cols< 3) return -1;
    cv::Point beginePoint(0, x0);  //x, y is oppsite, ignore x0==0 or x0 ==src.cols

    std::list<cv::Point> pointList;
    pointList.push_back(beginePoint);

    for (int i = 0; i < src.rows-1; i++)
    {
        int x = pointList.back().x, y = pointList.back().y;
        if (x == src.rows -1)
        {
            break;
        }
        int Sigma = 0, wi = 0, m = 1, Max = std::numeric_limits<int>::min();
        int tSigma;
        for (int j = 0; j < 2; j++)
        {
            for (int k = -1; k < 2; k++)
            {
                if (j!=0 || k!=0)
                {
                    tSigma = (src.ptr<uchar>(x+j)[y+k] == COLOR_BLACK? 0 : 1) * (m++-j*k*2);
                    Max = tSigma > Max ? tSigma: Max;
                    Sigma += tSigma;
                }
            }
        }
        wi = Sigma == 15 || Sigma == 0 ? 4: Max;
        cv::Point tPoint;
        switch (wi)
        {
        case 1:
            tPoint.x = x;
            tPoint.y = y-1;
            break;
        case 2:
            tPoint.x = x;
            tPoint.y = y + 1;
            break;
        case 3:
            tPoint.x = x + 1;
            tPoint.y = y + 1;
            break;
        case 4:
            tPoint.x = x + 1;
            tPoint.y = y ;
            break;
        case 5:
            tPoint.x = x + 1;
            tPoint.y = y - 1;
            break;
        default:
            break;
        }
        pointList.push_back(tPoint);
    }
    //left, rigt bellow
    int lm=x0, rm=x0;
    for(auto ite=pointList.begin(); ite!=pointList.end(); ite++){
        lm = std::min(lm, ite->y);
        rm = std::max(rm, ite->x);
    }
    left = cv::Mat(src.rows, rm, CV_8UC1);
    right = cv::Mat(src.rows, src.cols-lm, CV_8UC1);
    for(auto ite=pointList.begin(); ite!=pointList.end(); ite++){
        //write left, and right
    }
}

void DropFall(cv::Mat &src, std::vector<cv::Mat> &dst){
    int status;
    cv::Mat left, right;
    status = DropFall(src, left, right, src.cols/2);
    if(status == -1){
        dst.push_back(src);
    }else{
        DropFall(left, dst);
        DropFall(right, dst);
    }
}


cv::Mat MatTo32X32(cv::Mat &src, int flags)
{
    cv::Mat ret;
    cv::Size size(32, 32);
    ResizeMat(src, ret, size, flags);
    return ret;
}

cv::Mat ExtendWidthOrHeight(cv::Mat &src)
{
    cv::Mat result;
    int rows = src.rows, cols = src.cols;
    if(rows > cols){
        result = cv::Mat(rows,rows,CV_8UC1, cv::Scalar(255));
        int x = (rows - cols)/2;
        cv::Rect rect(x,0,cols,rows);
        src.copyTo(result(rect));
    }else if( rows==cols){
        result = src.clone();
    }else{
        result = cv::Mat(cols,cols,CV_8UC1,cv::Scalar(255));
        int y = (cols - rows)/2;
        cv::Rect rect(0,y,cols,rows);
        src.copyTo(result(rect));
    }
    return result;
}

}


