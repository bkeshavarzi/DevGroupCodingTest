#include "OPENING.h"

OPENING::OPENING(NODE * ptr)
{
    *NodalPoint=*ptr;
    *(NodalPoint+1)=*(ptr+1);
    *(NodalPoint+2)=*(ptr+2);
    *(NodalPoint+3)=*(ptr+3);
}
void OPENING::GetNode(NODE * ptr)
{
    *ptr=*NodalPoint;
    *(ptr+1)=*(NodalPoint+1);
    *(ptr+2)=*(NodalPoint+2);
    *(ptr+3)=*(NodalPoint+3);
}

OPENING::~OPENING()
{
    //dtor
}
