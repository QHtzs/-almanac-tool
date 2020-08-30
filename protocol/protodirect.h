#ifndef PROTODIRECT_H
#define PROTODIRECT_H

#include "./protobase.h"

class ProtoDirect : public ProtoBase
{
public:
    ProtoDirect();
    virtual ~ProtoDirect();

    virtual Frame* PackData(cv::Mat data);
};

#endif // PROTODIRECT_H
