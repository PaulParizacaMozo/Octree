# IMPLEMENTACIÓN DEL OCTREE Y LA VISUALIZACIÓN DE FIGURAS TRIDIMENSIONALES
## Por: Paul Antony Parizaca Mozo

## Ejecución

Clonar el repositorio.
```bash
git clone https://github.com/PaulParizacaMozo/Octree
```
Crear el directorio build e ingresamos
```bash
mkdir build
cd build
```
Movemos los datasets *points1.csv* y *points2.csv* al directorio build
```bash
mv ../points1.csv ../points2.csv .
```
Ahora construimos el proyecto y ejecutable
```bash
cmake ..
make
./main
```

## Ejemplo de Ejecución

Primero cargara el menu inicial

![Ejemplo de imagen local](Imagenes/ejec1.png)

En la primera y segunda opcion nos cargara en segundo menu

![Ejemplo al](Imagenes/ejec2.png)

Y depende a cada opcion podemos visualizar las figuras

Con la Opcion 1 del menu de visualizacion

![Ejemplo al](Imagenes/resultado_dragon_cuboHoja.png)

Con la Opcion 2 del menu de visualizacion

![Ejemplo al](Imagenes/resultado_dragon_medio.png)

Con la Opcion 3 del menu de visualizacion

![Ejemplo al](Imagenes/resultado_dragon_p.png)

Con la tercera opcion nos cargara un menu de Octree con funciones como insertar,
buscar y mostrar nodos hojas junto a su nivel en el arbol

![Ejemplo deen local](Imagenes/ejec3.png)

Insertamos un punto con la primera opcion

![Ejemplo de imgen local](Imagenes/ejec4-insert.png)

y podemos ver el nodo hoja con la tercera opcion

![Ejemplo de imgen local](Imagenes/ejec4-res.png)

y asi podemos seguir insertando puntos(ej. en un nodo distinto de los hijos del
nodo root).
Es por ello que el arbol solo crece en 1 nivel

![Ejemplo de iagen local](Imagenes/ejec6.png)

Pero si seguimos insertando, depende en como les asigne su posicion la funcion
de inserccion tendremos un arbol con distintos niveles.

![Ejemplo d  local](Imagenes/ejec7.png)

La opcion de buscar nos pide las coordenadas de un punto y nos indica si 
se encuentra en el arbol.

![Ejemplo d  local](Imagenes/ejec7.png)
