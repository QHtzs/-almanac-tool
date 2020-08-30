#ifndef PROTOBASE_H
#define PROTOBASE_H


#include "./frame.h"
#include <QMap>
#include <QThread>
#include <QMutex>


class ProtoBase
{
public:
    ProtoBase();
    virtual ~ProtoBase();

    virtual Frame* PackData(cv::Mat data) = 0;

protected:
    QMap<Qt::HANDLE, Frame*> m_hold;
    QMutex m_mutex;

};

#endif // PROTOBASE_H
