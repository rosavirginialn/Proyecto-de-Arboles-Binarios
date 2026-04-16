#include <iostream>
#include <string>
#include <limits>
#include "arbol_mafia.h"
#include "gestor_csv.h"
#include "logica_sucesion.h"
#include "visualizador.h"

using namespace std;

/**
 * @brief Interfaz visual del menú principal.
 */
void mostrarMenu() {
    cout << "\n==============================================" << endl;
    cout << "       SISTEMA DE GESTION DE LA FAMILIA       " << endl;
    cout << "==============================================" << endl;
    cout << "  1. Cargar datos" << endl;
    cout << "  2. Ver Organigrama Familiar" << endl;
    cout << "  3. Consultar Linea de Sucesion (Vivos)" << endl;
    cout << "  4. Editar Perfil de Miembro" << endl;
    cout << "  5. Notificar Baja (Muerte / Arresto)" << endl;
    cout << "  6. Guardar Cambios y Salir" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Seleccione una accion: ";
}

/**
 * @brief Limpia el buffer de entrada para evitar bucles infinitos.
 */
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    ArbolMafia familia;
    string ruta = "../bin/datos.csv"; 
    int opcion = 0;

    // Mensaje de inicio
    cout << "Iniciando terminal de control..." << endl;

    while (opcion != 6) {
        mostrarMenu();
        
        if (!(cin >> opcion)) {
            cout << "\n>>> [ERROR]: Entrada no valida. Por favor, use numeros." << endl;
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1: // CARGAR DATOS
                if (cargarDesdeCSV(ruta, familia)) {
                    cout << "\n>>> EXITO: Base de datos sincronizada desde " << ruta << endl;
                    // Al cargar, verificamos si el jefe actual sigue siendo apto
                    reasignar_jefe(familia);
                } else {
                    cout << "\n>>> [ERROR]: Archivo no encontrado en " << ruta << endl;
                }
                break;

            case 2: // MOSTRAR ESTRUCTURA
                cout << "\n--- ESTRUCTURA JERARQUICA ACTUAL ---" << endl;
                if (familia.raiz) {
                    imprimir_arbol(familia.raiz);
                } else {
                    cout << "[Aviso]: No hay registros cargados en el sistema." << endl;
                }
                break;

            case 3: // LINEA DE SUCESION
                cout << "\n--- PROTOCOLO DE SUCESION (MIEMBROS ACTIVOS) ---" << endl;
                if (familia.raiz) {
                    mostrar_sucesion_viva(familia.raiz);
                } else {
                    cout << "[Aviso]: La jerarquia esta vacia." << endl;
                }
                break;

            case 4: { // EDITAR MIEMBRO
                int id;
                cout << "\nIngrese ID del miembro a modificar: "; cin >> id;
                
                Miembro* m = familia.buscar_por_id(id);
                if (m) {
                    string n, ln;
                    int edad;
                    char gen;
                    
                    cout << "Editando a: " << m->name << " " << m->last_name << endl;
                    cout << "Nuevo Nombre: "; cin >> n;
                    cout << "Nuevo Apellido: "; cin >> ln;
                    cout << "Nueva Edad: "; cin >> edad;
                    cout << "Genero (H/M): "; cin >> gen;

                    familia.editar_miembro(id, n, ln, edad, gen);
                    
                    // Verificamos si los cambios (especialmente la edad) alteran la jefatura
                    reasignar_jefe(familia);
                    cout << ">>> Perfil actualizado correctamente." << endl;
                } else {
                    cout << ">>> [ERROR]: No se encontro ningun miembro con ID " << id << endl;
                }
                break;
            }

            case 5: { // REPORTE DE BAJA
                int id, estado;
                cout << "\nReportar incidencia para ID: "; cin >> id;
                
                Miembro* m = familia.buscar_por_id(id);
                if (m) {
                    cout << "Seleccione el estado: (1) Fallecido | (2) Arrestado: ";
                    cin >> estado;

                    if (estado == 1) {
                        m->is_dead = true;
                        cout << ">>> Registrado: Fallecimiento confirmado." << endl;
                    } else if (estado == 2) {
                        m->in_jail = true;
                        cout << ">>> Registrado: Miembro bajo custodia policial." << endl;
                    } else {
                        cout << ">>> Operacion cancelada: Opcion invalida." << endl;
                        break;
                    }

                    // Disparar lógica de sucesión si el afectado era el jefe o el siguiente en línea
                    reasignar_jefe(familia);
                } else {
                    cout << ">>> [ERROR]: El ID especificado no existe." << endl;
                }
                break;
            }

            case 6: // GUARDAR Y SALIR
                if (guardarEnCSV(ruta, familia)) {
                    cout << "\n>>> Base de datos actualizada satisfactoriamente. Cerrando sistema..." << endl;
                } else {
                    cout << "\n>>> [ADVERTENCIA]: No se pudieron salvar los datos. Verifique permisos." << endl;
                }
                break;

            default:
                cout << "\n>>> Opcion no reconocida. Reintente." << endl;
                break;
        }
    }

    return 0;
}