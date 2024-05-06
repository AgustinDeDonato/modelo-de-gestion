#ifndef VENTASCABECERA_H_INCLUDED
#define VENTASCABECERA_H_INCLUDED

class VentasCab{
private:
    int nVenta;
    int dniCliente;
    float importeTotal=0;
    int MedPago;
    FechaAuto FechaDelDia;
    bool Estado;

public:
    void Cargar();
    void Mostrar();
    void Modificar(int );

    ///sets
    void setNumVenta(int nV){
        nVenta=nV;
    }
    void setDniCliente(int dC){
        dniCliente=dC;
    }
    void setImporteTotal(float Imp){
        importeTotal=Imp;
    }

    void setMedpago(int Mdp){
        MedPago=Mdp;
    }

    void setFechaDelDia(FechaAuto f){
        FechaDelDia = f;
    }

    void setEstado(bool e){
        Estado=e;
    }

    ///gets
    int getNumVenta(){
        return nVenta;
        }

    int getDniCliente(){
        return dniCliente;
        }

    float getImporteTotal(){
        return importeTotal;
        }

    int getMedpago(){
        return MedPago;
        }

    FechaAuto getFechaDelDia(){
        return FechaDelDia;
        }

    int getEstado(){
        return Estado;
        }

        bool GrabarEnDisco();
        bool LeerDeDisco(int pos);
};

bool VentasCab::GrabarEnDisco(){
    FILE *p;
    bool escribio;
    p=fopen("ventasCab.dat", "ab");
    if(p==NULL) return false;
    escribio=fwrite(this, sizeof(VentasCab),1,p);
    fclose(p);
    return escribio;
}

bool VentasCab::LeerDeDisco(int pos){
    FILE *pVentasCab;

    pVentasCab= fopen("ventasCab.dat", "rb");

    if(pVentasCab==NULL){
    return false;
    }
    fseek(pVentasCab, pos*sizeof(VentasCab), 0);
    bool Leyo = fread(this, sizeof(VentasCab), 1, pVentasCab);

    fclose(pVentasCab);
    return Leyo;
}

void VentasCab::Modificar(int pos){

    FILE *pVentasCab;
    pVentasCab = fopen("ventasCab.dat","rb+");
    if (pVentasCab==NULL) exit(1);
    fseek(pVentasCab, sizeof *this*pos,0);
    fwrite(this, sizeof *this, 1 ,pVentasCab);
    fclose(pVentasCab);

}


///AUTONUMERICO
int ContarRegistrosVC(){
    int Posicion;
    int Tam;
    FILE *pVentasCab;

    pVentasCab=fopen("ventasCab.dat", "rb");
    if(pVentasCab==NULL){//verificacion
            pVentasCab=fopen("ventasCab.dat","ab");
            if(pVentasCab==NULL){
                cout << "no se puede abrir el archivo" << endl;
                exit(1);

        }
        Posicion=0;
        return Posicion;
        fclose(pVentasCab);
    }
    fseek(pVentasCab, 0, 2);//2(desde el final)y 0 (hasta el comienzo)
    Tam=ftell(pVentasCab);
    fclose(pVentasCab);
    Posicion=Tam/sizeof(VentasCab);//tamaño dividido el de los registros
    return Posicion;
}

void NumeroPago(int MedPago){
switch(MedPago){
      case 1:
          cout << "DEBITO" << endl;
          break;
      case 2:
          cout << "CREDITO" << endl;
          break;
      case 3:
          cout << "TRANSFERENCIA" << endl;
          break;

      default:
          cout << "LA OPCION SELECCIONADA ES INCORRECTA" << endl;
          break;
          }
}

int BuscarPorNumVentaCab(int nVenta){

VentasCab reg;
int pos=0;

FILE *pVentasCab;
pVentasCab=fopen("ventasCab.dat", "rb");

if(pVentasCab==NULL){
    return -2;
}
while(fread(&reg, sizeof reg, 1, pVentasCab)==1){
    if(reg.getNumVenta()==nVenta){
        fclose(pVentasCab);
        return pos;
    }
    pos++;
}

fclose(pVentasCab);
return -1;

}

int BuscarDniCliente(int dniCliente){

Cliente retorno;
int retDni=0;

FILE *pCliente;
pCliente=fopen("Cliente.dat", "rb");

if(pCliente==NULL){
    return -2;
}
while(fread(&retorno, sizeof retorno, 1, pCliente)==1){
    if(retorno.getDni()==dniCliente){
        fclose(pCliente);
        return retDni;
    }
    retDni++;
}

fclose(pCliente);
return -1;
}

float PrecioPreParcial(int idArticulo, int cantV){ ///INT

Habitaciones obj;
float importeV=0;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return 0;
}
while(fread(&obj, sizeof obj, 1, pHabitaculos)==1){
        if(idArticulo==obj.getIDarticulo()){
            importeV = obj.getPrecio()*cantV;
    }
 }
    fclose(pHabitaculos);
    return importeV;
}

