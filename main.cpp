#include <iostream>
#include <string>
#include "NODE.h"
#include "OPENING.h"
#include "WALLPANEL.h"
#include "Beam.h"
using namespace std;

vector <BEAM> PanelIntersect(BEAM,WALLPANEL);
vector <BEAM> OpeningIntersect(BEAM,WALLPANEL);
bool intersect(NODE,NODE,NODE,NODE,NODE *);

int main()
{
    //Define the wall panel
    NODE obj1(10,30),obj2(20,40),obj3(20,10),obj4(10,10);
    NODE no[4]={obj1,obj2,obj3,obj4};
    WALLPANEL wp(no);
    //Define the openings
    NODE obj5(12,28),obj6(14,28),obj7(14,20),obj8(12,20);         //Opening #1
    no[0]=obj5;no[1]=obj6;no[2]=obj7;no[3]=obj8;
    OPENING op1(no);
    NODE obj9(17,26),obj10(17.3,26),obj11(17.3,18),obj12(17,18);  //Opening #2
    no[0]=obj9;no[1]=obj10;no[2]=obj11;no[3]=obj12;
    OPENING op2(no);
    NODE obj13(17,26),obj14(17.3,26),obj15(17.3,18),obj16(17,18);  //Opening #3
    no[0]=obj13;no[1]=obj14;no[2]=obj15;no[3]=obj16;
    OPENING op3(no);
    //Assign openings
    OPENING opv[3]={op1,op2,op3};
    wp.SetOpening(opv,3);
    //Define Beam
    NODE obj17(8,17),obj18(23,32);
    NODE no_b[2]={obj17,obj18};
    BEAM bo(no_b);
    return 0;
}


vector <BEAM> PanelIntersect(BEAM b,WALLPANEL w)
{
    NODE nwobj[4];
    w.GetNodalObj(nwobj);
    NODE nbobj[2];
    b.GetNodeObj(nbobj);
    NODE * obj,* inernode, * outernode;
    vector <NODE> NV;
    vector <BEAM> BV;
    double v1[2]={0,0},v2[2]={0,0},v3[2]={0,0},v4[2]={0,0};

    if(intersect(nbobj[0],nbobj[1],nwobj[0],nwobj[1],obj)==true) (NV.push_back(*obj));
    if(intersect(nbobj[0],nbobj[1],nwobj[1],nwobj[2],obj)==true) (NV.push_back(*obj));
    if(intersect(nbobj[0],nbobj[1],nwobj[2],nwobj[3],obj)==true) (NV.push_back(*obj));
    if(intersect(nbobj[0],nbobj[1],nwobj[3],nwobj[0],obj)==true) (NV.push_back(*obj));

    //Fill Outside wall panel vector

    nbobj[0].GetCord(v1);
    nbobj[1].GetCord(v2);
    double d1,d2,d3,d4;

    if(NV.size()==2)
    {
      int id_min_beam=(v1[0]>=v2[0]?2:1);
      int id_max_beam=(v1[0]>=v2[0]?1:2);
      NV[0].GetCord(v3);
      NV[1].GetCord(v4);
      int id_min_inter=(v3[0]>=v4[0]?2:1);
      int id_max_inter=(v3[0]>=v4[0]?1:2);
      NODE n1[2]={nbobj[id_min_beam-1],NV[id_min_inter-1]};
      NODE n2[2]={nbobj[id_max_beam-1],NV[id_max_inter-1]};
      BEAM b1(n1),b2(n2);
      BV.push_back(b1);
      BV.push_back(b2);
    }
    if(NV.size()==1)
    {
      nwobj[0].GetCord(v1);
      nwobj[1].GetCord(v2);
      nwobj[2].GetCord(v3);
      nwobj[3].GetCord(v4);
      double xc_min=(v1[0]>=v2[0]?v2[0]:v1[0]);xc_min=(v3[0]>=xc_min?xc_min:v3[0]);xc_min=(v4[0]>=xc_min?xc_min:v4[0]);
      double xc_max=(v1[0]>=v2[0]?v1[0]:v2[0]);xc_max=(v3[0]>=xc_max?v3[0]:xc_max);xc_max=(v4[0]>=xc_max?v4[0]:xc_max);
      double yc_min=(v1[1]>=v2[1]?v2[1]:v1[1]);yc_min=(v3[1]>=yc_min?yc_min:v3[1]);yc_min=(v4[1]>=yc_min?yc_min:v4[1]);
      double yc_max=(v1[1]>=v2[1]?v1[1]:v2[1]);yc_max=(v3[1]>=yc_max?v3[1]:yc_max);yc_max=(v4[1]>=yc_max?v4[1]:yc_max);
      nbobj[0].GetCord(v1);
      nbobj[1].GetCord(v2);
      int id;
      if (((v1[0]>=xc_min) && (v1[0]<=xc_max)) && ((v1[1]>=yc_min)&&(v1[1]<=yc_max))) id=1;
      if (((v2[0]>=xc_min) && (v2[0]<=xc_max)) && ((v2[1]>=yc_min)&&(v2[1]<=yc_max))) id=2;
      NODE n1[2]={nbobj[id-1],NV[0]};
      BV.push_back(n1);
    }
}

