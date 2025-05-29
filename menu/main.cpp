#include <iostream>
#include <string>
using namespace std;

const int MAX_PROCESOS = 100;

string pilaProcesos[MAX_PROCESOS];
int topePila = -1;

string listaProcesos[MAX_PROCESOS];
int cantidadLista = 0;

string colaProcesos[MAX_PROCESOS];
int frenteCola = 0;
int finalCola = -1;
int cantidadCola = 0;

void menuPila() {
    int opcion;
    string proceso;

    do {
        cout << "\n--- SUBMENU: PILA DE PROCESOS ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Mostrar procesos\n";
        cout << "4. Volver al submenu de procesos\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                if (topePila < MAX_PROCESOS - 1) {
                    cout << "Ingrese nombre del proceso: ";
                    getline(cin, proceso);
                    pilaProcesos[++topePila] = proceso;
                } else {
                    cout << "La pila esta llena.\n";
                }
                break;
            case 2:
                if (topePila >= 0) {
                    cout << "Proceso eliminado: " << pilaProcesos[topePila--] << "\n";
                } else {
                    cout << "La pila esta vacia.\n";
                }
                break;
            case 3:
                if (topePila < 0) {
                    cout << "Pila vacia.\n";
                } else {
                    cout << "Procesos en pila:\n";
                    for (int i = topePila; i >= 0; i--) {
                        cout << "- " << pilaProcesos[i] << "\n";
                    }
                }
                break;
            case 4: cout << "Volviendo al submenu...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}

void menuLista() {
    int opcion;
    string proceso;

    do {
        cout << "\n--- SUBMENU: LISTA DE PROCESOS ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar primer proceso\n";
        cout << "3. Mostrar procesos\n";
        cout << "4. Volver al submenu de procesos\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                if (cantidadLista < MAX_PROCESOS) {
                    cout << "Ingrese nombre del proceso: ";
                    getline(cin, proceso);
                    listaProcesos[cantidadLista++] = proceso;
                } else {
                    cout << "La lista esta llena.\n";
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
                    cout << "La lista esta vacia.\n";
                }
                break;
            case 3:
                if (cantidadLista == 0) {
                    cout << "Lista vacia.\n";
                } else {
                    cout << "Procesos en lista:\n";
                    for (int i = 0; i < cantidadLista; i++) {
                        cout << "- " << listaProcesos[i] << "\n";
                    }
                }
                break;
            case 4: cout << "Volviendo al submenu...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}

void menuCola() {
    int opcion;
    string proceso;

    do {
        cout << "\n--- SUBMENU: COLA DE PROCESOS ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Mostrar procesos\n";
        cout << "4. Volver al submenu de procesos\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                if (cantidadCola < MAX_PROCESOS) {
                    cout << "Ingrese nombre del proceso: ";
                    getline(cin, proceso);
                    finalCola = (finalCola + 1) % MAX_PROCESOS;
                    colaProcesos[finalCola] = proceso;
                    cantidadCola++;
                } else {
                    cout << "La cola esta llena.\n";
                }
                break;
            case 2:
                if (cantidadCola > 0) {
                    cout << "Proceso eliminado: " << colaProcesos[frenteCola] << "\n";
                    frenteCola = (frenteCola + 1) % MAX_PROCESOS;
                    cantidadCola--;
                } else {
                    cout << "La cola esta vacia.\n";
                }
                break;
            case 3:
                if (cantidadCola == 0) {
                    cout << "Cola vacia.\n";
                } else {
                    cout << "Procesos en cola:\n";
                    for (int i = 0; i < cantidadCola; i++) {
                        int index = (frenteCola + i) % MAX_PROCESOS;
                        cout << "- " << colaProcesos[index] << "\n";
                    }
                }
                break;
            case 4: cout << "Volviendo al submenu...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}

void menuProcesos() {
    int opcion;
    do {
        cout << "\n===== SUBMENU: GESTION DE PROCESOS =====\n";
        cout << "1. Pila de procesos\n";
        cout << "2. Lista de procesos\n";
        cout << "3. Cola de procesos\n";
        cout << "4. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuPila(); break;
            case 2: menuLista(); break;
            case 3: menuCola(); break;
            case 4: cout << "Regresando al menu principal...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}

void mostrarMenuPrincipal() {
    int opcion;
    do {
        cout << "\n======= MENU PRINCIPAL =======\n";
        cout << "1. Gestion de procesos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuProcesos(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}

int main() {
    mostrarMenuPrincipal();
    return 0;
}