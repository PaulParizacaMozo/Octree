#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <vector>
#include "Octree.hpp"
using namespace std;

//Constructor
Octree::Octree(const Point &min, const Point &max) : pMin(min), pMax(max) {
    pMid.x = (pMin.x + pMax.x) / 2;
    pMid.y = (pMin.y + pMax.y) / 2;
    pMid.z = (pMin.z + pMax.z) / 2;
}

//Destructor
Octree::~Octree(){
    delete ulf;
    delete urf;
    delete llf;
    delete lrf;
    delete ulb;
    delete urb;
    delete llb;
    delete lrb;
}

bool Octree::inside(const Point & p){
    return((pMin.x <= p.x) && (p.x < pMax.x) && (pMin.y <= p.y) && (p.y < pMax.y) && (pMin.z <= p.z) && (p.z < pMax.z));
}

void Octree::insert(const Point &newP){            
    //first case - node perfect
    if(!leaf && !ulf){
        leaf = true;
        this->p = newP;
        //cout<<"its ok"<<newP<<"\n";
        return;
    }
    //Second case - node equal to other node
    if(newP == this->p){
        cout<<"Duplicated\n";
        return;} // Discard duplicates

    //Third case - split current node into 4 nodes
    leaf = false;
    if(ulf == nullptr){
        ulf = new Octree({pMin.x,pMid.y,pMin.z},{pMid.x, pMax.y, pMid.z}); //ok
        urf = new Octree({pMid.x,pMid.y,pMin.z},{pMax.x, pMax.y, pMid.z}); //ok
        llf = new Octree(pMin,pMid); //ok
        lrf = new Octree({pMid.x, pMin.y, pMin.z}, {pMax.x, pMid.y, pMid.z}); //ok
        ulb = new Octree({pMin.x,pMid.y,pMid.z},{pMid.x, pMax.y, pMax.z});
        urb = new Octree(pMid,pMax); //ok
        llb = new Octree({pMin.x, pMin.y, pMid.z}, {pMid.x, pMid.y, pMax.z});
        lrb = new Octree({pMid.x, pMin.y, pMid.z}, {pMax.x, pMid.y, pMax.z}); //ok
        if (ulf->inside(this->p)) { ulf->insert(this->p);}
        if (urf->inside(this->p)) { urf->insert(this->p);}
        if (llf->inside(this->p)) { llf->insert(this->p);}
        if (lrf->inside(this->p)) { lrf->insert(this->p);}
        if (ulb->inside(this->p)) { ulb->insert(this->p);}
        if (urb->inside(this->p)) { urb->insert(this->p);}
        if (llb->inside(this->p)) { llb->insert(this->p);}
        if (lrb->inside(this->p)) { lrb->insert(this->p);}
    }
    if (ulf->inside(newP)) { ulf->insert(newP);}
    if (urf->inside(newP)) { urf->insert(newP);}
    if (llf->inside(newP)) { llf->insert(newP);}
    if (lrf->inside(newP)) { lrf->insert(newP);}
    if (ulb->inside(newP)) { ulb->insert(newP);}
    if (urb->inside(newP)) { urb->insert(newP);}
    if (llb->inside(newP)) { llb->insert(newP);}
    if (lrb->inside(newP)) { lrb->insert(newP);}
}

bool Octree::search(const Point &auxP){
    if(leaf){
        if(this->p == auxP){
            return true;   
        }
        else { return false; }
    }
    if (ulf && ulf->inside(auxP)) { return ulf->search(auxP);}
    if (urf && urf->inside(auxP)) { return urf->search(auxP);}
    if (llf && llf->inside(auxP)) { return llf->search(auxP);}
    if (lrf && lrf->inside(auxP)) { return lrf->search(auxP);}
    if (ulb && ulb->inside(auxP)) { return ulb->search(auxP);}
    if (urb && urb->inside(auxP)) { return urb->search(auxP);}
    if (llb && llb->inside(auxP)) { return llb->search(auxP);}
    if (lrb && lrb->inside(auxP)) { return lrb->search(auxP);}
    return false;
}

void Octree::printNodes(int level){
    if (leaf) {
        cout<<"Level "<<level<<": "<<p<<endl;
        return;
    }
    if (ulf) {
        level++;
        ulf->printNodes(level);
        urf->printNodes(level);
        llf->printNodes(level);
        lrf->printNodes(level);
        ulb->printNodes(level);
        urb->printNodes(level);
        llb->printNodes(level);
        lrb->printNodes(level);
    }
}

void Octree::printNodes(){
    return printNodes(0);
}

void insertPointsFromFile(const string& filename, Octree* root) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        double x, y, z;

        // Lee los valores x, y, z del formato x,y,z
        char discard;
        if (ss >> x >> discard >> y >> discard >> z) {
            root->insert({x, y, z});
        } else {
            cerr << "Error al leer la línea: " << line << endl;
        }
    }
    file.close();
}
