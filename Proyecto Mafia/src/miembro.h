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
};
#endif
