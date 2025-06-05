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
// Retorna true si ambas cadenas son iguales, false si son diferentes
bool compararCadenas(const char a[], const char b[])
{
    int i = 0; // Índice para recorrer las cadenas
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i]) // Si algún carácter es diferente, retorna false
            return false;
        i++;
    }
    return a[i] == b[i]; // Si ambas cadenas terminaron al mismo tiempo, son iguales
}

// -----------------------------------------------------------------------------
// Guarda todos los procesos de la lista enlazada en un archivo
// Cada línea del archivo tendrá: id nombre prioridad
void guardarProcesosEnArchivo(Proceso *cabeza)
{
    ofstream archivo("procesos.txt"); // Abre el archivo para escritura (sobrescribe)
    Proceso *aux = cabeza;
    while (aux != NULL)
    {
        archivo << aux->id << " " << aux->nombre << " " << aux->prioridad << "\n"; // Escribe los datos del proceso
        aux = aux->siguiente;
    }
    archivo.close(); // Cierra el archivo
}

// -----------------------------------------------------------------------------
// Carga los procesos desde el archivo al iniciar el programa
// Inserta cada proceso leído al inicio de la lista enlazada
void cargarProcesosDesdeArchivo(Proceso *&cabeza)
{
    ifstream archivo("procesos.txt"); // Abre el archivo para lectura
    if (!archivo.is_open())
        return; // Si no existe el archivo, no hace nada

    int id, prioridad;
    char nombre[30];
    while (archivo >> id >> nombre >> prioridad)
    {
        Proceso *nuevo = new Proceso; // Reserva memoria para el nuevo proceso
        nuevo->id = id;
        int i = 0;
        for (; nombre[i] != '\0'; i++)
            nuevo->nombre[i] = nombre[i]; // Copia el nombre carácter por carácter
        nuevo->nombre[i] = '\0';
        nuevo->prioridad = prioridad;
        nuevo->siguiente = cabeza;
        cabeza = nuevo; // Inserta el proceso al inicio de la lista
    }
    archivo.close(); // Cierra el archivo
}

// -----------------------------------------------------------------------------
// Inserta un nuevo proceso al inicio de la lista enlazada y guarda en archivo
void insertarProceso(Proceso *&cabeza, int id, const char nombre[], int prioridad)
{
    Proceso *nuevo = new Proceso; // Reserva memoria para el nuevo proceso
    nuevo->id = id;
    int i = 0;
    for (; nombre[i] != '\0'; i++)
        nuevo->nombre[i] = nombre[i]; // Copia el nombre carácter por carácter
    nuevo->nombre[i] = '\0';
    nuevo->prioridad = prioridad;
    nuevo->siguiente = cabeza;
    cabeza = nuevo; // El nuevo proceso es ahora la cabeza de la lista
    cout << "Proceso insertado correctamente.\n";
    guardarProcesosEnArchivo(cabeza); // Guarda la lista actualizada en el archivo
}

// -----------------------------------------------------------------------------
// Busca un proceso por ID en la lista enlazada y muestra su información
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

    while (actual != NULL)
    {
        if (actual->id == idEliminar) // Si encuentra el proceso a eliminar
        {
            if (anterior == NULL)
                cabeza = actual->siguiente; // Si es el primero de la lista
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
        cout << "6. Volver al menu principal\n";
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
    } while (opcion != 6); // Repite hasta que el usuario elija salir
}

// ===================== GESTOR DE MEMORIA (PILA) =====================

// Estructura para representar un bloque de memoria en la pila
struct BloqueMemoria
{
    int ID_Proceso;           // ID del proceso que ocupa el bloque
    int tamanio;              // Tamaño del bloque en MB
    BloqueMemoria *siguiente; // Puntero al siguiente bloque en la pila
};
//Funcion que calcula la cantidad total de memoria actualmente asignada
int memoriaUsada(BloqueMemoria *cima)
{
    int total = 0;  // Se inicializa la variable total en 0 para acumular la memoria usada
    while (cima != NULL)  //Mientras haya bloques en la pila 
    {
        total += cima->tamanio; //Se suma el tamaño del bloque actual al total
        cima = cima->siguiente; //Se avanza al siguiente bloque en la pila 
    }
    return total; //Se devuelve el total acumulado de memoria usada
}
// -----------------------------------------------------------------------------
// Guarda todos los bloques de memoria en un archivo de texto (memoria.txt)
void guardarMemoriaEnArchivo(BloqueMemoria *cima)
{
    ofstream archivo("memoria.txt"); // Abre el archivo para escritura
    BloqueMemoria *aux = cima; // Se declara un puntero auxiliar para recorrer la pila sin modificar el puntero original 
    while (aux != NULL)
    {
        archivo << aux->ID_Proceso << " " << aux->tamanio << "\n"; // Escribe los datos del bloque
        aux = aux->siguiente; //Se avanza al siguiente bloque en la pila
    }
    archivo.close(); // Cierra el archivo
}

