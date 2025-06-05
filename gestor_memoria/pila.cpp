#include <iostream>
using namespace std;

struct BloqueMemoria // Estructura para representar un bloque de memoria
{
    int ID_Proceso; // Identificador único del proceso
    int tamanio; // Tamaño del proceso en MB
    BloqueMemoria *siguiente; // Puntero al siguiente bloque en la lista
};

void AsignarMemoria(BloqueMemoria *&cima, int ID_Proceso, int tamanio) // Función para asignar memoria a un proceso
{
    BloqueMemoria *nuevo = new BloqueMemoria; // Se crea un nuevo bloque de memoria
    nuevo->ID_Proceso = ID_Proceso; // Se asigna el ID del proceso
    nuevo->tamanio = tamanio; // Se asigna el tamaño del proceso
    nuevo->siguiente = cima; // El nuevo bloque apunta al anterior que era la cima
    cima = nuevo; // El nuevo bloque pasa a ser la cima de la pila
    cout << "Memoria asignada correctamente\n"; // Mensaje de confirmación
}

void LiberarMemoriaPorID(BloqueMemoria *&cima, int id) // Función para liberar memoria de un proceso por su ID
{
    if (cima == NULL) // Si no hay bloques asignados
    {
        cout << "No hay bloques de memoria asignados\n"; // Mensaje informando que la lista está vacía
        return;
    }

    BloqueMemoria *actual = cima; // Puntero temporal para recorrer la lista
    BloqueMemoria *anterior = NULL; // Puntero para rastrear el nodo anterior

    while (actual != NULL && actual->ID_Proceso != id) // Recorre la lista buscando el ID
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) // Si no se encontró el ID
    {
        cout << "No se encontró un bloque con ID " << id << "\n"; // Mensaje indicando que no se halló el proceso
        return;
    }

    if (anterior == NULL) // Si el nodo a eliminar es el primero
    {
        cima = actual->siguiente; // Se mueve la cima al siguiente nodo
    }
    else // Si el nodo a eliminar está en medio o al final
    {
        anterior->siguiente = actual->siguiente; // Se salta el nodo actual
    }

    cout << "Liberando memoria del proceso ID=" << actual->ID_Proceso << "\n"; // Mensaje de liberación
    delete actual; // Se elimina el nodo
}

void BuscarPorID(BloqueMemoria *cima, int id) // Función para buscar un proceso por su ID
{
    while (cima != NULL) // Recorre toda la lista
    {
        if (cima->ID_Proceso == id) // Si encuentra el ID solicitado
        {
            cout << "Proceso encontrado: ID=" << cima->ID_Proceso << ", Tamanio=" << cima->tamanio << "MB\n"; // Muestra datos
            return;
        }
        cima = cima->siguiente; // Avanza al siguiente nodo
    }
    cout << "Proceso con ID=" << id << " no encontrado\n"; // Mensaje si no se encuentra el proceso
}

void MostrarMemoria(BloqueMemoria *cima) // Función para mostrar todos los bloques de memoria asignados
{
    if (cima == NULL) // Si la lista está vacía
    {
        cout << "No hay bloques de memoria asignados\n"; // Mensaje indicando vacío
        return;
    }
    cout << "Bloques de memoria asignados:\n"; // Encabezado de la lista

    while (cima != NULL) // Recorre toda la lista
    {
        cout << "Proceso ID: " << cima->ID_Proceso << ", Tamanio: " << cima->tamanio << "MB\n"; // Muestra cada nodo
        cima = cima->siguiente; // Avanza al siguiente nodo
    }
}

int main()
{
    BloqueMemoria *pilaMemoria = NULL; // Puntero inicial a la lista de bloques de memoria
    int op; // Variable para guardar la opción del menú

    do
    {
        // Menú de opciones
        cout << "\n ---- Gestion de Memoria ---- \n";
        cout << "1. Asignar Memoria \n";
        cout << "2. Liberar Memoria por ID \n";
        cout << "3. Ver estado de la Memoria \n";
        cout << "4. Buscar Proceso por ID \n";
        cout << "5. Salir \n";
        cout << "Seleccione una opcion: ";
        cin >> op; // Entrada de la opción

        switch (op) // Evaluación de la opción
        {
            case 1: {
                int id, tam;
                cout << "ID del proceso: ";
                cin >> id;
                cout << "Tamanio en MB: ";
                cin >> tam;
                AsignarMemoria(pilaMemoria, id, tam); // Llama a la función para asignar memoria
                break;
            }
            case 2: {
                int id;
                cout << "Ingrese el ID del proceso a liberar: ";
                cin >> id;
                LiberarMemoriaPorID(pilaMemoria, id); // Llama a la función para liberar por ID
                break;
            }
            case 3:
                MostrarMemoria(pilaMemoria); // Llama a la función para mostrar la memoria
                break;
            case 4: {
                int id;
                cout << "Ingrese el ID del proceso a buscar: ";
                cin >> id;
                BuscarPorID(pilaMemoria, id); // Llama a la función para buscar un ID
                break;
            }
            case 5:
                cout << "Saliendo del programa...\n"; // Mensaje de salida
                break;
            default:
                cout << "Opcion incorrecta\n"; // Mensaje si se ingresa una opción inválida
        }

    } while (op != 5); // Se repite el menú hasta que se seleccione salir

    return 0; // Fin del programa
}
