#ifndef PROTOTCP_H
#define PROTOTCP_H


#include "./protobase.h"

class ProtoTcp : public ProtoBase
{
public:
    ProtoTcp();
    virtual ~ProtoTcp();

    virtual Frame* PackData(cv::Mat data);


};

#endif // PROTOTCP_H
