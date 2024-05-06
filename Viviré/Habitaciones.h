#ifndef HABITACIONES_H_INCLUDED
#define HABITACIONES_H_INCLUDED

///CLASE HABITACIONES
class Habitaciones{

private:
    int IDarticulo;
    char Descripcion[30];
    float Precio;
    int Stock;
    bool Estado;

public:
    void Cargar();
    void Mostrar();

    ///sets
    void setIDarticulo(int ID){
        IDarticulo=ID;
    }
    void setDescripcion(char *d){
        strcpy(Descripcion,d);
    }
    void setPrecio(float p){
        Precio=p;
    }
    void setStock(int s){
        Stock=s;
    }
    void setEstado(bool e){
        Estado=e;
    }

    ///gets
    int getIDarticulo(){
        return IDarticulo;
    }
    const char * getDescripcion(){
        return Descripcion;
    }
    float getPrecio(){
        return Precio;
    }
    int getStock(){
        return Stock;
    }
    int getEstado(){
        return Estado;
    }

    bool GrabarEnDisco();
    bool LeerDeDisco(int pos);
};

/**
bool Habitaciones::GrabarEnDisco(){
    FILE *pHabitaculos;

    pHabitaculos=fopen("Habitaciones.dat", "ab");
    if(pHabitaculos==NULL){
            return false;
    }

    bool Escribio=fwrite(this,sizeof(Habitaciones),1,pHabitaculos);

    fclose(pHabitaculos);
    return Escribio;
}
*/

bool Habitaciones::GrabarEnDisco(){
    FILE *p;
    bool escribio;
    p=fopen("Habitaciones.dat", "ab");
    if(p==NULL) return false;
    escribio=fwrite(this, sizeof(Habitaciones),1,p);
    fclose(p);
    return escribio;
}


bool Habitaciones::LeerDeDisco(int pos){
    FILE *pHabitaculos;

    pHabitaculos = fopen("Habitaciones.dat", "rb");

    if(pHabitaculos==NULL){
    return false;
    }
    fseek(pHabitaculos, pos*sizeof(Habitaciones), 0);
    bool Leyo = fread(this, sizeof(Habitaciones), 1, pHabitaculos);

    fclose(pHabitaculos);
    return Leyo;
}

///BUSCA POR ID
/**
int BuscarPorCodigo(int IDarticulo){

Habitaciones reg;
int pos=0;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return -2;
}
while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){
    if(reg.getIDarticulo()==IDarticulo){
        fclose(pHabitaculos);
        return pos;
    }
    pos++;
}

fclose(pHabitaculos);
return -1;
}
*/

///AUTONUMERICO
int ContarRegistrosHB(){
    int Posicion;
    int Tam;
    FILE *pHabitaculos;

    pHabitaculos=fopen("Habitaciones.dat", "rb");
    if(pHabitaculos==NULL){//verificacion
            pHabitaculos=fopen("Habitaciones.dat","ab");
            if(pHabitaculos==NULL){
                cout << "no se puede abrir el archivo" << endl;
                exit(1);

        }
        Posicion=0;
        return Posicion;
        fclose(pHabitaculos);
    }
    fseek(pHabitaculos, 0, 2);//2(desde el final)y 0 (hasta el comienzo)
    Tam=ftell(pHabitaculos);
    fclose(pHabitaculos);
    Posicion=Tam/sizeof(Habitaciones);//tamaño dividido el de los registros
    return Posicion;
}

void Habitaciones::Cargar(){
    bool pasa;
    ///bool pasaCodigo;

    /**
    do{
    cout << "INGRESE EL ID DEL HABITACULO: ";
    cin >> IDarticulo;
    int pos=BuscarPorCodigo(IDarticulo);
    if(pos<0){
        pasaCodigo = true;
    }
    else{
        system("cls");
        cout << "ESTE CODIGO YA FUE INGRESADO, INTENTE NUEVAMENTE" << endl;
        pasaCodigo = false;
    }
    }while(pasaCodigo == false);
    */

    IDarticulo=ContarRegistrosHB()+1;
    cout << "ID DE ARTICULO: #";
    cout << IDarticulo << endl;
    setIDarticulo(IDarticulo);

    cout << "INGRESE LA DESCRIPCION: ";
    cin >> Descripcion;
    do{
    cout << "INGRESE EL PRECIO: " << "$";
    cin >> Precio;
    if(Precio>0){
            pasa=true;
    }
    else{
    cout << "EL PRECIO ES MENOR QUE CERO (0), VUELVA A INGRESAR EL PRECIO" << endl;
    pasa=false;
    }

    }while(pasa==false);

    cout << "INGRESE EL STOCK: ";
    cin >> Stock;

    Estado=true;
}

