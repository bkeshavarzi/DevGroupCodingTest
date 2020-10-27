#include <iostream>
#ifndef BEAM_H
#define BEAM_H
#include "NODE.h"

class BEAM
{
    public:
        BEAM();
        BEAM(NODE *);
        void GetNodeObj(NODE *);
        void ShowCord();
        virtual ~BEAM();

    protected:

    private:

        NODE NodeObj [2];
};

#endif // BEAM_H
