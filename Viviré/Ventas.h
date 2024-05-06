#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

class Ventas{
private:
    int nVenta;
    int dniCliente;
    int idArticulo;
    float importeV;
    int cantV;
    ///int MedPago;
    Fecha fechaIncorporacion;
    bool Estado;

public:
    void Cargar();
    void Mostrar();

    ///sets
    void setNumVenta(int nV){
        nVenta=nV;
    }
    void setDniCliente(int dC){
        dniCliente=dC;
    }
    void setIdArticulo(int iD){
        idArticulo=iD;
    }
    void setImporte(float Imp){
        importeV=Imp;
    }
    void setCantVend(int cV){
        cantV=cV;
    }

    /**void setMedpago(int Mdp){
        MedPago=Mdp;
    }*/

    void setfechaIncorporacion(Fecha f){
        fechaIncorporacion = f;
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
    int getIdArticulo(){
        return idArticulo;
        }
    float getImporte(){
        return importeV;
        }
    int getCantVend(){
        return cantV;
        }

    /**int getMedpago(){
        return MedPago;
        }*/

    Fecha getfechaIncorporacion(){
        return fechaIncorporacion;
        }
    int getEstado(){
        return Estado;
        }

        bool LeerDeDisco(int pos);
};

bool Ventas::LeerDeDisco(int pos){
    FILE *pVentas;

    pVentas= fopen("ventasCab.dat", "rb");

    if(pVentas==NULL){
    return false;
    }
    fseek(pVentas, pos*sizeof(Ventas), 0);
    bool Leyo = fread(this, sizeof(Ventas), 1, pVentas);

    fclose(pVentas);
    return Leyo;
}

int BuscarPorNumVenta(int nVenta){

Ventas reg;
int pos=0;

FILE *pVentas;
pVentas=fopen("ventasCab.dat", "rb");

if(pVentas==NULL){
    return -2;
}
while(fread(&reg, sizeof reg, 1, pVentas)==1){
    if(reg.getNumVenta()==nVenta){
        fclose(pVentas);
        return pos;
    }
    pos++;
}

fclose(pVentas);
return -1;

}

int BuscarCodHabit(int idArticulo){

Habitaciones obj;
int regID=0;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return -2;
}
while(fread(&obj, sizeof obj, 1, pHabitaculos)==1){
    if(obj.getIDarticulo()==idArticulo){
        fclose(pHabitaculos);
        return regID;
    }
    regID++;
}

fclose(pHabitaculos);
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

int PrecioTotal(int idArticulo, int cantV){

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

bool CambiarStock(int cantV, int idArticulo){

Habitaciones des;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb+");

if(pHabitaculos==NULL){
    return false;
}

while(fread(&des, sizeof des, 1, pHabitaculos)==1){

    if(idArticulo==des.getIDarticulo()){
            des.setStock(des.getStock()-cantV);
            fseek(pHabitaculos, ftell(pHabitaculos)-sizeof (Habitaciones), 0);
            fwrite(&des, sizeof des, 1, pHabitaculos);
            fseek(pHabitaculos,0,2);
        }
}

fclose(pHabitaculos);
return true;
}

/*void NumeroPago(int MedPago){
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

}*/

void Ventas::Cargar(){

  bool pasaN;
  bool pasaId;
  bool pasaDni;
  bool Cantidad;
  ///bool pasaPago;

    do{
    cout << "INGRESE EL NUMERO DE VENTA: ";
    cin >> nVenta;
    int pos=BuscarPorNumVenta(nVenta);
    if(pos<0){
        pasaN = true;
    }
    else{
        system("cls");
        cout << "ESTE NUMERO DE VENTA YA FUE INGRESADO, INTENTE NUEVAMENTE:" << endl;
        pasaN = false;
    }
    }while(pasaN == false);

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

    /**cout << "IMPORTE DE LA VENTA HASTA EL MOMENTO: ";
    PrecioTotal(cantV, idArticulo);*/

        do{
    cout << "INGRESE EL ID DEL HABITACULO: ";
    cin >> idArticulo;
    int regID=BuscarCodHabit(idArticulo);
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

    /**do{
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
    */

    cout << "INGRESE LA FECHA DE LA VENTA: " << endl;
    fechaIncorporacion.Carga();
    CambiarStock(cantV, idArticulo);

    Estado=true;
}

void Ventas::Mostrar(){

  if(getEstado()==true){
        cout << "NUMERO DE VENTA: ";
        cout << nVenta << endl;
        cout << "DNI DEL CLIENTE: ";
        cout << dniCliente << endl;
        cout << "ID DEL ARTICULO: ";
        cout << idArticulo << endl;
        cout << "IMPORTE DE LA VENTA: $";
        float importeV = PrecioTotal(cantV, idArticulo);
        cout << importeV << endl;
        cout << "CANTIDAD VENDIDA: ";
        cout << cantV << endl;

        /**cout << "MEDIO DE PAGO: ";
        NumeroPago(MedPago);*/

        cout << "FECHA DE LA VENTA: ";
        fechaIncorporacion.Muestra();
        cout << "-------------------------------" << endl;
    }

}

///CARGAR
bool CargaVenta(){
Ventas reg;
reg.Cargar();

FILE *pVentas;

pVentas=fopen("ventasCab.dat", "ab");
if(pVentas==NULL){
    return false;
}

bool escribio;
escribio = fwrite(&reg, sizeof reg, 1, pVentas);
fclose(pVentas);

return escribio;
}

///LISTAR TODOS
bool ListarRegistroVenta(){

Ventas reg;

FILE *pVentas;
pVentas=fopen("ventasCab.dat", "rb");

if(pVentas==NULL){
    return false;
}
while(fread(&reg, sizeof reg, 1, pVentas)==1){
    reg.Mostrar();
}

fclose(pVentas);
return true;
}

///LISTAR POR NUMERO VENTA
bool ListarRegistroPorNumeroDeVenta(){

Ventas reg;
int Venta;
bool idPasa = false;

cout << "INGRESE EL NUMERO DE VENTA A BUSCAR: ";
cin >> Venta;
cout << endl;

FILE *pVentas;
pVentas=fopen("ventasCab.dat", "rb");

if(pVentas==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1,pVentas)==1){

    if(Venta==reg.getNumVenta()){
    reg.Mostrar();
    idPasa = true;
    }
}

fclose(pVentas);

if(idPasa==false){
    cout << "ESTE NUMERO DE VENTA NO EXISTE" << endl;
}

return true;
}

///CONTAR REGISTRO
int ContarRegistrosVentas(){
  int cantReg;
  FILE *pVentas;
  pVentas=fopen("ventasCab.dat", "rb");
  if(pVentas==NULL) return -1;
  fseek(pVentas,0,2);
  cantReg=ftell(pVentas)/sizeof(Ventas);
  fclose(pVentas);
  return cantReg;
}

///COPIA ARCHIVOS
void CopiarArchivoVentas(Ventas *pVentas, int CantVentas){
    int i;
    for(i=0;i<CantVentas;i++){
        pVentas[i].LeerDeDisco(i);
    }
}

///ORDENO ARCHIVO
void OrdenarVentas(Ventas *pVentas, int CantVentas){
    int i, j, posMin;
    Ventas aux;
    for(i=0;i<CantVentas-1;i++){
        posMin=i;
        for(j=i+1;j<CantVentas;j++){
            if(pVentas[j].getDniCliente() < pVentas[posMin].getDniCliente()){
                posMin=j;
            }
        }
        aux=pVentas[i];
        pVentas[i]=pVentas[posMin];
        pVentas[posMin]=aux;

    }
 }

///IMPRIMO
void MostrarVectorVentas(Ventas *pVentas,int CantVentas){
    int i;
    for(i=0;i<CantVentas;i++){
        pVentas[i].Mostrar();
    }
}

///LISTA ORDENADOS POR CLIENTE
void ListarRegistroVentasOrdenado(){
///Contar los registros.
    int CantVentas=ContarRegistrosVentas();
///Crear un vector mediante la asignación dinámica de memoria.
    Ventas *pVentas;
    pVentas=new Ventas[CantVentas];///o una dirección válida, o NULL
    if(pVentas==NULL){
        cout<<"ERROR DE ASIGNACION DE MEORIA";
        return;
    }

///Copiar los registros del archivo en el vector.
    CopiarArchivoVentas(pVentas, CantVentas);
///Ordeno el vector.
    OrdenarVentas(pVentas, CantVentas);
///Muestro (imprimo).
    MostrarVectorVentas(pVentas, CantVentas);
///Devolver la memoria pedida
    delete pVentas;
}

///DAR BAJA VENTA
bool DarBajaVenta(){
Ventas reg;
int Venta;

cout << "INGRESE EL NUMERO DE VENTA A BUSCAR: ";
cin >> Venta;
cout << endl;

FILE *pVentas;
pVentas=fopen("ventasCab.dat", "rb+");

if(pVentas==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pVentas)==1){

    if(Venta==reg.getNumVenta()){
    reg.setEstado(false);
    fseek(pVentas, ftell(pVentas)-sizeof (Ventas), 0);
    fwrite(&reg, sizeof reg, 1, pVentas);
    fseek(pVentas,0,2);
    cout << "SU REGISTRO A SIDO ELIMINADO" << endl;
    }
}

fclose(pVentas);
return true;
}

///DAR ALTA VENTA
bool DarAltaVenta(){
Ventas reg;
int Venta;

cout << "INGRESE EL NUMERO DE VENTA A BUSCAR: ";
cin >> Venta;
cout << endl;

FILE *pVentas;
pVentas=fopen("ventasCab.dat", "rb+");

if(pVentas==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pVentas)==1){

    if(Venta==reg.getNumVenta()){
    reg.setEstado(true);
    fseek(pVentas, ftell(pVentas)-sizeof (Ventas), 0);
    fwrite(&reg, sizeof reg, 1, pVentas);
    fseek(pVentas,0,2);
    cout << "SU REGISTRO A SIDO ELIMINADO" << endl;
    }
}

fclose(pVentas);
return true;
}

