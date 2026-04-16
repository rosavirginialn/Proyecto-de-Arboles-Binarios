#include "logica_sucesion.h"
#include <iostream>
using namespace std;

// Un jefe debe estar vivo y tener menos de 70 años. 
// La restriccion de prisión es opcional para la segunda fase de busqueda.
bool es_apto_para_jefe(Miembro* m, bool incluir_carcel) {
    if (!m || !m->esta_vivo() || m->age >= 70) return false;
    if (!incluir_carcel && m->in_jail) return false;
    return true;
}

Miembro* encontrar_actual_jefe(Miembro* aux) {
    if (!aux) return nullptr;
    if (aux->is_boss) return aux;
    Miembro* res = encontrar_actual_jefe(aux->izq);
    if (res) return res;
    else return encontrar_actual_jefe(aux->der);
}

// Busca al primer apto en un subarbol (Los hijos y descendencia tiene la prioridad)
Miembro* buscar_primer_apto(Miembro* nodo, bool incluir_carcel) {
    if (!nodo) return nullptr;
    if (es_apto_para_jefe(nodo, incluir_carcel)) return nodo;

    Miembro* candidato = buscar_primer_apto(nodo->izq, incluir_carcel);
    if (candidato) return candidato;
    
    return buscar_primer_apto(nodo->der, incluir_carcel);
}