float PrecioFinal(int MedPago, float Importe){ ///INT

float importeV=0;

switch(MedPago){
            case 1:
                importeV = Importe*1.07; ///DEBITO
                break;

            case 2:
                importeV = Importe*1.15; ///CREDITO
                break;

            case 3:
                importeV = Importe;
                break;

            default:
                break;
                }

return importeV;
}

float PrecioPracial(int MedPago, int nVenta){ ///INT

VentasDet reg;
int IDH=0;
int CVH=0;
float Importe=0;
float ImporteFinal=0;

FILE *pVentasDet;
pVentasDet=fopen("ventasDet.dat", "rb");

if(pVentasDet==NULL){
    cout << "ERROR DE CARGA" << endl;
    return 0;
}

while(fread(&reg, sizeof reg, 1, pVentasDet)==1){
    IDH=reg.getIdArticulo();
    CVH=reg.getCantVend();

if(nVenta==reg.getNumVenta()){
    float importeF = PrecioPreParcial(IDH, CVH);
    Importe+=importeF;
    ImporteFinal = PrecioFinal(MedPago, Importe);
    }
}

fclose(pVentasDet);
return ImporteFinal;
}

void VentasCab::Cargar(){

  ///bool pasaN;
  bool pasaDni;
  bool pasaPago;

  ///NRO DE VENTA
    /**
    do{
    cout << "INGRESE EL NUMERO DE VENTA: ";
    cin >> nVenta;
    int pos=BuscarPorNumVentaCab(nVenta);
    if(pos<0){
        pasaN = true;
    }
    else{
        system("cls");
        cout << "ESTE NUMERO DE VENTA YA FUE INGRESADO, INTENTE NUEVAMENTE:" << endl;
        pasaN = false;
    }
    }while(pasaN == false);
*/

    nVenta=ContarRegistrosVC()+1;
    cout << "NUMERO DE VENTA: #";
    cout << nVenta << endl;
    setNumVenta(nVenta);

  ///DNI CLIENTE
    do{
    cout << "INGRESE EL DNI DEL CLIENTE: ";
    cin >> dniCliente;
    int retDni=BuscarDniCliente(dniCliente);
    if(retDni<0){
        cout << "ESTE DNI DE CLIENTE NO EXISTE, INTENTE NUEVAMENTE" << endl;
        pasaDni = true;
    }
    else{
        pasaDni = false;
    }
    }while(pasaDni == true);

  ///MEDIO DE PAGO
    do{
    cout << "INGRESE EL MEDIO DE PAGO: " << endl;
    cout << "(1) - DEBITO              " << endl; ///7%  +
    cout << "(2) - CREDITO             " << endl; ///15% +
    cout << "(3) - TRANSFERENCIA       " << endl; ///MISMO PRECIO
    cin >> MedPago;
    if(MedPago == 1 || MedPago == 2 || MedPago == 3){
        pasaPago = true;
    }
    else{
        cout << "MEDIO DE PAGO INCORRECTO, INTENTE NUEVAMENTE" << endl;
        pasaPago = false;
    }
    }while(pasaPago==false);

    cout << "FECHA: ";
    FechaDelDia.MostrarFecha();

    Estado=true;
}

void VentasCab::Mostrar(){

  if(getEstado()==true){
        cout << "NUMERO DE VENTA: ";
        cout << nVenta << endl;
        cout << "DNI DEL CLIENTE: ";
        cout << dniCliente << endl;
        cout << "IMPORTE TOTAL DE LA VENTA: $";
        importeTotal = PrecioPracial(MedPago, nVenta);
        setImporteTotal(importeTotal);
        cout << importeTotal << endl;
        cout << "MEDIO DE PAGO: ";
        NumeroPago(MedPago);
        cout << "FECHA DE LA VENTA: ";
        FechaDelDia.MostrarFecha();
        cout << "-------------------------------" << endl;
    }


}

///CARGAR
bool CargaVentaCab(){
VentasCab reg;
reg.Cargar();

FILE *pVentasCab;

pVentasCab=fopen("ventasCab.dat", "ab");
if(pVentasCab==NULL){
    return false;
}

bool escribio;
escribio = fwrite(&reg, sizeof reg, 1, pVentasCab);
fclose(pVentasCab);

return escribio;
}

///LISTAR TODOS
bool ListarRegistroVentaCab(){

VentasCab reg;

FILE *pVentasCab;
pVentasCab=fopen("ventasCab.dat", "rb");

if(pVentasCab==NULL){
    return false;
}
while(fread(&reg, sizeof reg, 1, pVentasCab)==1){
    reg.Mostrar();
}

fclose(pVentasCab);
return true;
}

///LISTAR POR NUMERO VENTA
bool ListarRegistroPorNumeroDeVentaCab(){

VentasCab reg;
int Venta;
bool idPasa = false;

cout << "INGRESE EL NUMERO DE VENTA A BUSCAR: ";
cin >> Venta;
cout << endl;

FILE *pVentasCab;
pVentasCab=fopen("ventasCab.dat", "rb");

if(pVentasCab==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1,pVentasCab)==1){

    if(Venta==reg.getNumVenta()){
    reg.Mostrar();
    idPasa = true;
    }
}