// -----------------------------------------------------------------------------
// Carga los bloques de memoria desde el archivo al iniciar el programa
void cargarMemoriaDesdeArchivo(BloqueMemoria *&cima)
{
    ifstream archivo("memoria.txt"); // Abre el archivo para lectura
    if (!archivo.is_open())
        return; // Si no existe el archivo, no hace nada
    int id, tamanio;
    while (archivo >> id >> tamanio)
    {
        BloqueMemoria *nuevo = new BloqueMemoria; // Reserva memoria para el nuevo bloque
        nuevo->ID_Proceso = id; // Se asigna el ID del proceso
        nuevo->tamanio = tamanio; // Se asigna el tamaño del proceso
        nuevo->siguiente = cima; // El nuevo bloque apunta al anterior que era la cima
        cima = nuevo; // Inserta el bloque al inicio de la pila
    }
    archivo.close(); // Cierra el archivo
}

// -----------------------------------------------------------------------------
// Asigna un bloque de memoria (push) y guarda en archivo
void AsignarMemoria(BloqueMemoria *&cima, int ID_Proceso, int tamanio)
{
    BloqueMemoria *nuevo = new BloqueMemoria; // Reserva memoria para el nuevo bloque
    nuevo->ID_Proceso = ID_Proceso; // Se asigna el ID del proceso
    nuevo->tamanio = tamanio; // Se asigna el tamaño del proceso
    nuevo->siguiente = cima; // El nuevo bloque apunta al anterior que era la cima
    cima = nuevo; // El nuevo bloque pasa a ser la cima de la pila
    cout << "Memoria asignada correctamente\n";
    guardarMemoriaEnArchivo(cima); // Guarda la pila actualizada en el archivo
}

// -----------------------------------------------------------------------------
// Libera el bloque de memoria por ID y guarda en archivo
void LiberarMemoriaPorID(BloqueMemoria *&cima, int id)
{
    if (cima == NULL) // Si no hay bloques asignados
    {
        cout << "No hay bloques de memoria asignados\n"; // Mensaje informando que la lista está vacía
        return;
    }
    BloqueMemoria *actual = cima;   // Puntero temporal para recorrer la pila
    BloqueMemoria *anterior = NULL; // Puntero para rastrear el nodo anterior
    while (actual != NULL && actual->ID_Proceso != id) //Busca el nodo que tenga el ID correspondiente 
    {
        anterior = actual; //Se guarda el nodo actual como "anterior"
        actual = actual->siguiente; //Se avanza al siguiente nodo
    }
    if (actual == NULL) //Si se recorrio toda la pila y no se enocntro el ID
    {
        cout << "No se encontro memoria asignada para ese ID\n"; //Mensaje de error
        return; //Salida de la funcion sin ningun cambio
    }
    if (anterior == NULL) //
        cima = actual->siguiente; // Si el nodo a eliminar es el primero
    else
        anterior->siguiente = actual->siguiente; // Si el nodo a eliminar está en medio o al final
    cout << "Memoria liberada para el proceso ID=" << id << "\n";
    delete actual;                 // Libera la memoria del nodo eliminado
    guardarMemoriaEnArchivo(cima); // Guarda la pila actualizada en el archivo
}

// -----------------------------------------------------------------------------
// Muestra todos los bloques de memoria asignados
void MostrarMemoria(BloqueMemoria *cima)
{
    if (cima == NULL) // Si toda la pila esta vacia
    {
        cout << "No hay bloques de memoria asignados\n"; // Mensaje informando que no hay bloques de memoria
        return; // Sale de la funcion
    }
    cout << "Bloques de memoria asignados:\n"; // Mensaje inicial para listar los bloques
    while (cima != NULL)  // Mientras no se llegue al final de la pila
    {
        cout << "Proceso ID: " << cima->ID_Proceso << ", Tamanio: " << cima->tamanio << "MB\n";  // Muestra el ID del proceso y el tamaño de cada bloque en MB
        cima = cima->siguiente; // Avanza al siguiente bloque de la pila
    }
}

