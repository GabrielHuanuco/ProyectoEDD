#include <iostream> 
using namespace std;

// -------------------- PLANIFICADOR DE CPU (COLA DE PRIORIDAD) --------------------

// Estructura para representar un proceso en la cola de prioridad de CPU
struct NodoCPU
{
    int id;             // Identificador del proceso
    char nombre[30];    // Nombre del proceso
    int prioridad;      // Prioridad del proceso (mayor número = mayor prioridad)
    NodoCPU *siguiente; // Puntero al siguiente proceso en la cola
};

// Función que crea y retorna un nuevo nodo (proceso) con los datos dados
NodoCPU* crearNodoCPU(int id, const char nombre[], int prioridad)
{
    NodoCPU *nuevo = new NodoCPU;  // Reserva memoria para un nuevo nodo

    nuevo->id = id;                // Asigna el ID del proceso

    // Copia el nombre carácter por carácter
    for (int i = 0; nombre[i] != '\0'; i++)
    {
        nuevo->nombre[i] = nombre[i];     // Copia letra por letra
        nuevo->nombre[i + 1] = '\0';      // Asegura el fin de la cadena
    }

    nuevo->prioridad = prioridad; // Asigna la prioridad del proceso
    nuevo->siguiente = NULL;      // El siguiente nodo será NULL al crearlo

    return nuevo;                 // Devuelve el nodo creado
}

// Inserta un proceso en la cola, manteniendo el orden por prioridad (mayor primero)
void encolarCPU(NodoCPU *&frente, int id, const char nombre[], int prioridad)
{
    NodoCPU *nuevo = crearNodoCPU(id, nombre, prioridad);  // Crea un nuevo nodo

    // Si la cola está vacía o el nuevo nodo tiene mayor prioridad que el primero
    if (frente == NULL || prioridad > frente->prioridad)
    {
        nuevo->siguiente = frente;  // El nuevo nodo apunta al frente actual
        frente = nuevo;             // El nuevo nodo se convierte en el nuevo frente
    }
    else
    {
        NodoCPU *actual = frente;    // Apuntador temporal al frente
        NodoCPU *anterior = NULL;    // Apuntador al nodo anterior

        // Recorre la cola hasta encontrar dónde insertar el nuevo nodo
        while (actual != NULL && actual->prioridad >= prioridad)
        {
            anterior = actual;        // Guarda el nodo actual como anterior
            actual = actual->siguiente; // Avanza al siguiente nodo
        }

        // Inserta el nuevo nodo entre anterior y actual
        anterior->siguiente = nuevo;
        nuevo->siguiente = actual;
    }

    // Mensaje de confirmación al usuario
    cout << "Proceso encolado en la CPU con prioridad " << prioridad << ".\n";
}
// Elimina (ejecuta) el primer proceso de la cola (mayor prioridad)
void ejecutarCPU(NodoCPU *&frente)
{
    if (frente == NULL)  // Si no hay procesos en la cola
    {
        cout << "No hay procesos en la cola de CPU para ejecutar.\n";
        return;
    }

    // Muestra información del proceso que se va a ejecutar
    cout << "Ejecutando proceso: ID = " << frente->id
         << ", Nombre = " << frente->nombre
         << ", Prioridad = " << frente->prioridad << "\n";

    NodoCPU *temp = frente;       // Guarda el nodo que será eliminado
    frente = frente->siguiente;   // Avanza el frente al siguiente nodo
    delete temp;                  // Libera la memoria del nodo ejecutado
}

// Muestra todos los procesos actualmente en la cola de la CPU
void mostrarColaCPU(NodoCPU *frente)
{
    if (frente == NULL)  // Si la cola está vacía
    {
        cout << "Cola de CPU vacía.\n";
        return;
    }

    cout << "\n--- Cola de procesos en CPU (ordenados por prioridad) ---\n";

    NodoCPU *actual = frente;  // Puntero temporal para recorrer la cola

    // Recorre y muestra cada nodo
    while (actual != NULL)
    {
        cout << "ID: " << actual->id
             << " | Nombre: " << actual->nombre
             << " | Prioridad: " << actual->prioridad << "\n";

        actual = actual->siguiente;  // Avanza al siguiente proceso
    }
}