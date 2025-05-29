#include <iostream>
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

// Función para comparar dos cadenas de caracteres (sin usar librerías extra)
bool compararCadenas(const char a[], const char b[])
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
            return false;
        i++;
    }
    return a[i] == b[i];
}

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

// -------------------- MENÚ DE PROCESOS --------------------
void menuProcesos(Proceso *&listaProcesos)
{
    int opcion; // Variable para almacenar la opción del usuario
    do
    {
        // Muestra el submenú de procesos
        cout << "\n--- GESTION DE PROCESOS (LISTA ENLAZADA) ---\n";
        cout << "1. Insertar proceso\n";
        cout << "2. Buscar proceso\n";
        cout << "3. Eliminar proceso\n";
        cout << "4. Modificar prioridad\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
        {
            // Validación para que no se repita ID, nombre o prioridad
            int id, prioridad;
            char nombre[30];
            bool existe;
            do
            {
                existe = false;
                cout << "ID del proceso: ";
                cin >> id;
                cout << "Nombre del proceso: ";
                cin >> nombre;
                cout << "Prioridad del proceso: ";
                cin >> prioridad;

                Proceso *aux = listaProcesos;
                // Recorre la lista para validar duplicados
                while (aux != NULL)
                {
                    if (aux->id == id)
                    {
                        cout << "Ya existe un proceso con ese ID.\n";
                        existe = true;
                    }
                    if (compararCadenas(aux->nombre, nombre))
                    {
                        cout << "Ya existe un proceso con ese nombre.\n";
                        existe = true;
                    }
                    if (aux->prioridad == prioridad)
                    {
                        cout << "Ya existe un proceso con esa prioridad.\n";
                        existe = true;
                    }
                    aux = aux->siguiente;
                }
                if (existe)
                    cout << "Por favor, ingrese los datos nuevamente.\n";
            } while (existe);

            // Inserta el proceso si no hay duplicados
            insertarProceso(listaProcesos, id, nombre, prioridad);
            break;
        }
        case 2:
        {
            int id;
            cout << "ID del proceso a buscar: ";
            cin >> id;
            buscarProceso(listaProcesos, id);
            break;
        }
        case 3:
        {
            int id;
            cout << "ID del proceso a eliminar: ";
            cin >> id;
            eliminarProceso(listaProcesos, id);
            break;
        }
        case 4:
        {
            int id, nueva;
            cout << "ID del proceso: ";
            cin >> id;
            cout << "Nueva prioridad: ";
            cin >> nueva;
            modificarPrioridad(listaProcesos, id, nueva);
            break;
        }
        case 5:
            cout << "Saliendo del gestor de procesos...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 5); // Repite hasta que el usuario elija salir
}

// -------------------- MAIN SOLO PARA LISTA ENLAZADA --------------------
int main()
{
    Proceso *listaProcesos = NULL; // Lista enlazada de procesos

    menuProcesos(listaProcesos); // Llama al menú de procesos

    return 0;
}