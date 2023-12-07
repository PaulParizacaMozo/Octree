cmake_minimum_required(VERSION 3.10)

project(main)

# Encuentra el paquete de VTK
find_package(VTK REQUIRED)

# Incluye los directorios de encabezado de VTK
include(${VTK_USE_FILE})

# Incluye el directorio de encabezados de tus clases
include_directories(clases)

# Agrega tu ejecutable
add_executable(main main.cpp)

# Enlaza tu ejecutable con las bibliotecas de VTK
target_link_libraries(main ${VTK_LIBRARIES})

