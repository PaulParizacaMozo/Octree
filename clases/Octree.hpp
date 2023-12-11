#include "Point.hpp"

#ifndef OCTREE_H
#define OCTREE_H

class Octree{
    public:
        bool leaf = false;
        Point p;
        //Limits
        Point pMin, pMax, pMid;
        //Pointers to child nodes
        Octree *ulf = nullptr;
        Octree *urf = nullptr;
        Octree *llf = nullptr;
        Octree *lrf = nullptr;
        Octree *ulb = nullptr;
        Octree *urb = nullptr;
        Octree *llb = nullptr;
        Octree *lrb = nullptr;
        //Constructor,Destructor
        Octree(const Point &min, const Point &max);
        Octree(const Octree &q) = delete; // No permite la creacion de objetos mediante copia.
        ~Octree();
        //Functions
        bool inside(const Point & p);
        void insert(const Point &newP);
        bool search(const Point &auxP);
        void printNodes(int level);
        void printNodes();  
};

#endif /* OCTREE_H */
