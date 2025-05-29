#include <iostream>
using namespace std;

void listarProcesos() {
    cout << "\n--- Listando procesos ---\n";
   
}

void agregarProceso() {
    cout << "\n--- Agregando proceso ---\n";
   
}

void editarProceso() {
    cout << "\n--- Editando proceso ---\n";
   
}

void eliminarProceso() {
    cout << "\n--- Eliminando proceso ---\n";
    
}


void menuProcesos() {
    int opcion;
    do {
        cout << "\n SUBMENU: GESTION DE PROCESOS \n";
        cout << "1. Listar procesos\n";
        cout << "2. Agregar proceso\n";
        cout << "3. Editar proceso\n";
        cout << "4. Eliminar proceso\n";
        cout << "0. Volver al menu principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) 
        {
            case 1:
             listarProcesos();
            break;

            case 2: 
            agregarProceso(); 
            break;

            case 3: 
            editarProceso();
            break;

            case 4: 
            eliminarProceso(); 
            break;
            case 5: cout << "Regresando al menú principal...\n"; break;
            default: cout << "Opción invalida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
}

//  Menu principal 
void mostrarMenuPrincipal() {
    int opcion;
    do {
        cout << "\n MENU PRINCIPAL \n";
        cout << "1. Gestion de procesos\n";
        cout << "0. Salir del sistema\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuProcesos(); break;
            case 0: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}

int main() {
    mostrarMenuPrincipal();
    return 0;
}
