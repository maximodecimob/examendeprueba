#include <iostream>
#include <fstream>
using namespace std;
// muestra un menú que permite al usuario elegir entre buscar información de una reserva
// por código, mostrar un listado con las reservas disponibles por fecha y precio máximo, o generar un informe
// con las reservas disponibles según su fecha.
// Reserva contendrá los siguientes datos:
// - DNI del cliente
// - Fecha de inicio 1
// - Número de noches
// - Código de habitación
// - Precio
// Agencia contendrá:
// - Una lista de reservas de tamano 100
// - Un contador
typedef struct 
{
    int dia;
    int mes;
    int ano;
}Fecha;

typedef struct{
    string DNI;
    Fecha inicio;
    int noches;
    int codhabitacion;
    float precio;
}Reserva;
typedef struct{
    Reserva todas[100];
    int contador;
}Agencia;
Agencia cargaDatosA(Agencia & data){
    ifstream archivo;
    char barra;
    archivo.open("reservasA.txt");
    if(archivo.is_open()){
        archivo>>data.contador;
        for (int i = 0; i < data.contador; i++)
        {   Reserva q;
            archivo>>q.DNI>>q.inicio.ano>>barra>>q.inicio.mes>>barra>>q.inicio.dia;
            archivo>>q.noches>>q.codhabitacion>>q.precio;
            data.todas[i]=q;
        }
    archivo.close();

    }else{
        cout<<"Error al conseguir el archivoA";
    }
    return data;
}
Agencia cargaDatosB(Agencia data){
    ifstream archivo;
    char barra;
    archivo.open("reservasB.txt");
    if (archivo.is_open()){ 
        bool terminado = false;
        int i = 0;
        while(!terminado && i < 100)
        {   
        Reserva q;
        archivo >> q.DNI;
            if (q.DNI != "-1"){
                archivo >>q.inicio.ano>>barra>>q.inicio.mes>>barra>>q.inicio.dia;
                archivo>>q.noches>>q.codhabitacion>>q.precio;
                data.todas[i]=q;
                i++;
            }else
            {
                terminado = true;
            }
        }
    }
    else{
        cout<<"Error al conseguir el archivoB";
    }
    return data;
}
int buscar_reserva(Agencia data,string DNI){
    int id = -1;
    for (int i = 0; i < data.contador; i++)
    {
        if(data.todas[i].DNI==DNI){
            id=i;
            i=data.contador;
        }
    }
    return id;
    
}
void informacionReserva(int id,Agencia data){
    if (id != -1){
    cout<<"-------------------------------"<<endl;
    cout<<"INFORMACIÓN RESERVA"<<endl;
    cout<<"-------------------------------"<<endl;
    cout<<"DNI del cliente: "<<data.todas[id].DNI<<endl;
    cout<<"Fecha de inicio: "<<data.todas[id].inicio.dia<<"/"<<data.todas[id].inicio.mes<<"/"<<data.todas[id].inicio.ano<<endl;
    cout<<"Número de noches: "<<data.todas[id].noches<<endl;
    cout<<"Código de habitación: "<<data.todas[id].codhabitacion<<endl;
    cout<<"Precio: "<<data.todas[id].precio<<" € "<<endl;
    cout<<"-------------------------------"<<endl;
    }else{
        cout<<"No encontrado \n";
    }
}
void informegeneral(Agencia data){
    float sumatorio=0;
    float medio=0;
    float mednoches=0;
    float min=data.todas[0].precio;
    float max=data.todas[0].precio;
    int contador24=0,contador25=0;
    for (int i = 0; i < data.contador; i++)
    {
        mednoches += data.todas[i].noches;
        sumatorio +=data.todas[i].precio;
        if(data.todas[i].precio<min){
            min=data.todas[i].precio;
        }
        if (data.todas[i].precio>max)
        {
            max=data.todas[i].precio;
        }
        if (data.todas[i].inicio.ano == 2024) {
            contador24++;
            }
        else if (data.todas[i].inicio.ano == 2025) {
            contador25++; 
            }
    }
    medio=sumatorio/data.contador;
    mednoches=mednoches/data.contador;
    
    cout<<"--------------------------------------------------"<<endl;
    cout<<"INFORME GENERAL"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"Número total de reservas: "<<data.contador<<endl;
    cout<<"Precio total de todas las reservas: "<<sumatorio<<" euros"<<endl;
    cout<<"Precio promedio por reserva: "<<medio<<" euros"<<endl;
    cout<<"Duración promedio de las reservas: "<<mednoches<< " noches"<<endl;
    cout<<"Número de reservas por año:"<<endl;
    cout << "Año 2024: " << contador24 << " reservas" << endl;
    cout << "Año 2025: " << contador25 << " reservas" << endl;
    cout<<"Precio mínimo de una reserva: "<<min<<" euros"<<endl;
    cout<<"Precio máximo de una reserva: "<<max<<" euros"<<endl;
    cout<<"--------------------------------------------------"<<endl;

}
bool reservaEnFecha(Reserva reservado,int mess,int anno){
    bool salida=false;
    if(reservado.inicio.mes==mess && reservado.inicio.ano==anno){
        salida=true;
    }
    return salida;
}
void generaInforme(Agencia data){
    int anno,mess;
    cout<<"Introduce el año: "<<endl;
    cin>>anno;
    cout<<"Introduce el mes: "<<endl;
    cin>>mess;
    ofstream archivo;
    archivo.open("informe.txt");
    archivo<<"Reservas realizadas durante "<<mess<<"/"<<anno<<endl;
    for (int i = 0; i < data.contador; i++) {
        if (reservaEnFecha(data.todas[i], mess, anno)) { 
        archivo << data.todas[i].DNI << ": Reserva de " <<data.todas[i].noches;
        archivo << " noches en la habitación " << data.todas[i].codhabitacion<< ", por ";
        archivo << data.todas[i].precio << " euros." << endl;
            }
        }
    archivo.close();
    cout<<"Generando archivo..."<<endl;
    cout<<"...archivo generado correctamente!"<<endl;
}
void menu(){
    Agencia data;
    data.contador=0;
    data=cargaDatosA(data);
    //data=cargaDatosB(data);
    bool programa=true;
    int selector;
    bool info = true;
    string DNI;
    int id;
    while(programa){
        cout<<"Presiona el número de lo que \nquieras realizar\n";
        cout<<"-----------------------------------\n";
        cout<<"1- Buscar una reserva con el codigo\n";
        cout<<"2- Conseguir el informe general    \n";
        cout<<"3- Informe de una fecha            \n";
        cout<<"4- Salir del programa              \n";
        cout<<"-----------------------------------\n";
        info = true;
        while(info){
            cin>>selector;
            switch(selector)
            {
            case 1:
                cout<<"Introduce tu DNI para buscar la reserva: ";
                cin>>DNI;
                id=buscar_reserva(data,DNI);
                informacionReserva(id,data);
                info=false;
                break;
            case 2:
                informegeneral(data);
                info=false;
                break;
            case 3:
                generaInforme(data);
                info=false;
                break;
            case 4:
                programa = false;
                info = false;
                break;
            default:
                cout<<"Has introducido mal la entrada introduce otra\n";
                break;
            }
        }

    }
}


int main(){
    menu();
}
