@echo off

cd /d "%~dp0"
title Compilador Mafioso - Estructura Profesional


set EJECUTABLE=GestionMafia.exe
set RUTA_BIN=..\bin
set ARCHIVOS=main.cpp arbol_mafia.cpp gestor_csv.cpp logica_sucesion.cpp visualizador.cpp

echo ==================================================
echo        SISTEMA DE GESTION MAFIOSA v1.0
echo ==================================================
echo [+] Carpeta actual (Fuente): %CD%
echo [+] Destino del ejecutable: %RUTA_BIN%


if not exist "%RUTA_BIN%" (
    echo [!] La carpeta 'bin' no existia. Creandola en %RUTA_BIN%...
    mkdir "%RUTA_BIN%"
)

echo [+] Compilando archivos...

g++ -O2 -Wall %ARCHIVOS% -o "%RUTA_BIN%/%EJECUTABLE%"

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa errores de sintaxis arriba.
    pause
    exit /b %errorlevel%
)

echo [+] Compilacion exitosa.
echo.
set /p opt=^> Desea iniciar el sistema ahora? (S/N): 

if /i "%opt%"=="S" (
    cls
    
    cd /d "%RUTA_BIN%"
    

    if not exist "datos.csv" (
        echo [ADVERTENCIA] No se encontro 'datos.csv' en la carpeta bin.
        echo Es posible que el programa de errores al cargar.
    )

    "%EJECUTABLE%"
    
  
    cd /d "%~dp0"
)

echo.
echo [+] Proceso terminado.
pause