#include "BEAM.h"

BEAM::BEAM()
{

}
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
void BEAM::ShowCord()
{
    double v[2]={0,0};
    NodeObj[0].GetCord(v);
    cout << "Showing Beam Nodal Coordinates :" <<endl;
    cout << "x="<<v[0]<< " " <<"y="<<v[1] <<endl;
    NodeObj[1].GetCord(v);
    cout << "x="<<v[0]<< " " <<"y="<<v[1] <<endl;
}
BEAM::~BEAM()
{
    //dtor
}
