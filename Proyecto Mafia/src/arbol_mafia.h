#ifndef ARBOL_MAFIA_H
#define ARBOL_MAFIA_H
#include "miembro.h"

struct ArbolMafia {
    Miembro* raiz;

    ArbolMafia() : raiz(nullptr) {}
    ~ArbolMafia();

    void insertar(Miembro* nuevo);
    Miembro* buscar(Miembro* aux, int id_buscado);
    Miembro* buscar_por_id(int id);
    void liberar_memoria(Miembro* aux);
    

    void editar_miembro(int id, std::string n, std::string ln, int a, char g);
};

#endif