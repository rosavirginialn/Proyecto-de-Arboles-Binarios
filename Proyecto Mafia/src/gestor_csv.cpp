#include "gestor_csv.h"
#include <fstream>
#include <sstream>

using namespace std;

bool stringToBool(string str) { return str == "1" || str == "true"; }

Miembro* crearMiembroDesdeLinea(string linea) {
    stringstream ss(linea);
    string aux;
    Miembro* m = new Miembro();
    try {
        getline(ss, aux, ','); m->id = stoi(aux);
        getline(ss, m->name, ',');
        getline(ss, m->last_name, ',');
        getline(ss, aux, ','); m->gender = aux[0];
        getline(ss, aux, ','); m->age = stoi(aux);
        getline(ss, aux, ','); m->id_boss = stoi(aux);
        getline(ss, aux, ','); m->is_dead = stringToBool(aux);
        getline(ss, aux, ','); m->in_jail = stringToBool(aux);
        getline(ss, aux, ','); m->was_boss = stringToBool(aux);
        getline(ss, aux, ','); m->is_boss = stringToBool(aux);
    } catch (...) { delete m; return nullptr; }
    return m;
}

void escribirRecursivo(Miembro* actual, ofstream& archivo) {
    if (!actual) return;
    archivo << actual->id << "," << actual->name << "," << actual->last_name << ","
            << actual->gender << "," << actual->age << "," << actual->id_boss << ","
            << actual->is_dead << "," << actual->in_jail << "," 
            << actual->was_boss << "," << actual->is_boss << endl;
    escribirRecursivo(actual->izq, archivo);
    escribirRecursivo(actual->der, archivo);
}

bool cargarDesdeCSV(string ruta, ArbolMafia& arbol) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return false;
    string linea;
    getline(archivo, linea); // Encabezado
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        Miembro* n = crearMiembroDesdeLinea(linea);
        if (n) arbol.insertar(n);
    }
    archivo.close();
    return true;
}

bool guardarEnCSV(string ruta, ArbolMafia& arbol) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return false;
    archivo << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss" << endl;
    escribirRecursivo(arbol.raiz, archivo); // Acceso directo a raiz
    archivo.close();
    return true;
}