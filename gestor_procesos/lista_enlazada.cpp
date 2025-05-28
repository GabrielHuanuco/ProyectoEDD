#include <iostream> // Incluye la librería estándar de entrada/salida
using namespace std;

// -------------------- GESTOR DE PROCESOS (LISTA ENLAZADA) --------------------

// Estructura para representar un proceso en la lista enlazada
struct Proceso
{
    int id;             // Identificador único del proceso
    char nombre[30];    // Nombre del proceso (arreglo de caracteres)
    int prioridad;      // Prioridad del proceso
    Proceso *siguiente; // Puntero al siguiente proceso en la lista
};