///OPCIONES LISTAR
void ListarV(){
int Op;

cout << "SELECCIONAR LA FORMA PARA LISTAR:      " << endl;
cout << "---------------------------------------" << endl;
cout << "(1) MOSTRAR VENTAS CARGADAS          " << endl;
cout << "(2) MOSTRAR VENTAS POR NUMERO DE VENTA           " << endl;
cout << "(3) MOSTRAR VENTAS ORDENADAS POR CLIENTE " << endl;
cout << "---------------------------------------" << endl;
cout << "OPCION: ";
cin >> Op;
system("cls");

switch(Op){
case 1: ListarRegistroVenta();
    break;
case 2: ListarRegistroPorNumeroDeVenta();
    break;
case 3: ListarRegistroVentasOrdenado();
    break;

default:
    break;
}
}

///OPCIONES DE MODIFICACION
void ModificarV(){
int Op;

cout << "SELECCIONAR MODIFICACION: " << endl;
cout << "--------------------------" << endl;
cout << "(1) DAR DE BAJA           " << endl;
cout << "(2) DAR DE ALTA           " << endl;
cout << "--------------------------" << endl;
cout << "OPCION: ";
cin >> Op;
system("cls");

switch(Op){
case 1: DarBajaVenta();
    break;
case 2: DarAltaVenta();
    break;

default:
    break;
}
}

void MenuVentas(){
int opcion;

do
    {
        system ("cls");

        cout << "      - MENU VENTAS -      " << endl;
        cout << "-------------------------------" << endl;
        cout << "1 - CARGAR VENTA            " << endl;
        cout << "2 - MOSTRAR (LISTAR)        " << endl;
        cout << "3 - MODIFICAR DATOS CARGADOS" << endl;
        cout << "4 - VENTAS DETALLE" << endl;
        cout << "-------------------------------" << endl;
        cout << "0 - VOLVER AL MENU PRINCIPAL" << endl;

        cout << "OPCION: " << endl;
        cin >> opcion;

        system("cls");

        switch(opcion)
        {
        case 1:
            if(CargaVenta()==false){
                cout << "ERROR EN LA CARGA DEL ARCHIVO" << endl;
            }
            else{
                cout << "REGISTRO CARGADO CON EXITO!" << endl;
            }
            system("pause");
            break;

        case 2: ListarV();
            system("pause");
            break;

        case 3: ModificarV();
            system("pause");
            break;

        default:
            break;
        }

    }
    while(opcion != 0);
}

#endif // VENTAS_H_INCLUDED