vector <BEAM> OpeningIntersect(BEAM b,WALLPANEL w)
{
    vector <OPENING> OV = w.GetOpenings();
    NODE nwobj[4];
    w.GetNodalObj(nwobj);
    NODE nbobj[2];
    b.GetNodeObj(nbobj);
    NODE * obj,* inernode, * outernode;
    vector <NODE> NV;
    vector <BEAM> BV;
    int counter=-1;

    for (int iopen=0; iopen<OV.size(); iopen++)
    {
        OV[iopen].GetNode(nwobj);
        if(intersect(nbobj[0],nbobj[1],nwobj[0],nwobj[1],obj)==true) (NV.push_back(*obj));
        if(intersect(nbobj[0],nbobj[1],nwobj[1],nwobj[2],obj)==true) (NV.push_back(*obj));
        if(intersect(nbobj[0],nbobj[1],nwobj[2],nwobj[3],obj)==true) (NV.push_back(*obj));
        if(intersect(nbobj[0],nbobj[1],nwobj[3],nwobj[0],obj)==true) (NV.push_back(*obj));
    }

    NODE n[2]={nbobj[0],nbobj[1]};
    for (int imember=0;imember<NV.size();imember=imember+2)
    {
        n[0]=NV[imember];
        n[1]=NV[imember+1];
        BEAM b(n);
        BV.push_back(b);
    }

}

bool intersect(NODE n1,NODE n2,NODE n3,NODE n4,NODE * obj)
{
    double m1,b1,m2,b2; //y=m*x+b
    double v1[2],v2[2],v3[2],v4[2];
    double xint,yint;
    double max_x_1,min_x_1,max_x_2,min_x_2,max_y_1,min_y_1,max_y_2,min_y_2;
    string str1,str2;
    bool res;

    n1.GetCord(v1);
    n2.GetCord(v2);

    if (v1[0]!=v2[0])
    {
        str1="Type1";
        m1=(v2[1]-v1[1])/(v2[0]-v1[0]);
        b1=v2[1]-m1*v2[0];

    }else if (v1[0]==v2[0])
    {
        str1="Type2";
    }

    max_x_1=(v1[0]>=v2[0]?v1[0]:v2[0]);max_y_1=(v1[1]>=v2[1]?v1[1]:v2[1]);
    min_x_1=(v1[0]>=v2[0]?v2[0]:v1[0]);min_y_1=(v1[1]>=v2[1]?v2[1]:v1[1]);

    n3.GetCord(v3);
    n4.GetCord(v4);

    if (v3[0]!=v4[0])
    {
        str2="Type1";
        m2=(v4[1]-v3[1])/(v4[0]-v3[0]);
        b2=v4[1]-m2*v3[0];
    }else if (v3[0]==v4[0])
    {
        str2="Type2";
    }

    max_x_2=(v4[0]>=v3[0]?v4[0]:v3[0]);max_y_2=(v4[1]>=v3[1]?v4[1]:v3[1]);
    min_x_2=(v4[0]>=v3[0]?v3[0]:v4[0]);min_y_2=(v4[1]>=v3[1]?v3[1]:v4[1]);

    if (str1=="Type1" && str2=="Type2")
    {
        if (m1!=m2)
        {
            xint=(b2-b1)/(m1-m2);
            yint=m1*xint+b1;
            if (((xint>=min_x_1)&&(xint<=max_x_1)) && ((xint>=min_x_2)&&(xint<=max_x_2)))
            {
                res=true;
                obj -> SetCord(xint,yint);
            } else
            {
                res=false;
                obj -> SetCord(0,0);
            }
        } else if (m1==m2)
        {
            res=false;
            obj -> SetCord(0,0);
        }
    }

    if (str1=="Type1",str2=="Type2")
    {
        xint=v3[0];
        yint=m1*xint+b1;
        if (((xint>=min_x_1)&&(xint<=max_x_1)) && ((yint>=min_y_2)&&(yint<=max_y_2)))
        {
            res=true;
            obj -> SetCord(xint,yint);
        } else
        {
            res=false;
            obj -> SetCord(0,0);
        }
    }

    if (str1=="Type2",str2=="Type1")
    {
        xint=v1[0];
        yint=m2*xint+b2;
        if (((xint>=min_x_2)&&(xint<=max_x_2)) && ((yint>=min_y_1)&&(yint<=max_y_1)))
        {
            res=true;
            obj -> SetCord(xint,yint);
        } else
        {
            res=false;
            obj -> SetCord(0,0);
        }
    }

    if (str1=="Type2",str2=="Type1")
    {
        res=false;
        obj -> SetCord(0,0);
    }

    return res;

}
