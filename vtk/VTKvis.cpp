#include "../clases/Octree.cpp"

#include <ios>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int nPuntos = 0;

void calculateCubePoints(vector<double>p1, vector<double>p2, double pointsArray[8][3]) {
    // Esquina inferior izquierda (p1)
    pointsArray[0][0] = p1[0];
    pointsArray[0][1] = p1[1];
    pointsArray[0][2] = p1[2];

    // Esquina superior derecha (p2)
    pointsArray[6][0] = p2[0];
    pointsArray[6][1] = p2[1];
    pointsArray[6][2] = p2[2];

    //  otras esquinas
    pointsArray[1][0] = p2[0];
    pointsArray[1][1] = p1[1];
    pointsArray[1][2] = p1[2];

    pointsArray[2][0] = p2[0];
    pointsArray[2][1] = p2[1];
    pointsArray[2][2] = p1[2];

    pointsArray[3][0] = p1[0];
    pointsArray[3][1] = p2[1];
    pointsArray[3][2] = p1[2];

    pointsArray[4][0] = p1[0];
    pointsArray[4][1] = p1[1];
    pointsArray[4][2] = p2[2];

    pointsArray[5][0] = p2[0];
    pointsArray[5][1] = p1[1];
    pointsArray[5][2] = p2[2];

    pointsArray[7][0] = p1[0];
    pointsArray[7][1] = p2[1];
    pointsArray[7][2] = p2[2];
}

void printNodesVtk(const Octree *q, vtkSmartPointer<vtkRenderer> & renderer,const int tipo){
    if (q->leaf) {
        nPuntos++;
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        vector<double> p1, p2;

        switch (tipo) {
            case 1: //Imprimir nodo segun sus dimensiones del cubo
                p1 = {q->pMin.x, q->pMin.y, q->pMin.z};
                p2 = {q->pMax.x, q->pMax.y, q->pMax.z};
                break;
            case 2: //Imprimir punto medio del cubo
                p1 = {q->pMid.x, q->pMid.y, q->pMid.z};  // Esquina inferior izquierda
                p2 = {q->pMid.x+3, q->pMid.y+3, q->pMid.z+3};  // Esquina superior derecha
                break;
            case 3: 
                p1 = {q->p.x, q->p.y, q->p.z};  // Esquina inferior izquierda
                p2 = {q->p.x+3, q->p.y+3, q->p.z+3};  // Esquina superior derecha
                break;
        }
        
        //Imprimir punto del nodo 
        double pointsArray[8][3];
        calculateCubePoints(p1, p2, pointsArray);

        // Añadir los puntos al conjunto
        for (int j = 0; j < 8; ++j) {
            points->InsertNextPoint(pointsArray[j]);
        }

        // Crear un objeto vtkPolyData y añadir los puntos
        vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
        polyData->SetPoints(points);

        // Definir las caras del cubo
        vtkSmartPointer<vtkCellArray> faces = vtkSmartPointer<vtkCellArray>::New();
        vtkIdType face0[4] = {0, 1, 5, 4};
        vtkIdType face1[4] = {1, 2, 6, 5};
        vtkIdType face2[4] = {2, 3, 7, 6};
        vtkIdType face3[4] = {3, 0, 4, 7};
        vtkIdType face4[4] = {0, 3, 2, 1};
        vtkIdType face5[4] = {4, 5, 6, 7};
        faces->InsertNextCell(4, face0);
        faces->InsertNextCell(4, face1);
        faces->InsertNextCell(4, face2);
        faces->InsertNextCell(4, face3);
        faces->InsertNextCell(4, face4);
        faces->InsertNextCell(4, face5);

        // Añadir las caras al objeto vtkPolyData
        polyData->SetPolys(faces);

        // Crear un mapeador para el objeto vtkPolyData
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(polyData);

        // Crear un actor y establecer el mapeador
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);

        // Añadir el actor al renderizador
        renderer->AddActor(actor);

        //cout<<q->p<<endl;
        return;
    }

    if(q->ulf){
        printNodesVtk(q->ulf, renderer, tipo);
        printNodesVtk(q->urf, renderer, tipo);
        printNodesVtk(q->llf, renderer, tipo);
        printNodesVtk(q->lrf, renderer, tipo);
        printNodesVtk(q->ulb, renderer, tipo);
        printNodesVtk(q->urb, renderer, tipo);
        printNodesVtk(q->llb, renderer, tipo);
        printNodesVtk(q->lrb, renderer, tipo);
    }
}


void printVTK(Octree * root,string nameFile,const int tipo) {
    //Octree* root = new Octree({-200, -200, -200}, {200, 200, 200});
    // Llama a la función para insertar puntos desde el archivo CSV
    insertPointsFromFile(nameFile, root);
    // Crear un renderizador
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    printNodesVtk(root, renderer, tipo);

    cout<<"Se insertaron "<<nPuntos<<" en el Octree."<<endl;
    nPuntos=0;
    // Crear una ventana de renderizado y añadir el renderizador
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // Crear un interactor y establecer la ventana de renderizado
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Iniciar el bucle de eventos
    renderWindow->Render();
    renderWindowInteractor->Start();
    //char c;
    //cin>>c;
    //if(c == 'x'){
    //    renderWindow->Finalize();
    //}
}
