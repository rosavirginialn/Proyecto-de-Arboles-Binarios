# Proyecto-De-Arboles-Binarios

## Descripción
Este proyecto implementa un sistema de gestión de árboles binarios para modelar la estructura jerárquica de una familia mafiosa. Utiliza una estructura de tipo Hijo Izquierdo - Hermano Derecho para gestionar de forma eficiente la descendencia y las líneas de mando, automatizando la sucesión según el estado vital, legal y la edad de los miembros.

## Estructura del Proyecto
- `Proyecto Mafia/`: Carpeta principal del proyecto
  - `src/`: Código fuente en C++
    - `arbol_mafia.cpp/h`: Implementación del árbol binario para la familia mafiosa
    - `gestor_csv.cpp/h`: Gestión de archivos CSV para importar/exportar datos
    - `logica_sucesion.cpp/h`: Algoritmos para determinar líneas de sucesión
    - `miembro.h`: Definición de la estructura de datos Miembro
    - `visualizador.cpp/h`: Funcionalidades para mostrar la estructura del árbol
    - `main.cpp`: Programa principal con menú interactivo
  - `bin/`: Archivos de datos y ejecutable
    - `datos.csv`: Archivo CSV con información de los miembros.
    - `GestionMafia.exe`:Ejecutable del programa (generado por el compilador)

## Requisitos del Sistema
- Compilador C++ compatible con C++11 o superior.
- Sistema operativo Windows/Linux/Mac con terminal

## Formato del Archivo CSV
El archivo `bin/datos.csv` debe contener los datos de los miembros en el siguiente formato:
```
id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss
```
Donde:
- `id`: Identificador único
- `name`: Nombre del miembro
- `last_name`: Apellido
- `gender`: Género ('M' o 'F')
- `age`: Edad
- `id_boss`: ID del jefe directo (0 si es el jefe maximo)
- `is_dead`: Estado de vida (0 = vivo, 1 = muerto)
- `in_jail`: Estado de encarcelamiento (0 = libre, 1 = preso)
- `was_boss`: Si fue jefe anteriormente (0 = no, 1 = sí)
- `is_boss`: Si es jefe actualmente (0 = no, 1 = sí)

## Compilación y Automatizacion
- Opcion A: Automatizacion
1. Haz doble clic en src/compilar.bat o ejecútalo desde la terminal dentro de la carpeta src

- Opcion B: Compilacion Manual 
1. Abre una terminal en el directorio `Proyecto Mafia`
2. Ejecuta el comando:
```bash
g++ src/main.cpp src/arbol_mafia.cpp src/gestor_csv.cpp src/logica_sucesion.cpp src/visualizador.cpp -Isrc -o bin/GestionMafia.exe
```

## Ejecución
En caso de utilizar la opcion B, después de compilar, inicia el programa haciendo:
1. Desde la terminal, ingresa a la carpeta donde se encuentra el ejecutable:
```bash
cd bin
```
2. Inicia el programa: 
```bash
./GestionMafia.exe
```
El programa presenta un menú interactivo con diferentes opciones.

## Funcionalidades Principales
- Gestión jerárquica: Representación de la familia como árbol binario
- Lógica de sucesión: Determinación automática de líneas de mando
- Persistencia de datos: Importación y exportación en formato CSV
- Estados dinámicos: Seguimiento de vida, encarcelamiento y roles
- Interfaz de usuario: Menú simple para todas las operaciones

## Notas de Uso
- El ejecutable debe ejecutarse desde el directorio `Proyecto Mafia` para que encuentre correctamente el archivo CSV
- Los cambios se guardan automáticamente al seleccionar "Guardar y salir"
