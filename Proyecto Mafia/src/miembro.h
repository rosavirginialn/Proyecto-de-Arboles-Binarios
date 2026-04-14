#ifndef MIEMBRO_H
#define MIEMBRO_H
#include <string>

struct Miembro {
    int id;
    std::string name;
    std::string last_name;
    char gender;
    int age;
    int id_boss;
    bool is_dead;
    bool in_jail;
    bool was_boss;
    bool is_boss;

    Miembro* izq;
    Miembro* der;
    Miembro* padre;
    
    // Constructor por defecto 
    Miembro() : id(0), gender(' '), age(0), id_boss(0), is_dead(false), 
                in_jail(false), was_boss(false), is_boss(false), 
                izq(nullptr), der(nullptr), padre(nullptr) {}

    // Constructor completo
    Miembro(int id, const std::string& n, const std::string& ln, char g, int a, 
            int idb, bool dead, bool jail, bool wboss, bool iboss)
        : id(id), name(n), last_name(ln), gender(g), age(a), id_boss(idb),
          is_dead(dead), in_jail(jail), was_boss(wboss), is_boss(iboss),
          izq(nullptr), der(nullptr), padre(nullptr) {}

    bool esta_vivo() const { return !is_dead; }
    bool esta_libre() const { return !is_dead && !in_jail; }
};

#endif
