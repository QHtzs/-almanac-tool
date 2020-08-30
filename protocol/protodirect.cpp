#include "protodirect.h"


ProtoDirect::ProtoDirect()
{

}

ProtoDirect::~ProtoDirect(){

}

Frame* ProtoDirect::PackData(cv::Mat data)
{
    // no atomic
    Qt::HANDLE id = QThread::currentThreadId();
    Frame* frame = m_hold.value(id, nullptr);
    if(frame == nullptr){
        frame = new Frame();
        m_mutex.lock();
        m_hold[id] = frame;
        m_mutex.unlock();
    }
    frame->descripter = 0;
    frame->m_ref = data;
    return frame;
}
