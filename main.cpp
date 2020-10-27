#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "NODE.h"
#include "OPENING.h"
#include "WALLPANEL.h"
#include "Beam.h"
using namespace std;

vector <BEAM> PanelIntersect(BEAM,WALLPANEL);   // This function finds the intersection of the beam with the wall panel.
vector <BEAM> OpeningIntersect(BEAM,WALLPANEL); // This function finds the intersection of the beam with the opening.
bool intersect(NODE,NODE,NODE,NODE,NODE *);     // This function finds the intersection points of two given beams

int main()
{
    //Define the wall panel
    NODE obj1(10,30),obj2(20,40),obj3(20,10),obj4(10,10);
    NODE no[4]={obj1,obj2,obj3,obj4};
    WALLPANEL wp(no); // The wall panel object is wp.
    //Define the openings
    NODE obj5(12,28),obj6(14,28),obj7(14,20),obj8(12,20);         //Opening #1
    no[0]=obj5;no[1]=obj6;no[2]=obj7;no[3]=obj8;
    OPENING op1(no);
    NODE obj9(17,26),obj10(17.3,26),obj11(17.3,18),obj12(17,18);  //Opening #2
    no[0]=obj9;no[1]=obj10;no[2]=obj11;no[3]=obj12;
    OPENING op2(no);
    NODE obj13(18,30),obj14(19,30),obj15(19,12),obj16(18,12);     //Opening #3
    no[0]=obj13;no[1]=obj14;no[2]=obj15;no[3]=obj16;
    OPENING op3(no);
    //Assign openings
    OPENING opv[3]={op1,op2,op3};
    wp.SetOpening(opv,3);
    //Define Beam
    NODE obj17(8,17),obj18(23,32);
    NODE no_b[2]={obj17,obj18};
    BEAM bo(no_b);
    //find the segment(s) after panel intersection
    vector <BEAM> outside_beam_intersection =PanelIntersect(bo,wp);  //Calculate the outsider portion of beam wrt to the wall panel
    vector <BEAM> inside_beam_intersection =OpeningIntersect(bo,wp); //Calculate the insider portion of beam wrt to openings

    int n=outside_beam_intersection.size();
    int m=inside_beam_intersection.size();

    cout << "**********RESULTS***********"<<endl;
    cout << "Number of beam segments located outside the wall panel are :"<<"\t"<<n<<endl;
    cout << "Number of beam segments located inside the opening(s) are :"<<"\t"<<m<<endl;
    if (n!=0)
    {
        for (int ibeam=0;ibeam<n;ibeam++)
        {
            cout << "Beam outsider # "<<"\t"<<ibeam+1<<endl;
            outside_beam_intersection[ibeam].ShowCord();
            cout<<"*******************************************"<<endl;
        }
    }
    if (m!=0)
    {
        for (int ibeam=0;ibeam<m;ibeam++)
        {
            cout << "Beam outsider # "<<"\t"<<ibeam+1<<endl;
            inside_beam_intersection[ibeam].ShowCord();
            cout<<"*******************************************"<<endl;
        }
    }
}


