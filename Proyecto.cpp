#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct producto{
    string nombre;
    float precio;
};

struct cliente{
    string apellido;
    vector<producto>listaPedido;
};

struct fecha{
    int dia;
    int mes;
    int year;
};

struct reporte{
    float ventasDia;
    fecha Fecha;
};

vector<producto>comidas;
vector<producto>bebidas;
vector<reporte>reportes;
queue<cliente>colaPedido;

float ventasDia=0;
fecha Fecha;

void inicio();
void administrador();
void empleado();

void atenderPedido();
void despacharPedido();
void pedidosPendientes();
void ventasDelDia();

bool acceso(string);
void productosIniciales();
void menuComidas(cliente&);
void menuBebidas(cliente&);
void mostrarMenu(vector<producto>);
float montoporpedido(cliente &Pedido);

void pedirFecha(fecha&);
bool abisiesto(int);
void mostrarFecha(fecha);
bool compFechas(reporte,reporte);

int main(void){
    //Llenar el menu con los primeros productos
    productosIniciales();

    inicio();

    return 0;
}

void inicio(){
    int opcion;
    bool status = true;

    cout << endl << "BIENVENIDO A -------" << endl;

    while(status){
        cout << endl << " ---INICIO---" << endl;
        cout << "Acceder como: " << endl;
        cout << "1) Administrador" << endl;
        cout << "2) Empleado" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion; cin.ignore();

        switch(opcion){

            case 1:
                administrador();
                break;
            case 2:
                empleado();
                break;
            default:
                cout << endl << "La opcion ingresada no es valida" << endl;
        }

    }

}

void administrador(){
    string password;
    bool status=true;

    do{
        char opcion;
        cout << endl << "Ingrese el contrase\244a: ";
        getline(cin,password);

        if(!acceso(password)){
            cout << endl << "contrase\244a incorrecta!" << endl;
            cout << "Desea volver a intentarlo? s/n: ";
            cin >> opcion; cin.ignore();

            switch(opcion){
                case 'S':
                case 's':
                    break;
                case 'N':
                case 'n':
                    return;
                default:
                    cout << "opcion no valida" << endl << endl;
            }
        }else{
            cout << endl << "Acceso concedido" << endl;
            status=false;
        }
    }while(status);

    status=true;
    while(status){
        int opcion;

        cout << endl << " ---MENU ADMINISTRADOR--- " << endl;
        cout << "1) Atender pedido \t5) Cierre de caja" << endl;
        cout << "2) Despachar pedido \t6) Editar menu" << endl;
        cout << "3) Pedidos pendientes \t7) Reporte de ventas" << endl; 
        cout << "4) Ventas del dia \t8) Cambiar modo de acceso" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion; cin.ignore();

        switch(opcion){
            case 1:
                atenderPedido();
                break;
            case 2:
                despacharPedido();
                break;
            case 3:
                pedidosPendientes();
                break;
            case 4:
                ventasDelDia();
                break;
            case 5:
                if(!colaPedido.empty()){
                    cout << endl << "Antes del cierra atiende todos los pedidos" << endl;
                }else{

                }
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                cout << endl << "Saliendo..." << endl;
                status=false;
                break;
            default:
                cout << endl << "La opcion ingresada no es valida" << endl;
        }
    }
}

void empleado(){
    bool status=true;

    while(status){
        int opcion;

        cout << endl << " ---MENU EMPLEADO--- " << endl;
        cout << "1) Atender pedido \t4) Ventas del dia" << endl;
        cout << "2) Despachar pedido \t5) Cierre de caja" << endl;
        cout << "3) Pedidos pendientes \t6) Cambiar modo de acceso" << endl; 
        cout << "Ingrese una opcion: ";
        cin >> opcion; cin.ignore();

        switch(opcion){
            case 1:
                atenderPedido();
                break;
            case 2:
                despacharPedido();
                break;
            case 3:
                pedidosPendientes();
                break;
            case 4:
                ventasDelDia();
                break;
            case 5:
                if(!colaPedido.empty()){
                    cout << endl << "Antes del cierra atiende todos los pedidos" << endl;
                }else{

                }
                break;
            case 6:
                cout << endl << "Saliendo..." << endl;
                status=false;
                break;
            default:
                cout << endl << "La opcion ingresada no es valida" << endl;
        }
    }
}