// -----------------------------------------------------------------------------
// Busca la memoria asignada a un proceso por su ID en la pila de memoria
int buscarMemoriaPorID(BloqueMemoria *cima, int idBuscar)
{
    while (cima != NULL) // Recorre la pila mientras haya nodos
    {
        if (cima->ID_Proceso == idBuscar)   // Si el ID del proceso coincide con el buscado
            return cima->tamanio;  // Retorna el tamaño de memoria del proceso
        cima = cima->siguiente;   // Avanza al siguiente nodo
    }
    return -1;  // Si no se encuentra el proceso con el ID buscado, retorna -1
}

// -----------------------------------------------------------------------------
// Busca un bloque de memoria por ID de proceso y muestra su información
void BuscarPorID(BloqueMemoria *cima, int id)
{
    while (cima != NULL) // Recorre la pila mientras existan nodos
    {
        if (cima->ID_Proceso == id) // Si el ID del proceso coincide con el buscado
        {
            cout << "Proceso encontrado: ID=" << cima->ID_Proceso
                 << ", Tamanio=" << cima->tamanio << "MB\n"; // Imprime la información del proceso encontrado
            return; // Termina la función al encontrar el proceso
        }
        cima = cima->siguiente; // Avanza al siguiente nodo
    }
    cout << "Proceso con ID=" << id << " no encontrado\n"; // Si no se encontró el proceso, muestra un mensaje indicándolo
}

// -----------------------------------------------------------------------------
// Menú para gestion de memoria (pila) con búsqueda por ID y opción de salir
void menuPilaMemoria()
{
    BloqueMemoria *pilaMemoria = NULL;      // Puntero inicial a la pila de bloques de memoria
    cargarMemoriaDesdeArchivo(pilaMemoria); // Carga los bloques desde archivo si existen
    int memoriaTotal;
    cout << "Ingrese la cantidad total de memoria disponible en MB: ";
    cin >> memoriaTotal;
    int op;                                 // Variable para guardar la opción del menú

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
        cin >> op; // Entrada de la opción

        switch (op)
        {
        case 1:
        {
            int id, tam;
            cout << "ID del proceso: ";
            cin >> id;
            cout << "Tamanio en MB: ";
            cin >> tam;
            int usada = memoriaUsada(pilaMemoria); 
            // Verifica si la memoria ocupada más la memoria solicitada supera la memoria total disponible
            if (usada + tam > memoriaTotal) 
            {
                cout << "Error: No hay suficiente memoria disponible. "
                     << "Disponible: " << (memoriaTotal - usada) << "MB\n";
            }
            else
            {
                AsignarMemoria(pilaMemoria, id, tam); // Si hay suficiente memoria, llama a la función para asignar el bloque al proceso
            }
            break; // Finaliza el caso o la ejecución dentro de un switch o loop
        }
        case 2:
        {
            int id;
            cout << "Ingrese el ID del proceso a liberar: ";
            cin >> id;
            LiberarMemoriaPorID(pilaMemoria, id); // Llama a la función para liberar por ID
            break;
        }
        case 3:
            MostrarMemoria(pilaMemoria); // Llama a la función para mostrar la memoria
            break;
        case 4:
        {
            int id;
            cout << "Ingrese el ID del proceso a buscar: ";
            cin >> id;
            BuscarPorID(pilaMemoria, id); // Llama a la función para buscar un ID
            break;
        }
        case 5:
            cout << "Volviendo al menu principal...\n"; // Mensaje de salida
            break;
        default:
            cout << "Opcion incorrecta\n"; // Mensaje si se ingresa una opción inválida
        }
    } while (op != 5); // Se repite el menú hasta que se seleccione salir
}

// ===================== PLANIFICADOR DE CPU (COLA DE PRIORIDAD) =====================

// Estructura para representar un proceso en la cola de CPU
struct NodoCPU
{
    int id;             // Identificador del proceso
    char nombre[30];    // Nombre del proceso
    int prioridad;      // Prioridad del proceso (mayor número = mayor prioridad)
    NodoCPU *siguiente; // Puntero al siguiente proceso en la cola
};

// -----------------------------------------------------------------------------
// Guarda todos los procesos de la cola de CPU en un archivo de texto (cola_cpu.txt)
void guardarColaCPUEnArchivo(NodoCPU *frente)
{
    ofstream archivo("cola_cpu.txt"); // Abre el archivo para escritura
    NodoCPU *aux = frente;
    while (aux != NULL)
    {
        archivo << aux->id << " " << aux->nombre << " " << aux->prioridad << "\n"; // Escribe los datos del proceso
        aux = aux->siguiente;
    }
    archivo.close(); // Cierra el archivo
}

