#ifndef LOGICA_SUCESION_H
#define LOGICA_SUCESION_H
#include "arbol_mafia.h"

bool es_apto_para_jefe(Miembro* m, bool incluir_carcel);

Miembro* encontrar_actual_jefe(Miembro* aux);
Miembro* buscar_primer_apto(Miembro* nodo, bool incluir_carcel);
Miembro* buscar_sucesor_protocolo(Miembro* jefe, bool incluir_carcel);
void reasignar_jefe(ArbolMafia& arbol);

#endif
