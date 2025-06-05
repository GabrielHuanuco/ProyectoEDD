#include <iostream> // Para entrada y salida estándar (cin, cout)
#include <fstream>  // Para manejo de archivos (ifstream, ofstream)
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
// Compara dos cadenas de caracteres (sin usar librerías extra)
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

// -----------------------------------------------------------------------------
// Guarda todos los procesos de la lista enlazada en un archivo
void guardarProcesosEnArchivo(Proceso *cabeza)
{
    ofstream archivo("procesos.txt");
    Proceso *aux = cabeza;
    while (aux != NULL)
    {
        archivo << aux->id << " " << aux->nombre << " " << aux->prioridad << "\n";
        aux = aux->siguiente;
    }
    archivo.close();
}

// -----------------------------------------------------------------------------
// Carga los procesos desde el archivo al iniciar el programa
void cargarProcesosDesdeArchivo(Proceso *&cabeza)
{
    ifstream archivo("procesos.txt");
    if (!archivo.is_open())
        return;
    int id, prioridad;
    char nombre[30];
    while (archivo >> id >> nombre >> prioridad)
    {
        Proceso *nuevo = new Proceso;
        nuevo->id = id;
        int i = 0;
        for (; nombre[i] != '\0'; i++)
            nuevo->nombre[i] = nombre[i];
        nuevo->nombre[i] = '\0';
        nuevo->prioridad = prioridad;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }
    archivo.close();
}

// -----------------------------------------------------------------------------
// Inserta un nuevo proceso al inicio de la lista enlazada y guarda en archivo
void insertarProceso(Proceso *&cabeza, int id, const char nombre[], int prioridad)
{
    Proceso *nuevo = new Proceso;
    nuevo->id = id;
    int i = 0;
    for (; nombre[i] != '\0'; i++)
        nuevo->nombre[i] = nombre[i];
    nuevo->nombre[i] = '\0';
    nuevo->prioridad = prioridad;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    cout << "Proceso insertado correctamente.\n";
    guardarProcesosEnArchivo(cabeza);
}

// -----------------------------------------------------------------------------
// Busca un proceso por ID en la lista enlazada y muestra su información
void buscarProceso(Proceso *cabeza, int idBuscar)
{
    Proceso *aux = cabeza;
    while (aux != NULL)
    {
        if (aux->id == idBuscar)
        {
            cout << "Proceso encontrado:\n";
            cout << "ID: " << aux->id << "\n";
            cout << "Nombre: " << aux->nombre << "\n";
            cout << "Prioridad: " << aux->prioridad << "\n";
            return;
        }
        aux = aux->siguiente;
    }
    cout << "Proceso no encontrado.\n";
}