void Habitaciones::Mostrar(){
    if(getEstado()==true){
    cout << "ID DEL HABITACULO: ";
    cout << IDarticulo << endl;
    cout << "DESCRIPCION: ";
    cout << Descripcion << endl;
    cout << "PRECIO: " << "$";
    cout << Precio << endl;
    cout << "STOCK: ";
    cout << Stock << endl;
    cout << "-------------------------------" << endl;
    }
}

///CARGA
bool CargarHabitaculos(){
Habitaciones reg;
reg.Cargar();

FILE *pHabitaculos;

pHabitaculos=fopen("Habitaciones.dat", "ab");
if(pHabitaculos==NULL){
    return false;
}

bool Escribio;
Escribio = fwrite(&reg, sizeof reg, 1, pHabitaculos);
fclose(pHabitaculos);

return Escribio;
}

///LISTA TODOS
bool ListarRegistros(){
Habitaciones reg;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return false;
}
while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){
    reg.Mostrar();
}

fclose(pHabitaculos);
return true;
}

///BUSCA Y LISTA POR ID
bool ListarRegistrosPorID(){
Habitaciones reg;
int ID;
bool idPasa = false;

cout << "INGRESE EL ID DE ARTICULO A BUSCAR: ";
cin >> ID;
cout << endl;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return false;
}

while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){

    if(ID==reg.getIDarticulo()){
    reg.Mostrar();
    idPasa = true;
    }
}

fclose(pHabitaculos);

if(idPasa==false){
    cout << "ESTE ID DE ARTICULO NO EXISTE" << endl;
}

return true;
}

///CONTAR REGISTRO
int ContarRegistrosHabitaculos(){
  int cantReg;
  FILE *pHabitaculos;
  pHabitaculos=fopen("Habitaciones.dat", "rb");
  if(pHabitaculos==NULL) return -1;
  fseek(pHabitaculos,0,2);
  cantReg=ftell(pHabitaculos)/sizeof(Habitaciones);///divide el total de archivos en bytes por el total de archivos en clase
  fclose(pHabitaculos);
  return cantReg;///Retorna la cantidad de registros
}

///COPIA ARCHIVOS
void CopiarArchivoHabitaculos(Habitaciones *pHabitaculos, int cantHabit){
    int i;
    for(i=0;i<cantHabit;i++){
        pHabitaculos[i].LeerDeDisco(i);
    }
}

///ORDENO ARCHIVO
void OrdenarHabitaculos(Habitaciones *pHabitaculos, int cantHabit){
    int i, j, posMin;
    Habitaciones aux;
    for(i=0;i<cantHabit-1;i++){
        posMin=i;
        for(j=i+1;j<cantHabit;j++){
            if(pHabitaculos[j].getIDarticulo() < pHabitaculos[posMin].getIDarticulo()){
                posMin=j;
            }
        }
        aux=pHabitaculos[i];
        pHabitaculos[i]=pHabitaculos[posMin];
        pHabitaculos[posMin]=aux;

    }
 }

///IMPRIMO
void MostrarVectorHabitaculos(Habitaciones *pHabitaculos,int cantHabit){
    int i;
    for(i=0;i<cantHabit;i++){
        pHabitaculos[i].Mostrar();
    }
}

///LISTA ORDENADOS - A +
void ListarRegistrosOrdenadosMM(){
///Contar los registros.
    int cantHabit=ContarRegistrosHabitaculos();
///Crear un vector mediante la asignación dinámica de memoria.
    Habitaciones *pHabitaculos;
    pHabitaculos=new Habitaciones[cantHabit];///o una dirección válida, o NULL
    if(pHabitaculos==NULL){
        cout<<"ERROR DE ASIGNACION DE MEORIA";
        return;
    }

///Copiar los registros del archivo en el vector.
    CopiarArchivoHabitaculos(pHabitaculos, cantHabit);
///Ordeno el vector.
    OrdenarHabitaculos(pHabitaculos, cantHabit);
///Muestro (imprimo).
    MostrarVectorHabitaculos(pHabitaculos, cantHabit);
///Devolver la memoria pedida
    delete pHabitaculos;
}

///CAMBIAR PRECIO
bool CambiarPrecio(){

Habitaciones reg;
int ID;
float pR;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb+");

cout << "INGRESE EL ID DEL HABITACULO A BUSCAR: ";
cin >> ID;
cout << endl;
cout << "INGRESE EL PRECIO DEL HABITACULO A MODIFICAR: ";
cin >> pR;
cout << endl;

if(pHabitaculos==NULL){
    return false;
}

while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){

    if(ID==reg.getIDarticulo()){
            reg.setPrecio(pR);
            fseek(pHabitaculos, ftell(pHabitaculos)-sizeof (Habitaciones), 0);
            fwrite(&reg, sizeof reg, 1, pHabitaculos);
            fseek(pHabitaculos,0,2);
            cout << "SU REGISTRO A SIDO MODIFICADO CON EXITO" << endl;
        }
}