void atenderPedido(){
    cliente Pedido;
    float monto;
    cout << endl << " --ATENDIENDO PEDIDO--";
    cout << endl << "Ingrese el apellido: ";
    getline(cin,Pedido.apellido);

    bool status=true;
    while(status){
        int opcion;
        cout << endl << "Seleccione el tipo de producto: " << endl;
        cout << "1) Comidas \t3) Finalizar pedido" << endl;
        cout << "2) Bebidas \t4) Cancelar pedido" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion; cin.ignore();
        while(opcion==3 && Pedido.listaPedido.empty()){
            cout << endl << "Debes comprar algo o cancelar el pedido" << endl;
            cout << endl << "Seleccione el tipo de producto: " << endl;
            cout << "1) Comidas \t3) Finalizar pedido" << endl;
            cout << "2) Bebidas \t4) Cancelar pedido" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion; cin.ignore();
        }

        switch(opcion){
            case 1:
                menuComidas(Pedido);
                break;
            case 2:
                menuBebidas(Pedido);
                break;
            case 3:
                monto=montoporpedido(Pedido);
                cout << endl << "Gracias cliente " << Pedido.apellido << " por su compra de $" << monto << endl;
                colaPedido.push(Pedido);
                ventasDia+=monto;
                status=false;
                break;
            case 4:
                return;
            default:
                cout << endl << "La opcion ingresada no es valida" << endl;
        }
    }
}

void despacharPedido(){
    if(colaPedido.empty()){
        cout << endl << "No se puede despachar, cola vacia" << endl;
    }else{
        cliente Pedido=colaPedido.front();
        cout << endl << "El pedido del cliente " << Pedido.apellido << " esta listo" << endl;
        cout << "Pedido despachado!" << endl;
        colaPedido.pop();
    }
}

void pedidosPendientes(){
    cout << endl << "Pedidos pendientes: " << colaPedido.size() << endl;
}

void ventasDelDia(){
    cout << endl << "Se han vendido $" << ventasDia << endl;
}



bool acceso(string password){
    if(password == "password"){
        return true;
    }else{
        return false;
    }
}

void productosIniciales(){
    producto Producto;

    Producto.nombre="Torta loca";
    Producto.precio=2.00;
    comidas.push_back(Producto);

    Producto.nombre="Cafe";
    Producto.precio=0.35;
    bebidas.push_back(Producto);

    Producto.nombre="CocaCola";
    Producto.precio=1.00;
    bebidas.push_back(Producto);

    Producto.nombre="Torta maciza";
    Producto.precio=1.75;
    comidas.push_back(Producto);

    Producto.nombre="7up";
    Producto.precio=0.75;
    bebidas.push_back(Producto);

    Producto.nombre="Torta simple";
    Producto.precio=1.25;
    comidas.push_back(Producto);
}

void menuComidas(cliente &Pedido){
        int opcion, cantidad;
        mostrarMenu(comidas);
        cout << endl << "Ingrese una opcion: ";
        cin >> opcion; cin.ignore();
        while(opcion<1 || opcion>comidas.size()){
            cout << endl << "La opcion ingresada no es valida" << endl;
            mostrarMenu(comidas);
            cout << endl << "Ingrese una opcion: ";
            cin >> opcion; cin.ignore();
        }
        cout << "Ingrese la cantidad a comprar: ";
        cin >> cantidad;cin.ignore();
        while(cantidad<1){
            cout << endl << "La cantidad ingresada no es valida" << endl;
            cout << endl << "Ingrese la cantidad a comprar: ";
            cin >> cantidad; cin.ignore();
        }

        for(int i=0; i<cantidad; i++){
            Pedido.listaPedido.push_back(comidas.at(opcion-1)); 
        }   
        cout << endl << "Producto agregado a la lista!" << endl;
}