vector <BEAM> PanelIntersect(BEAM b,WALLPANEL w)
{
    NODE nwobj[4];          //four nodes of the wall panel
    w.GetNodalObj(nwobj);   //getting the four nodes of the wall panel
    NODE nbobj[2];          //two nodes for the beam
    b.GetNodeObj(nbobj);    //getting the two nodes for the beam
    NODE obj;
    vector <NODE> NV;       // a vector container for storing nodal points  (nv==nodal vector)
    vector <BEAM> BV;       // a vector container for storing beam segments (bv==beam vector)
    double v1[2]={0,0},v2[2]={0,0},v3[2]={0,0},v4[2]={0,0}; //defining four lists for storing nodal coordinates

    if(intersect(nbobj[0],nbobj[1],nwobj[0],nwobj[1],&obj)==true) (NV.push_back(obj)); //finding the intersection of the beam and wall panel's vertical member on the left
    if(intersect(nbobj[0],nbobj[1],nwobj[1],nwobj[2],&obj)==true) (NV.push_back(obj)); //finding the intersection of the beam and wall panel's top member
    if(intersect(nbobj[0],nbobj[1],nwobj[2],nwobj[3],&obj)==true) (NV.push_back(obj)); //finding the intersection of the beam and wall panel's vertical member on the right
    if(intersect(nbobj[0],nbobj[1],nwobj[3],nwobj[0],&obj)==true) (NV.push_back(obj)); //finding the intersection of the beam and wall panel's horizontal member at the floor

    nbobj[0].GetCord(v1); //storing the coordinate of the beam's first point in v1
    nbobj[1].GetCord(v2); //storing the coordinate of the beam's first point in v2

    if(NV.size()==2) //if the beam intersects the wall panel at two points, this gives us two beams located outside of the wall panel.
    {
      int id_min_beam=(v1[0]>=v2[0]?2:1); //assigning the id of beam point with lower  x value
      int id_max_beam=(v1[0]>=v2[0]?1:2); //assigning the id of beam point with higher x value

      NV[0].GetCord(v3); //Coordinate of first intersection point
      NV[1].GetCord(v4); //Coordinate of second intersection point

      int id_min_inter=(v3[0]>=v4[0]?2:1); //assigning the id of intersection point with lower  x value
      int id_max_inter=(v3[0]>=v4[0]?1:2); //assigning the id of intersection point with higher  x value

      NODE n1[2]={nbobj[id_min_beam-1],NV[id_min_inter-1]}; //defining a list with two nodes; one node is from beam and another from intersection. This constitutes one of the outer segment.
      NODE n2[2]={nbobj[id_max_beam-1],NV[id_max_inter-1]}; //defining a list with two nodes; one node is from beam and another from intersection. This constitutes one of the outer segment.

      BEAM b1(n1),b2(n2); //storing beam elements

      BV.push_back(b1);   //storing first beam element
      BV.push_back(b2);   //storing second beam element
    }
    if(NV.size()==1) //if the beam intersects the wall panel at one points, this gives us one beam located outside of the wall panel.
    {                //We need to detect which beam's point is located inside the wall panel and which one lies outside.
      nwobj[0].GetCord(v1); //storing the 1st point of the wall panel
      nwobj[1].GetCord(v2); //storing the 2nd point of the wall panel
      nwobj[2].GetCord(v3); //storing the 3rd point of the wall panel
      nwobj[3].GetCord(v4); //storing the 4th point of the wall panel
      double xc_min=(v1[0]>=v2[0]?v2[0]:v1[0]);xc_min=(v3[0]>=xc_min?xc_min:v3[0]);xc_min=(v4[0]>=xc_min?xc_min:v4[0]); //finding the minimum x coordinate of the wall panel
      double xc_max=(v1[0]>=v2[0]?v1[0]:v2[0]);xc_max=(v3[0]>=xc_max?v3[0]:xc_max);xc_max=(v4[0]>=xc_max?v4[0]:xc_max); //finding the maximum x coordinate of the wall panel
      double yc_min=(v1[1]>=v2[1]?v2[1]:v1[1]);yc_min=(v3[1]>=yc_min?yc_min:v3[1]);yc_min=(v4[1]>=yc_min?yc_min:v4[1]); //finding the minimum y coordinate of the wall panel
      double yc_max=(v1[1]>=v2[1]?v1[1]:v2[1]);yc_max=(v3[1]>=yc_max?v3[1]:yc_max);yc_max=(v4[1]>=yc_max?v4[1]:yc_max); //finding the maximum y coordinate of the wall panel
      nbobj[0].GetCord(v1); //getting the coordinate of the 1st beam nodal point
      nbobj[1].GetCord(v2); //getting the coordinate of the 2nd beam nodal point
      int id;
      //finding the point inside the wall panel and assigning an id to it.
      if (((v1[0]>=xc_min) && (v1[0]<=xc_max)) && ((v1[1]>=yc_min)&&(v1[1]<=yc_max))) id=1;
      if (((v2[0]>=xc_min) && (v2[0]<=xc_max)) && ((v2[1]>=yc_min)&&(v2[1]<=yc_max))) id=2;
      //storing the list of nodes
      NODE n1[2]={nbobj[id-1],NV[0]};
      BV.push_back(n1); //making a beam element
    }
    return BV;
}

