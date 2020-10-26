#ifndef OPENING_H
#define OPENING_H
#include "NODE.h"

class OPENING
{
    public:

        OPENING(NODE *);
        void GetNode(NODE *);
        virtual ~OPENING();

    protected:

    private:

        NODE NodalPoint[4];
};

#endif // OPENING_H
