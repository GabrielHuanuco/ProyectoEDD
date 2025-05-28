#include <iostream>
using namespace std;

struct BloqueMemoria //Estructura para representar el bloque de memoria
{
    int ID_Proceso; //Valor asignado al Id del proceso
    int tamanio; //Valor asignado al tamaño del proceso
    BloqueMemoria *siguiente; //Puntero al siguiente bloque en la pila
};

void asignarMemoria(BloqueMemoria *&cima, int ID_Proceso, int tamanio) //Funcion para asignar un bloque de memoria
{
    BloqueMemoria *nuevo = new BloqueMemoria; //Se crea un nuevo bloque de memoria
    nuevo->ID_Proceso = ID_Proceso; //Se asigna los nuevos valores
    nuevo->tamanio = tamanio; //Se asigna un nuevo tamaño
    nuevo->siguiente = cima; //El nuevo bloque apunta al que antes era la cima
    cima = nuevo; //Ahora el nuevo bloque es la cima
    cout<<"Memoria asignada correctamente"; //Mensaje que afirma que el proceso fue agregado correctamente
}