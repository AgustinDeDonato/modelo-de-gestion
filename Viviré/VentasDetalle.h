#ifndef VENTASDETALLE_H_INCLUDED
#define VENTASDETALLE_H_INCLUDED

class VentasDet{
private:
    int nVentaDetalle;
    int idHabitaculo;
    int cantV;
    float ImporteSubTotal;
    bool Estado;

public:
    void Cargar();
    void Mostrar();

    ///sets
    void setNumVenta(int nV){
        nVentaDetalle=nV;
    }

    void setIdArticulo(int iD){
        idHabitaculo=iD;
    }

    void setCantVend(int cV){
        cantV=cV;
    }

    void setImporteSubTotal(float It){
        ImporteSubTotal=It;
    }

    void setEstado(bool e){
        Estado=e;
    }

    ///gets
    int getNumVenta(){
        return nVentaDetalle;
        }

    int getIdArticulo(){
        return idHabitaculo;
        }

    int getCantVend(){
        return cantV;
        }

    float getImporteSubTotal(){
        return ImporteSubTotal;
        }

    int getEstado(){
        return Estado;
        }

        bool GrabarEnDisco();
        bool LeerDeDisco(int pos);
};

bool VentasDet::GrabarEnDisco(){
    FILE *p;
    bool escribio;
    p=fopen("ventasDet.dat", "ab");
    if(p==NULL) return false;
    escribio=fwrite(this, sizeof(VentasDet),1,p);
    fclose(p);
    return escribio;
}


bool VentasDet::LeerDeDisco(int pos){
    FILE *pVentasDet;

    pVentasDet= fopen("ventasDet.dat", "rb");

    if(pVentasDet==NULL){
    return false;
    }
    fseek(pVentasDet, pos*sizeof(VentasDet), 0);
    bool Leyo = fread(this, sizeof(VentasDet), 1, pVentasDet);

    fclose(pVentasDet);
    return Leyo;
}

int ContarRegistrosVD(){
    int Posicion;
    int Tam;
    FILE *pVentasDet;

    pVentasDet=fopen("ventasDet.dat", "rb");
    if(pVentasDet==NULL){//verificacion
            pVentasDet=fopen("ventasDet.dat","ab");
            if(pVentasDet==NULL){
                cout << "no se puede abrir el archivo" << endl;
                exit(1);

        }
        Posicion=0;
        return Posicion;
        fclose(pVentasDet);
    }
    fseek(pVentasDet, 0, 2);//2(desde el final)y 0 (hasta el comienzo)
    Tam=ftell(pVentasDet);
    fclose(pVentasDet);
    Posicion=Tam/sizeof(VentasDet);//tamaño dividido el de los registros
    return Posicion;
}

int BuscarCodHabit(int idHabitaculo){

Habitaciones obj;
int regID=0;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return -2;
}
while(fread(&obj, sizeof obj, 1, pHabitaculos)==1){
    if(obj.getIDarticulo()==idHabitaculo){
        fclose(pHabitaculos);
        return regID;
    }
    regID++;
}

fclose(pHabitaculos);
return -1;

}

int ValidarCantidad(int cantV){

Habitaciones obj;
int Vc=0;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return -2;
}
while(fread(&obj, sizeof obj, 1, pHabitaculos)==1){
    if(cantV>0 && cantV<=obj.getStock()){
        fclose(pHabitaculos);
        return Vc;
    }
    Vc++;
}

fclose(pHabitaculos);
return -1;
}

bool CambiarStock(int cantV, int idHabitaculo){

Habitaciones des;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb+");

if(pHabitaculos==NULL){
    return false;
}

while(fread(&des, sizeof des, 1, pHabitaculos)==1){

    if(idHabitaculo==des.getIDarticulo()){
            des.setStock(des.getStock()-cantV);
            fseek(pHabitaculos, ftell(pHabitaculos)-sizeof (Habitaciones), 0);
            fwrite(&des, sizeof des, 1, pHabitaculos);
            fseek(pHabitaculos,0,2);
        }
}

fclose(pHabitaculos);
return true;
}

int Subtotal(int cantV, int idHabitaculo){

Habitaciones obj;
float importeT=0;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return 0;
}
while(fread(&obj, sizeof obj, 1, pHabitaculos)==1){
        if(idHabitaculo==obj.getIDarticulo()){
            importeT = obj.getPrecio()*cantV;
    }
 }
    fclose(pHabitaculos);
    return importeT;
}