vector <BEAM> OpeningIntersect(BEAM b,WALLPANEL w)
{
    vector <OPENING> OV = w.GetOpenings(); // getting opening(s) inside the wall panel
    NODE nwobj[4];
    w.GetNodalObj(nwobj);
    NODE nbobj[2];
    b.GetNodeObj(nbobj);
    NODE obj;
    vector <NODE> NV;
    vector <BEAM> BV;
    int counter=-1;

    for (int iopen=0; iopen<OV.size(); iopen++) //for each opening

    {
        OV[iopen].GetNode(nwobj); //getting the nodal points for an opening
        //finding the intersection
        if(intersect(nbobj[0],nbobj[1],nwobj[0],nwobj[1],&obj)==true) (NV.push_back(obj));
        if(intersect(nbobj[0],nbobj[1],nwobj[1],nwobj[2],&obj)==true) (NV.push_back(obj));
        if(intersect(nbobj[0],nbobj[1],nwobj[2],nwobj[3],&obj)==true) (NV.push_back(obj));
        if(intersect(nbobj[0],nbobj[1],nwobj[3],nwobj[0],&obj)==true) (NV.push_back(obj));
    }

    NODE n[2]={nbobj[0],nbobj[1]};
    if (NV.size()>1)
    {
      for (int imember=0;imember<floor(NV.size()/2)*2;imember=imember+2) //getting two intersection points
      {
        n[0]=NV[imember];
        n[1]=NV[imember+1];
        BEAM b(n);
        BV.push_back(b);
      }
    }
    return BV;
}

bool intersect(NODE n1,NODE n2,NODE n3,NODE n4,NODE * obj)
{
    //This function calculate the intersection of two lines and returns the intersection point.
    //It considers the possibility that one or two of those lines be vertical (i.e., slope=inf)
    double m1,b1,m2,b2; //y=m*x+b
    double v1[2],v2[2],v3[2],v4[2];
    double xint,yint;
    double max_x_1,min_x_1,max_x_2,min_x_2,max_y_1,min_y_1,max_y_2,min_y_2;
    string str1,str2;
    bool res;

    n1.GetCord(v1);
    n2.GetCord(v2);
    //beam element

    if (v1[0]!=v2[0])
    {
        str1="Type1"; //titlted line
        m1=(v2[1]-v1[1])/(v2[0]-v1[0]);
        b1=v2[1]-m1*v2[0];

    }else if (v1[0]==v2[0])
    {
        str1="Type2"; //vertical line, slope is inf.
    }

    max_x_1=(v1[0]>=v2[0]?v1[0]:v2[0]);max_y_1=(v1[1]>=v2[1]?v1[1]:v2[1]);
    min_x_1=(v1[0]>=v2[0]?v2[0]:v1[0]);min_y_1=(v1[1]>=v2[1]?v2[1]:v1[1]);

    n3.GetCord(v3);
    n4.GetCord(v4);
    //wall panel or opening element
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

    if ((str1=="Type1") && (str2=="Type1"))
    {
        if (m1!=m2)
        {
            xint=(b2-b1)/(m1-m2);
            yint=m1*xint+b1;
            if ((xint>=min_x_1)&&(xint<=max_x_1)&&(xint>=min_x_2)&&(xint<=max_x_2))
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
            obj->SetCord(0,0);
        }
    }

    if ((str1=="Type1") && (str2=="Type2"))
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

    if ((str1=="Type2")&&(str2=="Type1"))
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
    if ((str1=="Type2")&&(str2=="Type2"))
    {
        res=false;
        obj -> SetCord(0,0);
    }

    return res;

}
