#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

struct fecha{
  int dia, mes, anio;
};
/**Número de viaje, código de empresa, marca del autobús (1 a 10), cantidad de km del viaje (float),
cantidad de combustible consumido (float), fecha.
**/

struct viaje{
    int numeroViaje, marca;
    char codigoEmpresa[5];
    float cantidadKm, cantidadCombustible;
    fecha fechaViaje;
    bool estado;
};

/**
Código de empresa (char[5]), nombre, dirección, tipo de empresa (1: local.; 2: interurbano; 3: nacional; 4: internacional)
**/
struct empresa{
  char codigoEmpresa[5];
  char nombreEmpresa[30], direccion[40];
  int tipoEmpresa;
  bool estado;
};

struct nuevo{
    char codigoEmpresa[5];
    char nombreEmpresa[30];
    float promedioConsumo;
};

#endif // TIPOS_H_INCLUDED