fclose(pHabitaculos);
return true;
}

///CAMBIAR STOCK
bool CambiarStock(){

Habitaciones reg;
int ID;
int St;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb+");

cout << "INGRESE EL ID DE HABITACULO A BUSCAR: ";
cin >> ID;
cout << endl;
cout << "INGRESE EL STOCK DEL HABITACULO A MODIFICAR: ";
cin >> St;
cout << endl;

if(pHabitaculos==NULL){
    return false;
}

while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){

    if(ID==reg.getIDarticulo()){
            reg.setStock(St);
            fseek(pHabitaculos, ftell(pHabitaculos)-sizeof (Habitaciones), 0);
            fwrite(&reg, sizeof reg, 1, pHabitaculos);
            fseek(pHabitaculos,0,2);
            cout << "SU REGISTRO A SIDO MODIFICADO CON EXITO" << endl;
        }
}

fclose(pHabitaculos);
return true;
}

///BAJA LOGICA
bool DarBajaHB(){

Habitaciones reg;
int ID;

cout << "INGRESE EL ID DE ARTICULO A BUSCAR: ";
cin >> ID;
cout << endl;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb+");

if(pHabitaculos==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){

    if(ID==reg.getIDarticulo()){
    reg.setEstado(false);
    fseek(pHabitaculos, ftell(pHabitaculos)-sizeof (Habitaciones), 0);
    fwrite(&reg, sizeof reg, 1, pHabitaculos);
    fseek(pHabitaculos,0,2);
    cout << "SU REGISTRO A SIDO ELIMINADO" << endl;
    }
}

fclose(pHabitaculos);
return true;
}

///ALTA LOGICA
bool DarAltaHB(){

Habitaciones reg;
int ID;

cout << "INGRESE EL ID DE ARTICULO A BUSCAR: ";
cin >> ID;
cout << endl;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb+");

if(pHabitaculos==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){

    if(ID==reg.getIDarticulo()){
    reg.setEstado(true);
    fseek(pHabitaculos, ftell(pHabitaculos)-sizeof (Habitaciones), 0);
    fwrite(&reg, sizeof reg, 1, pHabitaculos);
    fseek(pHabitaculos,0,2);
    cout << "SU REGISTRO A SIDO DADO DE ALTA" << endl;
    }
}

fclose(pHabitaculos);
return true;
}

///OPCIONES LISTAR
bool ListarHB(){
    setlocale(LC_ALL, "spanish");
    setConsoleTitle("VIVIRE");
    AjustarVentana(120,30);
    const int ANCHO_MENU = 34;
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
      cout << "FORMAS PARA LISTAR";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "1. MOSTRAR HB CARGADOS";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. MOSTRAR HB POR ID";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "3. MOSTRAR HB ORDENADOS POR ID";
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
        case 1: ListarRegistros();
                system("pause");
                break;

        case 2: ListarRegistrosPorID();
                system("pause");
                break;

        case 3: ListarRegistrosOrdenadosMM();
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
void ListarHB(){
int Op;

cout << "SELECCIONAR LA FORMA PARA LISTAR: " << endl;
cout << "----------------------------------" << endl;
cout << "(1) MOSTRAR HB CARGADOS           " << endl;
cout << "(2) MOSTRAR HB POR ID             " << endl;
cout << "(3) MOSTRAR HB ORDENADOS POR ID   " << endl;
cout << "----------------------------------" << endl;
cout << "OPCION: ";
cin >> Op;
system("cls");

switch(Op){
case 1: ListarRegistros();
    break;
case 2: ListarRegistrosPorID();
    break;
case 3: ListarRegistrosOrdenadosMM();
    break;

default:
    break;
}
}
*/

///OPCIONES DE MODIFICACION
bool ModificarHB(){
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
      cout << "MENU HABITACIONES";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "1. PRECIO";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. STOCK";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "3. DAR DE BAJA";
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
        case 1: CambiarPrecio();
                system("pause");
                break;

        case 2: CambiarStock();
                system("pause");
                break;

        case 3: DarBajaHB();
                system("pause");
                break;

        case 0: return false;
                break;

        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }


}

bool MenuHabitaciones(){
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
      cout << "MENU HABITACIONES";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "1. CARGAR HABITACULOS";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. MOSTRAR (LISTAR)";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "3. MODIFICAR DATOS";
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
        case 1: if(CargarHabitaculos()==false){
                cout << "ERROR EN LA CARGA DEL ARCHIVO" << endl;
            }
            else{
                cout << "REGISTRO CARGADO CON EXITO!" << endl;
            }
                system("pause");
                break;

        case 2: ListarHB();
                break;

        case 3: ModificarHB();
                break;

        case 0: return false;
                break;

        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }

}

#endif // HABITACIONES_H_INCLUDED
