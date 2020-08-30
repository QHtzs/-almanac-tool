#include "frame.h"

#include <memory>

Frame::Frame(size_t buf_size)
{
    this->descripter = -1;
    this->m_ref = cv::Mat();
    this->buf_size = buf_size;
    this->d_size = 0;
    this->buff = reinterpret_cast<char*>(malloc(buf_size));
}

Frame::~Frame()
{
    free(buff);
}

bool Frame::IsValid()
{
    return this->descripter != -1;
}

bool Frame::ReSize(size_t size)
{
    auto ptr = reinterpret_cast<char*>(realloc(buff, size));
    if(ptr == nullptr){
        return false;
    }else{
        if(ptr != buff) free(buff);
         buff = ptr;
         d_size = 0;
         buf_size = size;
    }
    return true;
}
