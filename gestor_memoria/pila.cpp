#include <iostream>
using namespace std;

struct BloqueMemoria //Estructura para representar el bloque de memoria
{
    int ID_Proceso; //Valor asignado al Id del proceso
    int tamanio; //Valor asignado al tamaño del proceso
    BloqueMemoria *siguiente; //Puntero al siguiente bloque en la pila
};
