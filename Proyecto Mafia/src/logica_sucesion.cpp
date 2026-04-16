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

// Logica se sucesion segun las reglas
Miembro* buscar_sucesor_protocolo(Miembro* jefe, bool incluir_carcel) {
    if (!jefe) return nullptr;

    //Regla 1: Si tiene sucesores hijos, primer apto en su arbol.
    if (jefe->izq) {
        Miembro* s = buscar_primer_apto(jefe->izq, incluir_carcel);
        if (s) return s;
    }

    Miembro* padre = jefe->padre;
    if (padre) {
        //Regla 2: Buscar en el arbol del otro sucesor de su jefe(hermano).
        Miembro* hermano = padre->izq;
        while (hermano) {
            if (hermano != jefe) {
                Miembro* s = buscar_primer_apto(hermano->izq, incluir_carcel);
                if (s) return s;

                // Regla 3: Si el hermano esta vivo, apto y no tiene hijos, el se vuelve jefe.
                if (es_apto_para_jefe(hermano, incluir_carcel) && !hermano->izq) {
                    return hermano;
                }
            }
            hermano = hermano->der;
        }

        //Regla 4: Buscar en el arbol del compañero sucesor de su anterior jefe(tío).
        Miembro* abuelo = padre->padre;
        if (abuelo) {
            Miembro* tio = abuelo->izq;
            while (tio) {
                if (tio != padre) {
                    Miembro* s = buscar_primer_apto(tio->izq, incluir_carcel);
                    if (s) return s;
                    if (es_apto_para_jefe(tio, incluir_carcel) && !tio->izq) {
                        return tio;
                    }
                }
                tio = tio->der;
            }
        }
    }

    //Regla 5: Buscar el jefe mas cercano con dos sucesores fuera de la carcel.
    Miembro* temp = jefe->padre;
    while (temp) {
        int count = 0;
        Miembro* hijo = temp->izq;
        while (hijo) {
            if (es_apto_para_jefe(hijo, false)) count++;
            hijo = hijo->der;
        }
        
        if (count >= 2) {
            Miembro* s = buscar_primer_apto(temp->izq, incluir_carcel);
            if (s) return s;
        }
        temp = temp->padre;
    }

    return nullptr;
}

void reasignar_jefe(ArbolMafia& arbol) {
    Miembro* actual = encontrar_actual_jefe(arbol.raiz);    
    //Considera si el jefe murio, fue a prisión o supero los 70 años.
    if (actual && (actual->is_dead || actual->in_jail || actual->age >= 70)) {
        
        //1: Intentar encontrar sucesor libre
        Miembro* sucesor = buscar_sucesor_protocolo(actual, false);

        //2: Si no hay nadie libre, sigue las mismas reglas para presos vivos.
        if (!sucesor) {
            sucesor = buscar_sucesor_protocolo(actual, true);
        }

        if (sucesor) {
            actual->is_boss = false;
            sucesor->is_boss = true;
            sucesor->was_boss = true;
            cout << "\nAVISO: " << sucesor->name << " es el nuevo jefe.\n";
        } else {
            cout << "\nAVISO: No se encontro un sucesor apto en toda la jerarquia.\n";
        }
    }
}
