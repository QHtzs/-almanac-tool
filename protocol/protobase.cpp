#include "protobase.h"

ProtoBase::ProtoBase()
{

}

ProtoBase::~ProtoBase()
{
    for(Frame* hd: m_hold.values()){
        delete  hd;
        hd = nullptr;
    }
}
