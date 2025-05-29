#include <iostream>
using namespace std;

struct BloqueMemoria //Estructura para representar el bloque de memoria
{
    int ID_Proceso; //Valor asignado al Id del proceso
    int tamanio; //Valor asignado al tamaño del proceso
    BloqueMemoria *siguiente; //Puntero al siguiente bloque en la pila
};

void AsignarMemoria(BloqueMemoria *&cima, int ID_Proceso, int tamanio) //Funcion para asignar un bloque de memoria
{
    BloqueMemoria *nuevo = new BloqueMemoria; //Se crea un nuevo bloque de memoria
    nuevo->ID_Proceso = ID_Proceso; //Se asigna los nuevos valores
    nuevo->tamanio = tamanio; //Se asigna un nuevo tamaño
    nuevo->siguiente = cima; //El nuevo bloque apunta al que antes era la cima
    cima = nuevo; //Ahora el nuevo bloque es la cima
    cout<<"Memoria asignada correctamente"; //Mensaje que afirma que el proceso fue agregado correctamente
}
void LiberarMemoria(BloqueMemoria *&cima) //Funcion para liberar un bloque de memoria
{
    if(cima==NULL) //Si el bloque de memoria esta vacia
    {
        cout<<"No hay bloques de memoria asignados ";//Mensaje que afirma que no existe ningun bloque de memoria
        return;
    }
    cout<<"Liberando memoria del proceso ID="<< cima->ID_Proceso<<"\n"; //Mensaje que afirme el procesos de liberacion de memoria
    BloqueMemoria *temp = cima; //Guarda temporalmente el bloque de memoria
    cima = cima->siguiente; //Mueve la cima al siguiente bloque
    delete temp; //Elimina el bloque que estaba en la cima
}
void MostrarMemoria(BloqueMemoria *cima) //Funcion para mostrar los bloques de memoria
{
    if(cima==NULL)//Si el bloque de memoria esta vacia
    {
        cout<<"No hay bloques de memoria asignados \n";//Mensaje que afirma que no existe ningun bloque de memoria
        return;
    }
    cout<<"Bloques de memoria asignados: \n";//Mensaje que afirma el proceso asginado de los bloques de memoria
    while(cima!=NULL)//Si hay bloques de memoria
    {
        cout<<"Proceso ID: "<<cima->ID_Proceso<<", Tamanio: "<<cima->tamanio<<"MB \n";//Mensaje mostrando los bloques de memoria
        cima = cima->siguiente;//Mueve la cima al siguiente bloque
    }
}
int main()
{
    BloqueMemoria *pilaMemoria = NULL;
    int op;
    do
    {
        cout<<"\n ---- Gestion de Memoria ---- \n";
        cout<<"1. Asiganr Memoria \n";
        cout<<"2. Liberar Memoria \n";
        cout<<"3. Ver estado de la Memoria \n";
        cout<<"Seleccione una opcion: ";
        cin>>op;
        switch(op)
        {
            case 1:
                int id, tam;
                cout<<"ID del proceso: ";
                cin>>id;
                cout<<"Tamanio en MB: ";
                cin>>tam;
                AsignarMemoria(pilaMemoria, id, tam);
                break;
            case 2:
                LiberarMemoria(pilaMemoria);
                break;
            case 3:
                MostrarMemoria(pilaMemoria);
                break;
            default:
                cout<<"Opcion incorrecta \n";
            

        }
    }
    while(op!=4);
}