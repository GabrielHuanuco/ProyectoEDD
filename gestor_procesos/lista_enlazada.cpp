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

// Inserta un nuevo proceso al inicio de la lista enlazada
void insertarProceso(Proceso *&cabeza, int id, const char nombre[], int prioridad)
{
    Proceso *nuevo = new Proceso;           // Reserva memoria para el nuevo proceso
    nuevo->id = id;                         // Asigna el ID al nuevo proceso
    for (int i = 0; nombre[i] != '\0'; i++) // Copia el nombre caracter por caracter
    {
        nuevo->nombre[i] = nombre[i];
        nuevo->nombre[i + 1] = '\0'; // Asegura el fin de cadena
    }
    nuevo->prioridad = prioridad; // Asigna la prioridad
    nuevo->siguiente = cabeza;    // El nuevo proceso apunta al anterior primer elemento
    cabeza = nuevo;               // El nuevo proceso es ahora la cabeza de la lista
    cout << "Proceso insertado correctamente.\n";
}

// Busca un proceso por ID en la lista enlazada
void buscarProceso(Proceso *cabeza, int idBuscar)
{
    Proceso *aux = cabeza; // Puntero auxiliar para recorrer la lista
    while (aux != NULL)
    {
        if (aux->id == idBuscar) // Si encuentra el proceso con el ID buscado
        {
            cout << "Proceso encontrado:\n";
            cout << "ID: " << aux->id << "\n";
            cout << "Nombre: " << aux->nombre << "\n";
            cout << "Prioridad: " << aux->prioridad << "\n";
            return;
        }
        aux = aux->siguiente; // Avanza al siguiente proceso
    }
    cout << "Proceso no encontrado.\n";
}

// Elimina un proceso de la lista enlazada por ID
void eliminarProceso(Proceso *&cabeza, int idEliminar)
{
    Proceso *actual = cabeza; // Puntero al proceso actual
    Proceso *anterior = NULL; // Puntero al proceso anterior

    while (actual != NULL)
    {
        if (actual->id == idEliminar) // Si encuentra el proceso a eliminar
        {
            if (anterior == NULL) // Si es el primero de la lista
                cabeza = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;

            delete actual; // Libera la memoria del proceso eliminado
            cout << "Proceso eliminado correctamente.\n";
            return;
        }
        anterior = actual;          // Avanza el puntero anterior
        actual = actual->siguiente; // Avanza el puntero actual
    }
    cout << "Proceso no encontrado para eliminar.\n";
}

// Modifica la prioridad de un proceso dado su ID
void modificarPrioridad(Proceso *cabeza, int idBuscar, int nuevaPrioridad)
{
    Proceso *aux = cabeza; // Puntero auxiliar para recorrer la lista
    while (aux != NULL)
    {
        if (aux->id == idBuscar) // Si encuentra el proceso
        {
            aux->prioridad = nuevaPrioridad; // Cambia la prioridad
            cout << "Prioridad modificada correctamente.\n";
            return;
        }
        aux = aux->siguiente; // Avanza al siguiente proceso
    }
    cout << "Proceso no encontrado.\n";
}