#ifndef FRAME_H
#define FRAME_H

#include "opencv2/core.hpp"


class Frame
{
public:
    explicit Frame(size_t buf_size=1024);
    ~Frame();
    bool IsValid();
    bool ReSize(size_t size);

public:
    uint32_t buf_size;  // buf size;
    uint32_t d_size;  // data size;
    char* buff;  // buff
    int descripter; //

    cv::Mat m_ref; // mat ref
};

#endif // FRAME_H
