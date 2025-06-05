#include <iostream> // Librería para entrada y salida estándar (cin, cout)
#include <fstream>  // Librería para manejo de archivos (ifstream, ofstream)
using namespace std;

// ===================== GESTOR DE PROCESOS (LISTA ENLAZADA) =====================

// Estructura para representar un proceso en la lista enlazada
struct Proceso
{
    int id;             // Identificador único del proceso
    char nombre[30];    // Nombre del proceso (arreglo de caracteres)
    int prioridad;      // Prioridad del proceso
    Proceso *siguiente; // Puntero al siguiente proceso en la lista
};

// -----------------------------------------------------------------------------
// Función para comparar dos cadenas de caracteres (sin usar librerías extra)
// Retorna true si ambas cadenas son iguales, false si son diferentes
bool compararCadenas(const char a[], const char b[])
{
    int i = 0; // Índice para recorrer las cadenas
    // Recorre ambas cadenas hasta encontrar el final de alguna
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i]) // Si algún carácter es diferente, retorna false
            return false;
        i++;
    }
    // Si ambas cadenas terminaron al mismo tiempo, son iguales
    return a[i] == b[i];
}

// -----------------------------------------------------------------------------
// Función para guardar todos los procesos de la lista enlazada en un archivo
// Cada línea del archivo tendrá: id nombre prioridad
void guardarProcesosEnArchivo(Proceso *cabeza)
{
    ofstream archivo("procesos.txt"); // Abre el archivo para escritura (sobrescribe)
    Proceso *aux = cabeza;            // Puntero auxiliar para recorrer la lista
    while (aux != NULL)
    {
        // Escribe los datos del proceso en una línea
        archivo << aux->id << " " << aux->nombre << " " << aux->prioridad << "\n";
        aux = aux->siguiente; // Avanza al siguiente proceso
    }
    archivo.close(); // Cierra el archivo
}

// -----------------------------------------------------------------------------
// Función para cargar los procesos desde el archivo al iniciar el programa
// Inserta cada proceso leído al inicio de la lista enlazada
void cargarProcesosDesdeArchivo(Proceso *&cabeza)
{
    ifstream archivo("procesos.txt"); // Abre el archivo para lectura
    if (!archivo.is_open())
        return; // Si no existe el archivo, no hace nada

    int id, prioridad;
    char nombre[30];
    // Lee cada línea del archivo y crea un nuevo proceso
    while (archivo >> id >> nombre >> prioridad)
    {
        Proceso *nuevo = new Proceso; // Reserva memoria para el nuevo proceso
        nuevo->id = id;               // Asigna el ID
        int i = 0;
        for (; nombre[i] != '\0'; i++)
            nuevo->nombre[i] = nombre[i]; // Copia el nombre carácter por carácter
        nuevo->nombre[i] = '\0';          // Fin de cadena
        nuevo->prioridad = prioridad;     // Asigna la prioridad
        nuevo->siguiente = cabeza;        // El nuevo proceso apunta al anterior primer elemento
        cabeza = nuevo;                   // El nuevo proceso es ahora la cabeza de la lista
    }
    archivo.close(); // Cierra el archivo
}

// -----------------------------------------------------------------------------
// Inserta un nuevo proceso al inicio de la lista enlazada y guarda en archivo
void insertarProceso(Proceso *&cabeza, int id, const char nombre[], int prioridad)
{
    Proceso *nuevo = new Proceso; // Reserva memoria para el nuevo proceso
    nuevo->id = id;               // Asigna el ID
    int i = 0;
    for (; nombre[i] != '\0'; i++)
        nuevo->nombre[i] = nombre[i]; // Copia el nombre carácter por carácter
    nuevo->nombre[i] = '\0';          // Fin de cadena
    nuevo->prioridad = prioridad;     // Asigna la prioridad
    nuevo->siguiente = cabeza;        // El nuevo proceso apunta al anterior primer elemento
    cabeza = nuevo;                   // El nuevo proceso es ahora la cabeza de la lista
    cout << "Proceso insertado correctamente.\n";
    guardarProcesosEnArchivo(cabeza); // Guarda la lista actualizada en el archivo
}

// -----------------------------------------------------------------------------
// Busca un proceso por ID en la lista enlazada y muestra su información
void buscarProceso(Proceso *cabeza, int idBuscar)
{
    Proceso *aux = cabeza; // Puntero auxiliar para recorrer la lista
    // Recorre la lista hasta encontrar el proceso o llegar al final
    while (aux != NULL)
    {
        if (aux->id == idBuscar) // Si encuentra el proceso con el ID buscado
        {
            cout << "Proceso encontrado:\n";
            cout << "ID: " << aux->id << "\n";
            cout << "Nombre: " << aux->nombre << "\n";
            cout << "Prioridad: " << aux->prioridad << "\n";
            return; // Termina la función si lo encuentra
        }
        aux = aux->siguiente; // Avanza al siguiente proceso
    }
    cout << "Proceso no encontrado.\n";
}