/*
void verDesc(int idHabitaculo){

Habitaciones reg;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    cout << "ERROR DE CARGA" << endl;
    return;
}

while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){
        if(reg.getIDarticulo()==idHabitaculo){
            cout << reg.getDescripcion();
        }
}

fclose(pHabitaculos);
}
*/
void VentasDet::Cargar(){

  bool pasaId;
  bool Cantidad;

    cout << "INGRESE EL NUMERO DE VENTA: ";
    cin >> nVentaDetalle;

    /*
    nVentaDetalle=ContarRegistrosVD()+1;
    cout << "NUMERO DE VENTA: #";
    cout << nVentaDetalle << endl;
    setNumVenta(nVentaDetalle);
    */

        do{
    cout << "INGRESE EL ID DEL HABITACULO: ";
    cin >> idHabitaculo;
    int regID=BuscarCodHabit(idHabitaculo);
    if(regID<0){
        cout << "ESTE ID DE ARTICULO NO EXISTE, INTENTE NUEVAMENTE" << endl;
        pasaId = true;
    }
    else{
        pasaId = false;
    }
    }while(pasaId == true);

    do{
    cout << "INGRESE LA CANTIDAD A ADQUIRIR: ";
    cin >> cantV;
    int Vc=ValidarCantidad(cantV);
        if(Vc<0){
        cout << "LA CANTIDAD QUE USTED DESEA ADQUIRIR ES MENOR A 0(CERO) O SUPERA EL STOCK, INTENTE NUEVAMENTE" << endl;
        Cantidad = true;
    }
    else{
        Cantidad = false;
    }
    }while(Cantidad == true);

    ImporteSubTotal = Subtotal(cantV, idHabitaculo);
    setImporteSubTotal(ImporteSubTotal);

    CambiarStock(cantV, idHabitaculo);

    Estado=true;
}

void VentasDet::Mostrar(){
 if(getEstado()==true){

        cout << "NUMERO DE VENTA: ";
        cout << nVentaDetalle << endl;
        cout << "ID DEL ARTICULO: ";
        cout << idHabitaculo << endl;
        cout << "CANTIDAD VENDIDA: ";
        cout << cantV << endl;
        cout << "SUBTOTAL: $";
        cout << ImporteSubTotal << endl;
        cout << "-------------------------------" << endl;
    }
}

///CARGAR
#include "VentasCabecera.h"
bool CargaVentaDet(){
VentasDet reg;
reg.Cargar();

FILE *pVentasDet;

pVentasDet=fopen("ventasDet.dat", "ab");
if(pVentasDet==NULL){
    return false;
}

bool escribio;
escribio = fwrite(&reg, sizeof reg, 1, pVentasDet);
fclose(pVentasDet);

if (escribio){
    ModificarImporteTotal(reg.getNumVenta());
}

return escribio;
}

///CARGA V2
bool CargaVentaDetV2(){
char op;

do{
    CargaVentaDet();

    cout << "DESEA CARGAR OTRO ARTICULO? (s/n)" << endl;
    cin >> op;
}while(op!='n');

return true;
}

///LISTAR TODOS
bool ListarRegistroVentaDet(){

VentasDet reg;

FILE *pVentasDet;
pVentasDet=fopen("ventasDet.dat", "rb");

if(pVentasDet==NULL){
    return false;
}

cout << "NUMERO DE VENTA \tARTICULO \t CANTIDAD VENDIDA \t SUBTOTAL" << endl;

while(fread(&reg, sizeof reg, 1, pVentasDet)==1){
    reg.Mostrar();
}

fclose(pVentasDet);
return true;
}

bool MenuVentasDetalle(){
    setlocale(LC_ALL, "spanish");
    setConsoleTitle("VIVIRE");
    AjustarVentana(120,30);
    const int ANCHO_MENU = 26;
    const int ALTO_MENU = 7;
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
      cout << "MENU VENTA DETALLE";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "1. CARGAR VENTA";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. MOSTRAR (LISTAR)";
      locate(POSMENUX+3,POSMENUY+6);
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
            if(opc < 2){
                opc++;
            }else{
                opc=0;
            }
            break;
        case KEY_UP:
            if(opc > 0){
                opc--;
            }else{
                opc=2;
            }
            break;
        }
        if(opc != 0){
            cursorY = opc + POSMENUY + 3;
        }else{
            cursorY = POSMENUY + 6;
        }
        locate(cursorX,cursorY);
        cout<<">";
        key = getkey();
      }
      setBackgroundColor(BLUE);
      cls();
      showcursor();
      switch(opc){
            case 1:
            if(CargaVentaDetV2()==false){
                cout << "ERROR EN LA CARGA DEL ARCHIVO" << endl;
            }
            else{
                cout << "REGISTRO CARGADO CON EXITO!" << endl;
            }
            system("pause");
            break;

        case 2: ListarRegistroVentaDet();
            system("pause");
            break;

        case 0: return false;
                break;

        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }

}

/*
void MenuVentasDetalle(){
int opcion;

do
    {
        system ("cls");

        cout << "   - MENU VENTA DETALLE -      " << endl;
        cout << "-------------------------------" << endl;
        cout << "1 - CARGAR VENTA            " << endl;
        cout << "2 - MOSTRAR (LISTAR)        " << endl;

        ///cout << "3 - MODIFICAR DATOS CARGADOS" << endl;
        ///cout << "4 - VENTAS DETALLE" << endl;

        cout << "-------------------------------" << endl;
        cout << "0 - VOLVER AL MENU PRINCIPAL" << endl;

        cout << "OPCION: " << endl;
        cin >> opcion;

        system("cls");

        switch(opcion)
        {
        case 1:
            if(CargaVentaDetV2()==false){
                cout << "ERROR EN LA CARGA DEL ARCHIVO" << endl;
            }
            else{
                cout << "REGISTRO CARGADO CON EXITO!" << endl;
            }
            system("pause");
            break;

        case 2: ListarRegistroVentaDet();
            system("pause");
            break;

        default:
            break;
        }

    }
    while(opcion != 0);
}
*/
#endif // VENTASDETALLE_H_INCLUDED