void menuBebidas(cliente &Pedido){
        int opcion, cantidad;
        mostrarMenu(bebidas);
        cout << endl << "Ingrese una opcion: ";
        cin >> opcion; cin.ignore();
        while(opcion<1 || opcion>bebidas.size()){
            cout << endl << "La opcion ingresada no es valida" << endl;
            mostrarMenu(bebidas);
            cout <<  endl << "Ingrese una opcion: ";
            cin >> opcion; cin.ignore();
        }

        cout << "Ingrese la cantidad a comprar: ";
        cin >> cantidad;cin.ignore();
        while(cantidad<1){
            cout << endl << "La cantidad ingresada no es valida" << endl;
            cout << endl << "Ingrese la cantidad a comprar: ";
            cin >> cantidad; cin.ignore();
        }

        for(int i=0; i<cantidad; i++){
            Pedido.listaPedido.push_back(bebidas.at(opcion-1));
        }
        cout << endl << "Producto agregado a la lista!" << endl;
}

void mostrarMenu( vector<producto>lista){
    cout << endl << "--MENU--";
    for(int i=0; i<lista.size() ; i++){
            cout << endl << i+1 << ") " << lista.at(i).nombre << "..... $" << lista.at(i).precio;
    }
}

float montoporpedido(cliente &Pedido){
    float monto=0;

    for(int i=0; i<Pedido.listaPedido.size(); i++){
        monto+=Pedido.listaPedido[i].precio;
    }
    return monto;
}

void pedirFecha(fecha &Fecha){
    bool continuar=true;

    while (continuar){
    cout << "Ingrese el a\244o: ";
    cin >> Fecha.year;

    if (Fecha.year < 2020){
        cout << endl << "Error! / No puedes ingresar a\244os anteriores al actual" << endl << endl;
    } else {
        cout  << "Ingrese el mes (en formato numerico): ";
        cin >> Fecha.mes;
        switch (Fecha.mes){
            case 1:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 31 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 2:
                if (abisiesto(Fecha.year) == true){
                    cout << "Ingrese el dia: ";
                    cin >> Fecha.dia; 
                    if (Fecha.dia > 29 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                    }else {
                        continuar=false;
                    }
                }else {
                    cout << "Ingrese el dia: ";
                    cin >> Fecha.dia; 
                    if (Fecha.dia > 28 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                    }else {
                        continuar=false;
                    }
                }
                break;
            case 3:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 31 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 4:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 30 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 5:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 31 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 6:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 30 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 7:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 31 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 8:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 31 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 9:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 30 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 10:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 31 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 11:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 30 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            case 12:
                cout << "Ingrese el dia: ";
                cin >> Fecha.dia; 
                if (Fecha.dia > 31 || Fecha.dia < 1){
                    cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
                }else {
                    continuar=false;
                }
                break;
            default: 
                cout << endl << "Error! / Ha introducido una fecha invalida, intentelo nuevamente" << endl << endl;
        }

    }
    }
    cout << endl;
}

bool abisiesto(int a){
bool bisiesto;

    if (a % 400 == 0){
        bisiesto = true;
    } else if (a % 4 == 0 && a % 100 != 0){
        bisiesto = true;
    }else {
        bisiesto = false;
    }

    return bisiesto;
}

void mostrarFecha(fecha Fecha){
        if (Fecha.year<10) cout << 0;
        cout << Fecha.year << "/";
        if (Fecha.mes<10) cout << 0;
        cout << Fecha.mes << "/";
        if (Fecha.dia<10) cout << 0;
        cout << Fecha.dia;
}

bool compFechas(reporte a, reporte b){
    bool comparacion=false;

    if(a.Fecha.year>b.Fecha.year){
        comparacion=true;
    }else if(a.Fecha.year==b.Fecha.year){
        if(a.Fecha.mes>b.Fecha.mes){
            comparacion=true;
        }else if(a.Fecha.mes==b.Fecha.mes){
            if(a.Fecha.dia>b.Fecha.dia){
                comparacion=true;
            }
        }
    }

    return comparacion;
} 