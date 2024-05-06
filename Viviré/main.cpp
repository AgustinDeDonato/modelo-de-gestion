#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "rlutil.h"

using namespace std;
using namespace rlutil;

const int POSMENUX = 33;
const int POSMENUY = 3;
const int LETRA = WHITE;
const int FONDO = BLUE;

#include "Herramientas.h"
#include "Fecha.h"
#include "FechaAuto.h"
#include "Habitaciones.h"
#include "Clientes.h"
#include "VentasDetalle.h"
#include "VentasCabecera.h"
#include "Factura.h"
#include "Configuracion.h"
#include "Reportes.h"

bool Ventas(){
    setlocale(LC_ALL, "spanish");
    setConsoleTitle("VIVIRE");
    AjustarVentana(120,30);
    const int ANCHO_MENU = 26;
    const int ALTO_MENU = 8;
    int key, opc, cursorX, cursorY;

    while(true){
      cursorX=POSMENUX+1;
      cursorY=POSMENUY + 4;
      setBackgroundColor(FONDO);
      cls();
      opc=1;
      setColor(LETRA);
      setBackgroundColor(FONDO);
      recuadro(POSMENUX,POSMENUY, ANCHO_MENU,ALTO_MENU,LETRA,FONDO);
      separadorH(POSMENUX,POSMENUY+2,ANCHO_MENU,LETRA,FONDO);
      locate(POSMENUX+5,POSMENUY+1);
      cout << "MENÚ VENTAS";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "1. VENTAS CABECERA";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. VENTAS DETALLE";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "3. FACTURACION";
      locate(POSMENUX+3,POSMENUY+7);
      cout << "0. VOLVER AL MENU";
      locate(POSMENUX+2,POSMENUY+3);
      cout << " SELECCIONE UNA OPCION: ";
      hidecursor();

      locate(cursorX,cursorY);
      cout<<">";
      key = getkey();
      while(key != KEY_ENTER){
        locate(cursorX,cursorY);
        cout<<" ";
        switch(key){
        case KEY_DOWN:
            if(opc < 3){
                opc++;
            }else{
                opc=0;
            }
            break;
        case KEY_UP:
            if(opc > 0){
                opc--;
            }else{
                opc=3;
            }
            break;
        }
        if(opc != 0){
            cursorY = opc + POSMENUY + 3;
        }else{
            cursorY = POSMENUY + 7;
        }
        locate(cursorX,cursorY);
        cout<<">";
        key = getkey();
      }
      setBackgroundColor(BLUE);
      cls();
      showcursor();
      switch(opc){
        case 1: MenuVentas();
                break;
        case 2: MenuVentasDetalle();
                break;
        case 3: Facturacion();
                break;

        case 0: return false;
                break;

        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }

}


int main(){
    setlocale(LC_ALL, "spanish");
    setConsoleTitle("VIVIRE");
    AjustarVentana(120,30);
    const int ANCHO_MENU = 26;
    const int ALTO_MENU = 10;
    int key, opc, cursorX, cursorY;

    while(true){
      cursorX=POSMENUX+1 ;
      cursorY=POSMENUY + 4;
      setBackgroundColor(FONDO);
      cls();
      opc=1;
      setColor(LETRA);
      setBackgroundColor(FONDO);
      recuadro(POSMENUX,POSMENUY, ANCHO_MENU,ALTO_MENU,LETRA,FONDO);
      separadorH(POSMENUX,POSMENUY+2,ANCHO_MENU,LETRA,FONDO);
      locate(POSMENUX+5,POSMENUY+1);
      cout << "MENÚ PRINCIPAL";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "1. MENU HABITACIONES";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. CLIENTES";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "3. VENTAS";
      locate(POSMENUX+3,POSMENUY+7);
      cout << "4. CONFIGURACION";
      locate(POSMENUX+3,POSMENUY+8);
      cout << "5. REPORTES";
      locate(POSMENUX+3,POSMENUY+9);
      cout << "0. FIN DEL PROGRAMA";
      locate(POSMENUX+2,POSMENUY+3);
      cout << " SELECCIONE UNA OPCION: ";
      hidecursor();

      locate(cursorX,cursorY);
      cout<<">";
      key = getkey();
      while(key != KEY_ENTER){
        locate(cursorX,cursorY);
        cout<<" ";
        switch(key){
        case KEY_DOWN:
            if(opc < 5){
                opc++;
            }else{
                opc=0;
            }
            break;
        case KEY_UP:
            if(opc > 0){
                opc--;
            }else{
                opc=5;
            }
            break;
        }
        if(opc != 0){
            cursorY = opc + POSMENUY + 3;
        }else{
            cursorY = POSMENUY + 9;
        }
        locate(cursorX,cursorY);
        cout<<">";
        key = getkey();
      }
      setBackgroundColor(BLUE);
      cls();
      showcursor();
      switch(opc){
        case 1: MenuHabitaciones();
                break;
        case 2: MenuCliente();
                break;
        case 3: Ventas();
                break;
        case 4: MenuConfig();
                break;
        case 5: MenuReportes();
                break;

        case 0: return 0;
                break;

        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }

}


/*
void Ventas(){

int opcion;

do
    {
        system ("cls");

        cout << "   - MENU VENTAS -   " << endl;
        cout << "---------------------" << endl;
        cout << "1 - VENTAS CABECERA" << endl;
        cout << "2 - VENTAS DETALLE" << endl;
        cout << "3 - FACTURACION" << endl;
        cout << "---------------------" << endl;
        cout << "0 - SALIR" << endl;

        cout << "OPCION: " << endl;

        cin >> opcion;
        system("cls");

        switch(opcion)
        {
        case 1: MenuVentas();
            break;

        case 2: MenuVentasDetalle();
            break;

        case 3: Facturacion();
            break;

        default:
            break;
        }

    }
    while(opcion != 0);

}

int main(){
int opcion;

do
    {
        system ("cls");

        cout << "  - MENU PRINCIPAL -  " << endl;
        cout << "---------------------" << endl;
        cout << "1 - MENU HABITACIONES" << endl;
        cout << "2 - MENU CLIENTES" << endl;
        cout << "3 - MENU VENTAS" << endl;
        cout << "4 - CONFIGURACION" << endl;
        cout << "5 - REPORTES" << endl;
        cout << "4 - VENTAS DETALLE" << endl;
        cout << "5 - FACTURACION" << endl;
        cout << "---------------------" << endl;
        cout << "0 - SALIR" << endl;

        cout << "OPCION: " << endl;

        cin >> opcion;
        system("cls");

        switch(opcion)
        {
        case 1: MenuHabitaciones();
            break;

        case 2: MenuCliente();
            break;

        case 3: Ventas();
            break;

        case 4: MenuConfig();
            break;

        case 5: MenuReportes();
            break;

        ///case 3: MenuVentas();
           ///break;

        ///case 4: MenuVentasDetalle();
           ///break;

        ///case 5: Facturacion();
           ///break;

        default:
            break;
        }

    }
    while(opcion != 0);

    return 0;

}
*/
