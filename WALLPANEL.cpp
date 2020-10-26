#include "WALLPANEL.h"

WALLPANEL::WALLPANEL(NODE * ptr)
{
    *NodalPoint=*ptr;
    *(NodalPoint+1)=*(ptr+1);
    *(NodalPoint+2)=*(ptr+2);
    *(NodalPoint+3)=*(ptr+3);
}
void WALLPANEL::SetOpening(OPENING * ptr, int n)
{
    for (int i=0;i<n;i++)
    {
        OpenObj.push_back(*(ptr+i));
    }
}
void WALLPANEL::GetNodalObj(NODE * ptr)
{
    *(ptr)=*NodalPoint;
    *(ptr+1)=*(NodalPoint+1);
    *(ptr+2)=*(NodalPoint+2);
    *(ptr+3)=*(NodalPoint+3);
}
vector <OPENING> WALLPANEL:: GetOpenings()
{
   return  OpenObj;
}
WALLPANEL::~WALLPANEL()
{
    //dtor
}
