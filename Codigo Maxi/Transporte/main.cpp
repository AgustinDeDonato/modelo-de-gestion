#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "rlutil.h"

using namespace std;
using namespace rlutil;

const char *ARCHIVO_VIAJES="viajes.dat";
const char *ARCHIVO_EMPRESAS="empresas.dat";
const int POSMENUX = 33;
const int POSMENUY = 3;
const int COLOR_PANTALLA = DARKGREY;
const int LETRA = WHITE;
const int FONDO = BLUE;

#include "utilidades.h"
#include "tipos.h"
#include "prototipos.h"
#include "funciones.h"
#include "funciones_empresas.h"
#include "funciones_viajes.h"


int main(){
    setlocale(LC_ALL, "spanish");
    setConsoleTitle("Probando rlutil");
    AjustarVentana(89,30);
    const int ANCHO_MENU = 23;
    const int ALTO_MENU = 8;
    int key, opc, cursorX, cursorY;
    while(true){
      cursorX=POSMENUX+1;
      cursorY=POSMENUY + 3;
      setBackgroundColor(COLOR_PANTALLA);
      cls();
      opc=1;
      setColor(LETRA);
      setBackgroundColor(FONDO);
      recuadro(POSMENUX,POSMENUY, ANCHO_MENU,ALTO_MENU,LETRA,FONDO);
      separadorH(POSMENUX,POSMENUY+2,ANCHO_MENU,LETRA,FONDO);
      locate(POSMENUX+5,POSMENUY+1);
      cout << "MENÚ PRINCIPAL";
      locate(POSMENUX+3,POSMENUY+3);
      cout << "1. EMPRESAS";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "2. VIAJES";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "3. REPORTES";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "4. CONFIGURACION";
      locate(POSMENUX+3,POSMENUY+7);
      cout << "0. FIN DEL PROGRAMA";
      locate(POSMENUX,POSMENUY+ALTO_MENU+1);
      cout << " SELECCIONE UNA OPCION: ";
      hidecursor();
      //cin>>opc;
      locate(cursorX,cursorY);
      cout<<">";
      key = getkey();
      while(key != KEY_ENTER){
        locate(cursorX,cursorY);
        cout<<" ";
        switch(key){
        case KEY_DOWN:
            if(opc < 4){
                opc++;
            }else{
                opc=0;
            }
            break;
        case KEY_UP:
            if(opc > 0){
                opc--;
            }else{
                opc=4;
            }
            break;
        }
        if(opc != 0){
            cursorY = opc + POSMENUY + 2;
        }else{
            cursorY = POSMENUY + 7;
        }
        locate(cursorX,cursorY);
        cout<<">";
        key = getkey();
      }
      setBackgroundColor(COLOR_PANTALLA);
      cls();
      showcursor();
      switch(opc){
        case 1: menuEmpresas();
                break;
        case 2: menuViajes();
                break;
        case 3: menuReportes();
                break;
        case 0: return 0;
                break;
        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }
    return 0;
}
