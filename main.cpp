#include <iostream>
#include "clases/Octree.hpp"
#include "vtk/VTKvis.cpp"
using namespace std;

int menu(){
    int opt;
    cout<<"***Octree***"<<endl;
    cout<<"1.- Visualizar Gato"<<endl;
    cout<<"2.- Visualizar Dragon"<<endl;
    cout<<"3.- Nuevo Octree"<<endl;
    cout<<"0.- Salir"<<endl;
    cout<<"-> Ingrese una opcion: ";
    cin>>opt;
    return opt;
}
int VTKgrafico(){
    int opt;
    cout<<" ***Dimensiones del cubo***"<<endl;
    cout<<" 1.- Dimension total del nodo hoja"<<endl;
    cout<<" 2.- Punto medio del nodo hoja"<<endl;
    cout<<" 3.- Punto que almacena el nodo hoja"<<endl;
    cout<<" -> Ingrese una opcion: ";
    cin>>opt;
    return opt;
}

int funcOctree(){
    int opt;
    cout<<" ***Funciones del Octree**"<<endl;
    cout<<" 1.- Insertar nodo"<<endl;
    cout<<" 2.- Buscar nodo"<<endl;
    cout<<" 3.- Mostrar nodos hoja y nivel"<<endl;
    cout<<" 4.- Salir"<<endl;
    cout<<" -> Ingrese una opcion: ";
    cin>>opt;
    return opt;
}

int main(){
    Octree* root = nullptr;
    int opt, option;
    bool exit = false;
    while(!exit){
        opt = menu();
        switch (opt) {
            case 1:
                root = new Octree({-500, -500, -500}, {500, 500, 500});
                //root = new Octree({-490, 0, -80}, {300, 400, 80});
                option = VTKgrafico();
                printVTK(root,"points1.csv",option);
                delete root;
                root = nullptr;
                break;
            case 2:
                //root = new Octree({-35, -65, 0}, {50, 70, 200});
                root = new Octree({-20000, -20000, -20000}, {20000, 20000, 20000});
                option = VTKgrafico();
                printVTK(root,"points2.csv", option);
                delete root;
                root = nullptr;
                break;
            case 3:{
                root = new Octree({-100, -100, -100}, {100, 100, 100});
                double punto;
                bool sal = false;
                int opti;
                while (!sal) {
                    opti = funcOctree();
                    switch(opti){
                        case 1:{
                            cout<<"Ingresar puntos entre -100 y 100 se puede ser decimal(usar punto: ej. 2.34): ";
                            Point p;
                            cin>>p.x;
                            cin>>p.y;
                            cin>>p.z;
                            root->insert(p);
                            cout<<"Se inserto punto con exito.\n"<<endl;
                            break;
                            }
                        case 2:{
                            cout<<"Ingresar puntos entre -100 y 100 se puede ser decimal(usar punto: ej. 2.34): ";
                            bool res;
                            Point p;
                            cin>>p.x;
                            cin>>p.y;
                            cin>>p.z;
                            res = root->search(p);
                            cout<<(res?"El nodo SI se encuentra en el arbol.\n":"El nodo NO se encunetra en el arbol.\n")<<endl;
                            break;
                            }
                        case 3:
                            root->printNodes();
                            cout<<endl;
                            break;
                        case 4:
                            sal = true;
                            break;
                        }
                    }
                }
                delete root;
                root = nullptr;
                break;
            case 0:
                exit = true;
                break;
        }
    }

    //Octree* root = new Octree({0, 0,0}, {100, 100, 100});
    //root->insert({30,30,30}); // llf
    //root->insert({60,30,30}); // lrf
    //root->insert({30,60,30}); // ulf
    //root->insert({60,60,30}); // urf
    //root->insert({60,60,60}); // urb
    //root->insert({30,60,60}); // ulb
    //root->insert({30,30,60}); // llb
    //root->insert({60,30,60}); // lrb

    //root->insert({10,10,10}); // level2
    //root->printNodes();

    return 0;
}
