#include <iostream>

#ifndef POINT_H
#define POINT_H

class Point{

    public:
        double  x = 0;
        double  y = 0;
        double  z = 0;
        bool operator== (const Point &p) const{
            return (x == p.x) && (y == p.y) && (z == p.z);
        }
        friend std::ostream& operator<< (std::ostream &out, const Point &p){
            return out <<"("<<p.x<<","<<p.y<<","<<p.z<<")";
        }
};

#endif /* POINT_H */
