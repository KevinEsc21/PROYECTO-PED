#include <iostream>
#include "Proyecto_Funciones_y_variables.hpp"
using namespace std;

//PROTOTIPOS DE FUNCIONES

//Inicio
void inicio();

//Accesos
void administrador();
void empleado();

//Opciones principales
void atenderPedido();
void despacharPedido();
void pedidosPendientes();
void ventasDelDia();
void cierreCaja();
void editarMenu();
void menuReportes();

int main(void){
    //Llenar el menu con los primeros productos
    productosIniciales();

    inicio();

    return 0;
}

//FUNCIONES

//Inicio
void inicio(){
    int opcion;
    bool status = true;

    cout << endl << "BIENVENIDO A SIVAR PIZZA" << endl;

    while(status){
        cout << endl << " ---MENU DE ACCESO---" << endl;
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

//Accesos
void administrador(){
    string password;
    bool status=true;
    
    do{
        char opcion;
        cout << endl << "Ingrese la contrase\244a: ";
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
        cout << "4) Ventas del dia \t8) Opciones de acceso" << endl;
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
                cierreCaja();
                }
                break;
            case 6:
                editarMenu();
                break;
            case 7:
                menuReportes();
                break;
            case 8:
                opcionesDeAcceso(status);
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
                cierreCaja();
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

//Opciones principales
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

void cierreCaja(){
        reporte Reporte;
        bool continuar=true;
        cout<< endl << " --CIERRE-- " << endl;

        if(reportes.empty()){
            pedirFecha(Fecha);

            Reporte.Fecha=Fecha;
            Reporte.ventasDia=ventasDia;

            reportes.push_back(Reporte);

            cout << "Cierre de caja exitoso en el dia ";
            mostrarFecha(Fecha);
            cout << endl << "VENTA: $" << ventasDia << endl;

            ventasDia=0;
        }else{
            while(continuar){
                pedirFecha(Fecha);

                Reporte.Fecha=Fecha;
                Reporte.ventasDia=ventasDia;

                if(reportesAnteriores(Reporte)){
                    cout << "No se puede guardar un reporte con fecha anterior a ";
                    mostrarFecha(reportes.front().Fecha);
                    cout << endl << endl;
                }else{
                    reportes.push_back(Reporte);
                    sort(reportes.begin(), reportes.end(),compFechas);
                    cout << "Cierre de caja exitoso en el dia ";
                    mostrarFecha(Fecha);
                    cout << endl << "VENTA: $" << ventasDia << endl;

                    ventasDia=0;

                    continuar=false;
                }
            } 
        }
}

void editarMenu(){
    int opcion;
    bool status=true;

    while(status){
        cout << endl << " --EDITAR MENU--";
        cout << endl << "Selecciona el menu a modificar: " << endl;
        cout << "1) Comidas \t3) Regresar" << endl;
        cout << "2) Bebidas" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion; cin.ignore();

        switch(opcion){
            case 1:
                editarMenuComidas();
                break;
            case 2:
                editarMenuBebidas();
                break;
            case 3:
                status=false;
                break;
            default:
                cout << endl << "La opcion ingresada no es valida" << endl;
        }
    }
}

void menuReportes(){
    int opcion;
    bool status=true;

    while(status){
        cout << endl << " --REPORTES-- " << endl;
        cout << "1) Buscar reportes por dia \t4) Editar fecha de reporte" << endl;
        cout << "2) Buscar reportes por mes \t5) Regresar" << endl;
        cout << "3) Mostrar todos los reportes" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion; cin.ignore();

        switch(opcion){
            case 1:
                reporteDia();
                break;
            case 2:
                reporteMes();
                break;
            case 3:
                mostrarReporte(reportes);
                break;
            case 4:
                editarReporte();
                break;
            case 5:
                status=false;
                break;
            default:
                cout << endl << "La opcion ingresada no es valida" << endl;
        }
    }
}
