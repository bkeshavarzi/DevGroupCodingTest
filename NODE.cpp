#include "NODE.h"

NODE::NODE()
{
    //ctor
}
NODE::NODE(double xc,double yc)
{
    SetCord(xc,yc);
}
void NODE::SetCord(double xc,double yc)
{
    x=xc;
    y=yc;
}
void NODE::GetCord(double * ptr)
{
    *ptr=x;
    *(ptr+1)=y;
}
NODE::~NODE()
{
    //dtor
}
