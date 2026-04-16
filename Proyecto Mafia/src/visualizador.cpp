#include "visualizador.h"
using namespace std;

void imprimir_arbol(Miembro* nodo, int nivel) {
    if (!nodo) return;
    for (int i = 0; i < nivel; i++) {
        cout << "    ";
    }
    cout << "|-- " << nodo->name << " " << nodo->last_name;
    if (nodo->is_boss) cout << " (JEFE)";
    if (nodo->is_dead) cout << " (D.E.P.)";
    else if (nodo->in_jail) cout << " (PRESO)";
    cout << " [ID: " << nodo->id << "]" << endl;

    // Recursividad
    // 1. Bajamos a los hijos (izq) con mas espacio
    imprimir_arbol(nodo->izq, nivel + 1);
    // 2. Seguimos con los hermanos (der) al mismo nivel
    imprimir_arbol(nodo->der, nivel);
}

void mostrar_sucesion_viva(Miembro* nodo) {
    if (!nodo) return;
    // Solo mostramos si esta vivo
    if (nodo->esta_vivo()) {
        cout << "ID: " << nodo->id << " | " << nodo->name << " " << nodo->last_name;
        if (nodo->in_jail) cout << " (En Prision - No apto para mando actual)";
        if (nodo->age >= 70) cout << " (Retirado por edad)";
        cout << endl;
    }
    mostrar_sucesion_viva(nodo->izq);
    mostrar_sucesion_viva(nodo->der);
}