fclose(pVentasCab);

if(idPasa==false){
    cout << "ESTE NUMERO DE VENTA NO EXISTE" << endl;
}

return true;
}

///DAR BAJA VENTA
bool DarBajaVentaCab(){
VentasCab reg;
int Venta;

cout << "INGRESE EL NUMERO DE VENTA A BUSCAR: ";
cin >> Venta;
cout << endl;

FILE *pVentasCab;
pVentasCab=fopen("ventasCab.dat", "rb+");

if(pVentasCab==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pVentasCab)==1){

    if(Venta==reg.getNumVenta()){
    reg.setEstado(false);
    fseek(pVentasCab, ftell(pVentasCab)-sizeof (VentasCab), 0);
    fwrite(&reg, sizeof reg, 1, pVentasCab);
    fseek(pVentasCab,0,2);
    cout << "SU REGISTRO A SIDO ELIMINADO" << endl;
    }
}

fclose(pVentasCab);
return true;
}

///DAR ALTA VENTA
bool DarAltaVentaCab(){
VentasCab reg;
int Venta;

cout << "INGRESE EL NUMERO DE VENTA A BUSCAR: ";
cin >> Venta;
cout << endl;

FILE *pVentasCab;
pVentasCab=fopen("ventasCab.dat", "rb+");

if(pVentasCab==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pVentasCab)==1){

    if(Venta==reg.getNumVenta()){
    reg.setEstado(true);
    fseek(pVentasCab, ftell(pVentasCab)-sizeof (VentasCab), 0);
    fwrite(&reg, sizeof reg, 1, pVentasCab);
    fseek(pVentasCab,0,2);
    cout << "SU REGISTRO A SIDO DADO DE ALTA" << endl;
    }
}

fclose(pVentasCab);
return true;
}

///MODIFICAR IMPORTE POR CADA NUEVO VENTA DETALLE
bool ModificarImporteTotal(int nVenta){

    VentasCab v;
    int pos=0;
    while(v.LeerDeDisco(pos++)){
        if(nVenta==v.getNumVenta()){
            v.setImporteTotal(PrecioPracial(v.getMedpago(),nVenta));
            v.Modificar(pos-1);
            return true;
        }
    }

  return false;
}

bool MenuVentas(){
    setlocale(LC_ALL, "spanish");
    setConsoleTitle("VIVIRE");
    AjustarVentana(120,30);
    const int ANCHO_MENU = 33;
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
      cout << "MENÚ VENTAS CABECERA";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "1. CARGAR VENTA";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. LISTAR TODOS";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "3. LISTAR POR NUMERO DE VENTA";
      locate(POSMENUX+3,POSMENUY+7);
      cout << "4. BAJA VENTA";
      locate(POSMENUX+3,POSMENUY+8);
      cout << "5. ALTA VENTA";
      locate(POSMENUX+3,POSMENUY+9);
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
        case 1: if(CargaVentaCab()==false){
                cout << "ERROR EN LA CARGA DEL ARCHIVO" << endl;
            }
            else{
                cout << "REGISTRO CARGADO CON EXITO!" << endl;
            }
                system("pause");
                break;

        case 2: ListarRegistroVentaCab();
                system("pause");
                break;

        case 3: ListarRegistroPorNumeroDeVentaCab();
                system("pause");
                break;

        case 4: DarBajaVentaCab();
                system("pause");
                break;

        case 5: DarAltaVentaCab();
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
void MenuVentas(){
int opcion;

do
    {
        system ("cls");

        cout << "      - MENU VENTAS -      " << endl;
        cout << "-------------------------------" << endl;
        cout << "1 - CARGAR VENTA            " << endl;
        cout << "2 - LISTAR TODOS        " << endl;
        cout << "3 - LISTAR POR NUMERO DE VENTA" << endl;
        cout << "4 - BAJA VENTA" << endl;
        cout << "5 - ALTA VENTA" << endl;
        cout << "-------------------------------" << endl;
        cout << "0 - VOLVER AL MENU PRINCIPAL" << endl;

        cout << "OPCION: " << endl;
        cin >> opcion;

        system("cls");

        switch(opcion)
        {
        case 1:
            if(CargaVentaCab()==false){
                cout << "ERROR EN LA CARGA DEL ARCHIVO" << endl;
            }
            else{
                cout << "REGISTRO CARGADO CON EXITO!" << endl;
            }
            system("pause");
            break;

        case 2: ListarRegistroVentaCab();
            system("pause");
            break;

        case 3: ListarRegistroPorNumeroDeVentaCab();
            system("pause");
            break;

        case 4: DarBajaVentaCab();
            system("pause");
            break;

        case 5: DarAltaVentaCab();
            system("pause");
            break;

        default:
            break;
        }

    }
    while(opcion != 0);
}
*/

#endif // VENTASCABECERA_H_INCLUDED