// -----------------------------------------------------------------------------
// Elimina un proceso de la lista enlazada por ID y guarda en archivo
void eliminarProceso(Proceso *&cabeza, int idEliminar)
{
    Proceso *actual = cabeza; // Puntero al proceso actual
    Proceso *anterior = NULL; // Puntero al proceso anterior
    // Recorre la lista buscando el proceso a eliminar
    while (actual != NULL)
    {
        if (actual->id == idEliminar) // Si encuentra el proceso a eliminar
        {
            if (anterior == NULL)           // Si es el primero de la lista
                cabeza = actual->siguiente; // La cabeza apunta al siguiente
            else
                anterior->siguiente = actual->siguiente; // El anterior salta al siguiente

            delete actual; // Libera la memoria del proceso eliminado
            cout << "Proceso eliminado correctamente.\n";
            guardarProcesosEnArchivo(cabeza); // Guarda la lista actualizada en el archivo
            return;                           // Termina la función
        }
        anterior = actual;          // Avanza el puntero anterior
        actual = actual->siguiente; // Avanza el puntero actual
    }
    cout << "Proceso no encontrado para eliminar.\n";
}

// -----------------------------------------------------------------------------
// Modifica la prioridad de un proceso dado su ID y guarda en archivo
void modificarPrioridad(Proceso *cabeza, int idBuscar, int nuevaPrioridad)
{
    Proceso *aux = cabeza; // Puntero auxiliar para recorrer la lista
    // Recorre la lista buscando el proceso
    while (aux != NULL)
    {
        if (aux->id == idBuscar) // Si encuentra el proceso
        {
            aux->prioridad = nuevaPrioridad; // Cambia la prioridad
            cout << "Prioridad modificada correctamente.\n";
            guardarProcesosEnArchivo(cabeza); // Guarda la lista actualizada en el archivo
            return;                           // Termina la función
        }
        aux = aux->siguiente; // Avanza al siguiente proceso
    }
    cout << "Proceso no encontrado.\n";
}

// -----------------------------------------------------------------------------
// Muestra todos los procesos en la lista enlazada
void mostrarProcesos(Proceso *cabeza)
{
    if (!cabeza)
    {
        cout << "No hay procesos registrados.\n";
        return;
    }
    cout << "\n--- Lista de procesos ---\n";
    Proceso *aux = cabeza;
    while (aux)
    {
        cout << "ID: " << aux->id << " | Nombre: " << aux->nombre << " | Prioridad: " << aux->prioridad << "\n";
        aux = aux->siguiente;
    }
}

// -----------------------------------------------------------------------------
// Menú para gestionar procesos (lista enlazada)
void menuListaEnlazada()
{
    Proceso *listaProcesos = NULL;             // Lista enlazada de procesos (vacía al inicio)
    cargarProcesosDesdeArchivo(listaProcesos); // Carga los procesos guardados en el archivo
    int opcion;                                // Variable para almacenar la opción del usuario
    do
    {
        // Muestra el submenú de procesos
        cout << "\n--- GESTOR DE PROCESOS (LISTA ENLAZADA) ---\n";
        cout << "1. Insertar proceso\n";
        cout << "2. Buscar proceso\n";
        cout << "3. Eliminar proceso\n";
        cout << "4. Modificar prioridad\n";
        cout << "5. Mostrar todos los procesos\n";
        cout << "6. Volver al menú principal\n";
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
            mostrarProcesos(listaProcesos);
            break;
        case 6:
            cout << "Volviendo al menú principal...\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 6);
}

// ===================== GESTOR DE MEMORIA (PILA) =====================

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

int menuPilaMemoria()
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
                cout << "Volviendo al Menu Principal...\n"; // Mensaje de salida
                break;
            default:
                cout << "Opcion incorrecta\n"; // Mensaje si se ingresa una opción inválida
        }

    } while (op != 5); // Se repite el menú hasta que se seleccione salir

    return 0; // Fin del programa
}

// ===================== PLANIFICADOR DE CPU (COLA DE PRIORIDAD) =====================

// Estructura para representar un proceso en la cola de prioridad de CPU
struct NodoCPU
{
    int id;             // Identificador del proceso
    char nombre[30];    // Nombre del proceso
    int prioridad;      // Prioridad del proceso (mayor número = mayor prioridad)
    NodoCPU *siguiente; // Puntero al siguiente proceso en la cola
};