// -----------------------------------------------------------------------------
// Carga los procesos de la cola de CPU desde el archivo al iniciar el programa
void cargarColaCPUDesdeArchivo(NodoCPU *&frente)
{
    ifstream archivo("cola_cpu.txt"); // Abre el archivo para lectura
    if (!archivo.is_open())
        return; // Si no existe el archivo, no hace nada
    int id, prioridad;
    char nombre[30];
    while (archivo >> id >> nombre >> prioridad)
    {
        NodoCPU *nuevo = new NodoCPU; // Reserva memoria para el nuevo nodo
        nuevo->id = id;
        int i = 0;
        for (; nombre[i] != '\0'; i++)
            nuevo->nombre[i] = nombre[i]; // Copia el nombre carácter por carácter
        nuevo->nombre[i] = '\0';
        nuevo->prioridad = prioridad;
        nuevo->siguiente = frente;
        frente = nuevo; // Inserta el nodo al inicio de la cola
    }
    archivo.close(); // Cierra el archivo
}

// -----------------------------------------------------------------------------
// Busca un proceso por ID en la lista enlazada de procesos
// Retorna true si lo encuentra y copia el nombre y prioridad, false si no existe
bool obtenerDatosProcesoPorID(Proceso *cabeza, int idBuscar, char nombre[], int &prioridad)
{
    Proceso *aux = cabeza;
    while (aux != NULL)
    {
        if (aux->id == idBuscar)
        {
            int i = 0;
            for (; aux->nombre[i] != '\0'; i++)
                nombre[i] = aux->nombre[i]; // Copia el nombre carácter por carácter
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
    NodoCPU *nuevo = new NodoCPU; // Reserva memoria para el nuevo nodo
    nuevo->id = id;
    int i = 0;
    for (; nombre[i] != '\0'; i++)
        nuevo->nombre[i] = nombre[i]; // Copia el nombre carácter por carácter
    nuevo->nombre[i] = '\0';
    nuevo->prioridad = prioridad;
    nuevo->siguiente = NULL;
    return nuevo;
}

// -----------------------------------------------------------------------------
// Inserta un proceso en la cola, manteniendo el orden por prioridad (mayor primero)
void encolarCPU(NodoCPU *&frente, int id, const char nombre[], int prioridad)
{
    NodoCPU *nuevo = crearNodoCPU(id, nombre, prioridad); // Crea un nuevo nodo
    if (frente == NULL || prioridad > frente->prioridad)
    {
        nuevo->siguiente = frente; // El nuevo nodo apunta al frente actual
        frente = nuevo;            // El nuevo nodo se convierte en el nuevo frente
    }
    else
    {
        NodoCPU *actual = frente; // Apuntador temporal al frente
        NodoCPU *anterior = NULL; // Apuntador al nodo anterior
        while (actual != NULL && actual->prioridad >= prioridad)
        {
            anterior = actual;          // Guarda el nodo actual como anterior
            actual = actual->siguiente; // Avanza al siguiente nodo
        }
        anterior->siguiente = nuevo; // Inserta el nuevo nodo entre anterior y actual
        nuevo->siguiente = actual;
    }
    cout << "Proceso encolado en la CPU con prioridad " << prioridad << ".\n";
    guardarColaCPUEnArchivo(frente); // Guarda la cola actualizada en el archivo
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
    NodoCPU *temp = frente;          // Guarda el nodo que será eliminado
    frente = frente->siguiente;      // Avanza el frente al siguiente nodo
    delete temp;                     // Libera la memoria del nodo ejecutado
    guardarColaCPUEnArchivo(frente); // Guarda la cola actualizada en el archivo
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
    NodoCPU *colaCPU = NULL;            // Cola vacía al inicio
    cargarColaCPUDesdeArchivo(colaCPU); // Carga los procesos guardados en el archivo

    Proceso *listaProcesos = NULL;             // Lista enlazada de procesos para consulta
    cargarProcesosDesdeArchivo(listaProcesos); // Carga los procesos guardados en el archivo

    int opcion; // Variable para almacenar la opción del usuario
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
    } while (opcion != 4); // Repite hasta que el usuario elija salir
}

// ===================== MENÚ PRINCIPAL =====================

int main()
{
    int opcion; // Variable para almacenar la opción del usuario
    do
    {
        // Menú principal del sistema
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
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 4); // Repite hasta que el usuario elija salir
    return 0; // Fin del programa
}