// -----------------------------------------------------------------------------
// Elimina un proceso de la lista enlazada por ID y guarda en archivo
void eliminarProceso(Proceso *&cabeza, int idEliminar)
{
    Proceso *actual = cabeza;
    Proceso *anterior = NULL;
    while (actual != NULL)
    {
        if (actual->id == idEliminar)
        {
            if (anterior == NULL)
                cabeza = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;
            delete actual;
            cout << "Proceso eliminado correctamente.\n";
            guardarProcesosEnArchivo(cabeza);
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    cout << "Proceso no encontrado para eliminar.\n";
}

// -----------------------------------------------------------------------------
// Modifica la prioridad de un proceso dado su ID y guarda en archivo
void modificarPrioridad(Proceso *cabeza, int idBuscar, int nuevaPrioridad)
{
    Proceso *aux = cabeza;
    while (aux != NULL)
    {
        if (aux->id == idBuscar)
        {
            aux->prioridad = nuevaPrioridad;
            cout << "Prioridad modificada correctamente.\n";
            guardarProcesosEnArchivo(cabeza);
            return;
        }
        aux = aux->siguiente;
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
    Proceso *listaProcesos = NULL;
    cargarProcesosDesdeArchivo(listaProcesos);
    int opcion;
    do
    {
        cout << "\n--- GESTOR DE PROCESOS (LISTA ENLAZADA) ---\n";
        cout << "1. Insertar proceso\n";
        cout << "2. Buscar proceso\n";
        cout << "3. Eliminar proceso\n";
        cout << "4. Modificar prioridad\n";
        cout << "5. Mostrar todos los procesos\n";
        cout << "6. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
        {
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
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 6);
}

// ===================== GESTOR DE MEMORIA (PILA) =====================

// Estructura para representar un bloque de memoria en la pila
struct BloqueMemoria
{
    int ID_Proceso;           // ID del proceso que ocupa el bloque
    int tamanio;              // Tamaño del bloque en MB
    BloqueMemoria *siguiente; // Puntero al siguiente bloque en la pila
};

// -----------------------------------------------------------------------------
// Guarda todos los bloques de memoria en un archivo de texto (memoria.txt)
void guardarMemoriaEnArchivo(BloqueMemoria *cima)
{
    ofstream archivo("memoria.txt");
    BloqueMemoria *aux = cima;
    while (aux != NULL)
    {
        archivo << aux->ID_Proceso << " " << aux->tamanio << "\n";
        aux = aux->siguiente;
    }
    archivo.close();
}

// -----------------------------------------------------------------------------
// Carga los bloques de memoria desde el archivo al iniciar el programa
void cargarMemoriaDesdeArchivo(BloqueMemoria *&cima)
{
    ifstream archivo("memoria.txt");
    if (!archivo.is_open())
        return;
    int id, tamanio;
    while (archivo >> id >> tamanio)
    {
        BloqueMemoria *nuevo = new BloqueMemoria;
        nuevo->ID_Proceso = id;
        nuevo->tamanio = tamanio;
        nuevo->siguiente = cima;
        cima = nuevo;
    }
    archivo.close();
}

// -----------------------------------------------------------------------------
// Asigna un bloque de memoria (push) y guarda en archivo
void AsignarMemoria(BloqueMemoria *&cima, int ID_Proceso, int tamanio)
{
    BloqueMemoria *nuevo = new BloqueMemoria;
    nuevo->ID_Proceso = ID_Proceso;
    nuevo->tamanio = tamanio;
    nuevo->siguiente = cima;
    cima = nuevo;
    cout << "Memoria asignada correctamente\n";
    guardarMemoriaEnArchivo(cima);
}

// -----------------------------------------------------------------------------
// Libera el bloque de memoria por ID y guarda en archivo
void LiberarMemoriaPorID(BloqueMemoria *&cima, int id)
{
    if (cima == NULL)
    {
        cout << "No hay bloques de memoria asignados\n";
        return;
    }
    BloqueMemoria *actual = cima;
    BloqueMemoria *anterior = NULL;
    while (actual != NULL && actual->ID_Proceso != id)
    {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL)
    {
        cout << "No se encontro memoria asignada para ese ID\n";
        return;
    }
    if (anterior == NULL)
        cima = actual->siguiente;
    else
        anterior->siguiente = actual->siguiente;
    cout << "Memoria liberada para el proceso ID=" << id << "\n";
    delete actual;
    guardarMemoriaEnArchivo(cima);
}

// -----------------------------------------------------------------------------
// Muestra todos los bloques de memoria asignados
void MostrarMemoria(BloqueMemoria *cima)
{
    if (cima == NULL)
    {
        cout << "No hay bloques de memoria asignados\n";
        return;
    }
    cout << "Bloques de memoria asignados:\n";
    while (cima != NULL)
    {
        cout << "Proceso ID: " << cima->ID_Proceso << ", Tamanio: " << cima->tamanio << "MB\n";
        cima = cima->siguiente;
    }
}

// -----------------------------------------------------------------------------
// Busca la memoria asignada a un proceso por su ID en la pila de memoria
int buscarMemoriaPorID(BloqueMemoria *cima, int idBuscar)
{
    while (cima != NULL)
    {
        if (cima->ID_Proceso == idBuscar)
            return cima->tamanio;
        cima = cima->siguiente;
    }
    return -1;
}

// -----------------------------------------------------------------------------
// Busca un bloque de memoria por ID de proceso y muestra su información
void BuscarPorID(BloqueMemoria *cima, int id)
{
    while (cima != NULL)
    {
        if (cima->ID_Proceso == id)
        {
            cout << "Proceso encontrado: ID=" << cima->ID_Proceso
                 << ", Tamanio=" << cima->tamanio << "MB\n";
            return;
        }
        cima = cima->siguiente;
    }
    cout << "Proceso con ID=" << id << " no encontrado\n";
}

// -----------------------------------------------------------------------------
// Menú para gestion de memoria (pila) con búsqueda por ID y opción de salir
void menuPilaMemoria()
{
    BloqueMemoria *pilaMemoria = NULL;
    cargarMemoriaDesdeArchivo(pilaMemoria);
    int op;
    do
    {
        // Menú de opciones para la gestión de memoria
        cout << "\n ---- Gestion de Memoria ---- \n";
        cout << "1. Asignar Memoria \n";
        cout << "2. Liberar Memoria por ID\n";
        cout << "3. Ver estado de la Memoria \n";
        cout << "4. Buscar Proceso por ID \n";
        cout << "5. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> op;
        switch (op)
        {
        case 1:
        {
            int id, tam;
            cout << "ID del proceso: ";
            cin >> id;
            cout << "Tamanio en MB: ";
            cin >> tam;
            AsignarMemoria(pilaMemoria, id, tam);
            break;
        }
        case 2:
        {
            int id;
            cout << "Ingrese el ID del proceso a liberar: ";
            cin >> id;
            LiberarMemoriaPorID(pilaMemoria, id);
            break;
        }
        case 3:
            MostrarMemoria(pilaMemoria);
            break;
        case 4:
        {
            int id;
            cout << "Ingrese el ID del proceso a buscar: ";
            cin >> id;
            BuscarPorID(pilaMemoria, id);
            break;
        }
        case 5:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion incorrecta\n";
        }
    } while (op != 5);
}

// ===================== PLANIFICADOR DE CPU (COLA DE PRIORIDAD) =====================

// Estructura para representar un proceso en la cola de CPU
struct NodoCPU
{
    int id;
    char nombre[30];
    int prioridad;
    NodoCPU *siguiente;
};

// -----------------------------------------------------------------------------
// Guarda todos los procesos de la cola de CPU en un archivo de texto (cola_cpu.txt)
void guardarColaCPUEnArchivo(NodoCPU *frente)
{
    ofstream archivo("cola_cpu.txt");
    NodoCPU *aux = frente;
    while (aux != NULL)
    {
        archivo << aux->id << " " << aux->nombre << " " << aux->prioridad << "\n";
        aux = aux->siguiente;
    }
    archivo.close();
}

// -----------------------------------------------------------------------------
// Carga los procesos de la cola de CPU desde el archivo al iniciar el programa
void cargarColaCPUDesdeArchivo(NodoCPU *&frente)
{
    ifstream archivo("cola_cpu.txt");
    if (!archivo.is_open())
        return;
    int id, prioridad;
    char nombre[30];
    while (archivo >> id >> nombre >> prioridad)
    {
        NodoCPU *nuevo = new NodoCPU;
        nuevo->id = id;
        int i = 0;
        for (; nombre[i] != '\0'; i++)
            nuevo->nombre[i] = nombre[i];
        nuevo->nombre[i] = '\0';
        nuevo->prioridad = prioridad;
        nuevo->siguiente = frente;
        frente = nuevo;
    }
    archivo.close();
}

// -----------------------------------------------------------------------------
// Busca un proceso por ID en la lista enlazada de procesos
bool obtenerDatosProcesoPorID(Proceso *cabeza, int idBuscar, char nombre[], int &prioridad)
{
    Proceso *aux = cabeza;
    while (aux != NULL)
    {
        if (aux->id == idBuscar)
        {
            int i = 0;
            for (; aux->nombre[i] != '\0'; i++)
                nombre[i] = aux->nombre[i];
            nombre[i] = '\0';
            prioridad = aux->prioridad;
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

// -----------------------------------------------------------------------------
// Crea y retorna un nuevo nodo (proceso) con los datos dados
NodoCPU *crearNodoCPU(int id, const char nombre[], int prioridad)
{
    NodoCPU *nuevo = new NodoCPU;
    nuevo->id = id;
    int i = 0;
    for (; nombre[i] != '\0'; i++)
        nuevo->nombre[i] = nombre[i];
    nuevo->nombre[i] = '\0';
    nuevo->prioridad = prioridad;
    nuevo->siguiente = NULL;
    return nuevo;
}

// -----------------------------------------------------------------------------
// Inserta un proceso en la cola, manteniendo el orden por prioridad (mayor primero)
void encolarCPU(NodoCPU *&frente, int id, const char nombre[], int prioridad)
{
    NodoCPU *nuevo = crearNodoCPU(id, nombre, prioridad);
    if (frente == NULL || prioridad > frente->prioridad)
    {
        nuevo->siguiente = frente;
        frente = nuevo;
    }
    else
    {
        NodoCPU *actual = frente;
        NodoCPU *anterior = NULL;
        while (actual != NULL && actual->prioridad >= prioridad)
        {
            anterior = actual;
            actual = actual->siguiente;
        }
        anterior->siguiente = nuevo;
        nuevo->siguiente = actual;
    }
    cout << "Proceso encolado en la CPU con prioridad " << prioridad << ".\n";
    guardarColaCPUEnArchivo(frente);
}

// -----------------------------------------------------------------------------
// Elimina (ejecuta) el primer proceso de la cola (mayor prioridad) y guarda en archivo
void ejecutarCPU(NodoCPU *&frente)
{
    if (frente == NULL)
    {
        cout << "No hay procesos en la cola de CPU para ejecutar.\n";
        return;
    }
    cout << "Ejecutando proceso: ID = " << frente->id
         << ", Nombre = " << frente->nombre
         << ", Prioridad = " << frente->prioridad << "\n";
    NodoCPU *temp = frente;
    frente = frente->siguiente;
    delete temp;
    guardarColaCPUEnArchivo(frente);
}

// -----------------------------------------------------------------------------
// Muestra todos los procesos actualmente en la cola de la CPU
// Ahora también muestra la memoria asignada a cada proceso
void mostrarColaCPU(NodoCPU *frente)
{
    if (frente == NULL)
    {
        cout << "Cola de CPU vacia.\n";
        return;
    }
    // Cargar la pila de memoria para consultar la memoria de cada proceso
    BloqueMemoria *pilaMemoria = NULL;
    cargarMemoriaDesdeArchivo(pilaMemoria);

    cout << "\n--- Cola de procesos en CPU (ordenados por prioridad) ---\n";
    NodoCPU *actual = frente;
    while (actual != NULL)
    {
        // Buscar la memoria asignada a este proceso
        int memoria = buscarMemoriaPorID(pilaMemoria, actual->id);
        cout << "ID: " << actual->id
             << " | Nombre: " << actual->nombre
             << " | Prioridad: " << actual->prioridad;
        if (memoria != -1)
            cout << " | Memoria asignada: " << memoria << "MB";
        else
            cout << " | Memoria asignada: Ninguna";
        cout << "\n";
        actual = actual->siguiente;
    }

    // Liberar la pila temporal de memoria usada solo para mostrar
    while (pilaMemoria != NULL)
    {
        BloqueMemoria *temp = pilaMemoria;
        pilaMemoria = pilaMemoria->siguiente;
        delete temp;
    }
}

// -----------------------------------------------------------------------------
// Menú para el planificador de CPU (cola de prioridad)
void menuColaCPU()
{
    NodoCPU *colaCPU = NULL;
    cargarColaCPUDesdeArchivo(colaCPU);

    Proceso *listaProcesos = NULL;
    cargarProcesosDesdeArchivo(listaProcesos);

    int opcion;
    do
    {
        cout << "\n--- PLANIFICADOR DE CPU (COLA DE PRIORIDAD) ---\n";
        cout << "1. Encolar proceso existente\n";
        cout << "2. Mostrar cola de CPU\n";
        cout << "3. Ejecutar proceso\n";
        cout << "4. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
        {
            cout << "\nProcesos disponibles para encolar:\n";
            mostrarProcesos(listaProcesos);

            int id, prioridad;
            char nombre[30];
            cout << "Ingrese el ID del proceso a encolar: ";
            cin >> id;

            if (obtenerDatosProcesoPorID(listaProcesos, id, nombre, prioridad))
            {
                encolarCPU(colaCPU, id, nombre, prioridad);
            }
            else
            {
                cout << "No existe un proceso con ese ID. No se puede encolar.\n";
            }
            break;
        }
        case 2:
            mostrarColaCPU(colaCPU);
            break;
        case 3:
            ejecutarCPU(colaCPU);
            break;
        case 4:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}

// ===================== MENÚ PRINCIPAL =====================

int main()
{
    int opcion;
    do
    {
        cout << "\n======= MENU PRINCIPAL DEL SISTEMA =======\n";
        cout << "1. Gestor de procesos (Lista enlazada)\n";
        cout << "2. Gestion de memoria (Pila)\n";
        cout << "3. Planificador de CPU (Cola de prioridad)\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            menuListaEnlazada();
            break;
        case 2:
            menuPilaMemoria();
            break;
        case 3:
            menuColaCPU();
            break;
        case 4:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
    return 0;
}