// -----------------------------------------------------------------------------
// Crea y retorna un nuevo nodo (proceso) con los datos dados
NodoCPU *crearNodoCPU(int id, const char nombre[], int prioridad)
{
    NodoCPU *nuevo = new NodoCPU; // Reserva memoria para el nuevo nodo
    nuevo->id = id;               // Asigna el ID
    int i = 0;
    for (; nombre[i] != '\0'; i++)
        nuevo->nombre[i] = nombre[i]; // Copia el nombre carácter por carácter
    nuevo->nombre[i] = '\0';          // Fin de cadena
    nuevo->prioridad = prioridad;     // Asigna la prioridad
    nuevo->siguiente = NULL;          // El siguiente es NULL
    return nuevo;
}

// -----------------------------------------------------------------------------
// Inserta un proceso en la cola, manteniendo el orden por prioridad (mayor primero)
void encolarCPU(NodoCPU *&frente, int id, const char nombre[], int prioridad)
{
    NodoCPU *nuevo = crearNodoCPU(id, nombre, prioridad); // Crea el nuevo nodo
    // Si la cola está vacía o el nuevo tiene mayor prioridad, va al frente
    if (frente == NULL || prioridad > frente->prioridad)
    {
        nuevo->siguiente = frente;
        frente = nuevo;
    }
    else
    {
        NodoCPU *actual = frente;
        NodoCPU *anterior = NULL;
        // Busca la posición correcta según la prioridad
        while (actual != NULL && actual->prioridad >= prioridad)
        {
            anterior = actual;
            actual = actual->siguiente;
        }
        anterior->siguiente = nuevo;
        nuevo->siguiente = actual;
    }
    cout << "Proceso encolado en la CPU con prioridad " << prioridad << ".\n";
}

// -----------------------------------------------------------------------------
// Elimina (ejecuta) el primer proceso de la cola (mayor prioridad)
void ejecutarCPU(NodoCPU *&frente)
{
    if (frente == NULL) // Si la cola está vacía
    {
        cout << "No hay procesos en la cola de CPU para ejecutar.\n";
        return;
    }
    // Muestra el proceso que se va a ejecutar
    cout << "Ejecutando proceso: ID = " << frente->id
         << ", Nombre = " << frente->nombre
         << ", Prioridad = " << frente->prioridad << "\n";
    NodoCPU *temp = frente;     // Guarda el nodo a eliminar
    frente = frente->siguiente; // Avanza el frente de la cola
    delete temp;                // Libera la memoria del nodo ejecutado
}

// -----------------------------------------------------------------------------
// Muestra todos los procesos actualmente en la cola de la CPU
void mostrarColaCPU(NodoCPU *frente)
{
    if (frente == NULL)
    {
        cout << "Cola de CPU vacía.\n";
        return;
    }
    cout << "\n--- Cola de procesos en CPU (ordenados por prioridad) ---\n";
    NodoCPU *actual = frente;
    while (actual != NULL)
    {
        cout << "ID: " << actual->id
             << " | Nombre: " << actual->nombre
             << " | Prioridad: " << actual->prioridad << "\n";
        actual = actual->siguiente;
    }
}

// -----------------------------------------------------------------------------
// Menú para el planificador de CPU (cola de prioridad)
void menuColaCPU()
{
    NodoCPU *colaCPU = NULL; // Cola de procesos de la CPU (vacía al inicio)
    int opcion;              // Variable para almacenar la opción del usuario
    do
    {
        // Muestra el submenú de la CPU
        cout << "\n--- PLANIFICADOR DE CPU (COLA DE PRIORIDAD) ---\n";
        cout << "1. Encolar nuevo proceso\n";
        cout << "2. Mostrar cola de CPU\n";
        cout << "3. Ejecutar proceso\n";
        cout << "4. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
        {
            int id, prioridad;
            char nombre[30];
            cout << "Ingrese ID del proceso: ";
            cin >> id;
            cout << "Ingrese nombre del proceso: ";
            cin >> nombre;
            cout << "Ingrese prioridad del proceso: ";
            cin >> prioridad;
            encolarCPU(colaCPU, id, nombre, prioridad);
            break;
        }
        case 2:
            mostrarColaCPU(colaCPU);
            break;
        case 3:
            ejecutarCPU(colaCPU);
            break;
        case 4:
            cout << "Volviendo al menú principal...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 4);
}

// ===================== MENÚ PRINCIPAL =====================

int main()
{
    int opcion; // Variable para almacenar la opción del usuario
    do
    {
        // Muestra el menú principal del sistema
        cout << "\n======= MENÚ PRINCIPAL DEL SISTEMA =======\n";
        cout << "1. Gestor de procesos (Lista enlazada)\n";
        cout << "2. Gestión de memoria (Pila)\n";
        cout << "3. Planificador de CPU (Cola de prioridad)\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            menuListaEnlazada(); // Llama al menú de procesos
            break;
        case 2:
            menuPilaMemoria(); // Llama al menú de memoria
            break;
        case 3:
            menuColaCPU(); // Llama al menú de CPU
            break;
        case 4:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 4); // Repite hasta que el usuario elija salir
    return 0; // Fin del programa
}