#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class NODE
{
    public:

        NODE();
        NODE(double,double);
        void SetCord(double,double);
        void GetCord(double *);
        virtual ~NODE();

    protected:

    private:

        double x,y;
};

#endif // NODE_H
