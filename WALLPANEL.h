#include <iostream>
#ifndef WALLPANEL_H
#define WALLPANEL_H
#include <vector>
#include "NODE.h"
#include "OPENING.h"

using namespace std;

class WALLPANEL
{
    public:

        WALLPANEL(NODE *);
        void SetOpening(OPENING *,int);
        void GetNodalObj(NODE *);
        vector <OPENING> GetOpenings();
        virtual ~WALLPANEL();

    protected:

    private:

        NODE NodalPoint[4];
        vector <OPENING> OpenObj;
};

#endif // WALLPANEL_H
