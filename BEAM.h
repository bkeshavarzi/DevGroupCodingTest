#include <iostream>
#ifndef BEAM_H
#define BEAM_H
#include "NODE.h"

class BEAM
{
    public:
        BEAM(NODE *);
        void GetNodeObj(NODE *);
        virtual ~BEAM();

    protected:

    private:

        NODE NodeObj [2];
};

#endif // BEAM_H
