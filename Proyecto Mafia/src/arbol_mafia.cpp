#include "arbol_mafia.h"

void ArbolMafia::insertar(Miembro* nuevo) {
    if (!nuevo) return;
    if (!raiz) { raiz = nuevo; return; }
    
    Miembro* jefe = buscar(raiz, nuevo->id_boss);
    if (jefe) {
        nuevo->padre = jefe;
        if (!jefe->izq) {
            jefe->izq = nuevo;
        } else {
            Miembro* temp = jefe->izq;
            while (temp->der) temp = temp->der;
            temp->der = nuevo;
        }
    }
}

Miembro* ArbolMafia::buscar(Miembro* aux, int id_buscado) {
    if (!aux || aux->id == id_buscado) return aux;
    Miembro* enc = buscar(aux->izq, id_buscado);
    return (enc) ? enc : buscar(aux->der, id_buscado);
}

Miembro* ArbolMafia::buscar_por_id(int id) { 
    return buscar(raiz, id); 
}

void ArbolMafia::editar_miembro(int id, std::string n, std::string ln, int a, char g) {
    Miembro* m = buscar_por_id(id);
    if (m) {
        m->name = n;
        m->last_name = ln;
        m->age = a;
        m->gender = g;
    }
}

ArbolMafia::~ArbolMafia() {
    liberar_memoria(raiz);
}

void ArbolMafia::liberar_memoria(Miembro* aux) {
    if (!aux) return;
    liberar_memoria(aux->izq);
    liberar_memoria(aux->der);
    delete aux;
}
