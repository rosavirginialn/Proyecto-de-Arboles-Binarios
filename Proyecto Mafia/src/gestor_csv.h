#ifndef GESTOR_CSV_H
#define GESTOR_CSV_H
#include <string>
#include "arbol_mafia.h"

/**
 * Carga la estructura familiar desde un archivo CSV.
 * @param ruta Ubicación del archivo.
 * @param arbol Referencia al árbol donde se insertarán los miembros.
 * @return true si la carga fue exitosa, false si el archivo no existe.
 */
bool cargarDesdeCSV(std::string ruta, ArbolMafia& arbol);

/**
 * Guarda el estado actual del árbol en un archivo CSV.
 * @param ruta Ubicación del archivo de destino.
 * @param arbol Referencia al árbol de donde se extraerán los datos.
 * @return true si se guardó correctamente.
 */
bool guardarEnCSV(std::string ruta, ArbolMafia& arbol);

#endif
