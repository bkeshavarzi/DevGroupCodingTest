#include "BEAM.h"

BEAM::BEAM(NODE * ptr)
{
    *(NodeObj)=*(ptr);
    *(NodeObj+1)=*(ptr+1);
}
void BEAM::GetNodeObj(NODE * ptr)
{
    *(ptr)=*NodeObj;
    *(ptr+1)=*(NodeObj+1);
}
BEAM::~BEAM()
{
    //dtor
}
