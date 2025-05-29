#include <iostream>
#include <string>
using namespace std;

// ======= Variables globales =======
const int MAX_PROCESOS = 100;
string pilaProcesos[MAX_PROCESOS];
int topePila = -1;

string listaProcesos[MAX_PROCESOS];
int cantidadLista = 0;

// ======= Submenú: PILA =======
void menuPila() {
    int opcion;
    string proceso;

    do {
        cout << "\n--- SUBMENÚ: PILA DE PROCESOS ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Mostrar procesos\n";
        cout << "4. Volver al submenú de procesos\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                if (topePila < MAX_PROCESOS - 1) {
                    cout << "Ingrese nombre del proceso: ";
                    getline(cin, proceso);
                    pilaProcesos[++topePila] = proceso;
                } else {
                    cout << "La pila está llena.\n";
                }
                break;
            case 2:
                if (topePila >= 0) {
                    cout << "Proceso eliminado: " << pilaProcesos[topePila--] << "\n";
                } else {
                    cout << "La pila está vacía.\n";
                }
                break;
            case 3:
                if (topePila < 0) {
                    cout << "Pila vacía.\n";
                } else {
                    cout << "Procesos en pila:\n";
                    for (int i = topePila; i >= 0; i--) {
                        cout << "- " << pilaProcesos[i] << "\n";
                    }
                }
                break;
            case 4: cout << "Volviendo al submenú...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 4);
}

// ======= Submenú: LISTA =======
void menuLista() {
    int opcion;
    string proceso;

    do {
        cout << "\n--- SUBMENÚ: LISTA DE PROCESOS ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar primer proceso\n";
        cout << "3. Mostrar procesos\n";
        cout << "4. Volver al submenú de procesos\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                if (cantidadLista < MAX_PROCESOS) {
                    cout << "Ingrese nombre del proceso: ";
                    getline(cin, proceso);
                    listaProcesos[cantidadLista++] = proceso;
                } else {
                    cout << "La lista está llena.\n";
                }
                break;
            case 2:
                if (cantidadLista > 0) {
                    cout << "Proceso eliminado: " << listaProcesos[0] << "\n";
                    for (int i = 1; i < cantidadLista; i++) {
                        listaProcesos[i - 1] = listaProcesos[i];
                    }
                    cantidadLista--;
                } else {
                    cout << "La lista está vacía.\n";
                }
                break;
            case 3:
                if (cantidadLista == 0) {
                    cout << "Lista vacía.\n";
                } else {
                    cout << "Procesos en lista:\n";
                    for (int i = 0; i < cantidadLista; i++) {
                        cout << "- " << listaProcesos[i] << "\n";
                    }
                }
                break;
            case 4: cout << "Volviendo al submenú...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 4);
}

// ======= Submenú: GESTIÓN DE PROCESOS =======
void menuProcesos() {
    int opcion;
    do {
        cout << "\n===== SUBMENÚ: GESTIÓN DE PROCESOS =====\n";
        cout << "1. Pila de procesos\n";
        cout << "2. Lista de procesos\n";
        cout << "3. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuPila(); break;
            case 2: menuLista(); break;
            case 3: cout << "Regresando al menú principal...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 3);
}

// ======= Menú principal =======
void mostrarMenuPrincipal() {
    int opcion;
    do {
        cout << "\n======= MENÚ PRINCIPAL =======\n";
        cout << "1. Gestión de procesos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuProcesos(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

// ======= Función principal =======
int main() {
    mostrarMenuPrincipal();
    return 0;
}