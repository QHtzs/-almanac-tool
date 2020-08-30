#include "prototcp.h"

/// cast to pack, big endian
///  [HEAD]2b [WIDTH]2b [HEIGHT]2b  [CHANNEL]2b [DATA] WIDTH*HEIGHT*CHANNEL [LENTH]4b [TAIL]2b
static void cast_to_bytes(cv::Mat m, Frame *& dst){
    int size = m.rows * m.cols * m.channels();
    size_t b_size = static_cast<size_t>(2+2+2+2+ size +4+2);
    if(b_size > dst->buf_size){
        bool ok = dst->ReSize(b_size);
        if(!ok) return;
    }
    dst->d_size = b_size;
    char * buf = dst->buff;

    int index = 0;
    buf[index++] = 'H';
    buf[index++] = 'D';

    buf[index++] = (m.cols >> 8) & 0xff;
    buf[index++] = m.cols & 0xff;

    buf[index++] = (m.rows >> 8) & 0xff;
    buf[index++] = m.rows & 0xff;

    buf[index++] = (m.channels() >> 8) & 0xff;
    buf[index++] = m.channels() & 0xff;


    int nl = m.rows;
    int nc = m.cols * m.channels();
    for(int j=0; j<nl ;++j)
    {
       uchar *data = m.ptr<uchar>(j);
       for(int i=0; i<nc; ++i) buf[index++] = data[i];
    }
    buf[index++] = (size >> 24) & 0xff;
    buf[index++] = (size >> 16) & 0xff;
    buf[index++] = (size >> 8) & 0xff;
    buf[index++] = size & 0xff;

    buf[index++] = 'T';
    buf[index++] = 'L';
}


ProtoTcp::ProtoTcp()
{

}


ProtoTcp::~ProtoTcp()
{

}


Frame* ProtoTcp::PackData(cv::Mat data)
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
    cast_to_bytes(data, frame);
    return frame;
}
