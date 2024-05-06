#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

///CLASE CLIENTE
class Cliente{
private:
    int DNI;
    char Nombre[25];
    char Apellido[25];
    char Email[30];
    Fecha fechaIncorporacion;
    char Tel[20];
    bool Estado;

public:

    ///CONSTRUCTOR
    Cliente(int d=00000, const char *n="00000", const char *a="00000", const char *e="00000",const char *t="00000"){
        DNI=d;
        strcpy(Nombre,n);
        strcpy(Apellido,a);
        strcpy(Email,e);
        strcpy(Tel,t);
        Estado=e;
    }

    void Cargar();
    void Mostrar();

    ///sets
    void setDni(int d){
        DNI=d;
    }
    void setNombre(char *n){
        strcpy(Nombre,n);
    }
    void setApellido(char *a){
        strcpy(Apellido,a);
    }
    void setEmail(char *e){
        strcpy(Email,e);
    }
    void setTel(char *t){
        strcpy(Tel,t);
    }
    void setfechaIncorporacion(Fecha f){
        fechaIncorporacion = f;
    }
    void setEstado(bool e){
        Estado=e;
    }

    ///gets
    int getDni(){
        return DNI;
        }
    const char *getNombre(){
        return Nombre;
        }
    const char *getApellido(){
        return Apellido;
        }
    const char *getEmail(){
        return Email;
        }
    const char *getTel(){
        return Tel;
        }
    Fecha getfechaIncorporacion(){
        return fechaIncorporacion;
        }
    int getEstado(){
        return Estado;
        }

        bool GrabarEnDisco();
        bool LeerDeDisco(int pos);

};

bool Cliente::GrabarEnDisco(){
    FILE *p;
    bool escribio;
    p=fopen("Cliente.dat", "ab");
    if(p==NULL) return false;
    escribio=fwrite(this, sizeof(Cliente),1,p);
    fclose(p);
    return escribio;
}

bool Cliente::LeerDeDisco(int pos){
    FILE *pCliente;

    pCliente= fopen("Cliente.dat", "rb");

    if(pCliente==NULL){
    return false;
    }
    fseek(pCliente, pos*sizeof(Cliente), 0);
    bool Leyo = fread(this, sizeof(Cliente), 1, pCliente);

    fclose(pCliente);
    return Leyo;
}

int BuscarPorDNI(int DNI){

Cliente reg;
int pos=0;

FILE *p;
p=fopen("cliente.dat", "rb");

if(p==NULL){
    return -2;
}
while(fread(&reg, sizeof reg, 1, p)==1){
    if(reg.getDni()==DNI){
        fclose(p);
        return pos;
    }
    pos++;
}

fclose(p);
return -1;

}

void Cliente::Cargar(){
    bool pasaDNI;

    do{
    cout << "INGRESE EL DNI DEL CLIENTE: ";
    cin >> DNI;
    int pos=BuscarPorDNI(DNI);
    if(pos<0){
        pasaDNI = true;
    }
    else{
        system("cls");
        cout << "ESTE DNI YA FUE INGRESADO, INTENTE NUEVAMENTE" << endl;
        pasaDNI = false;
    }
    }while(pasaDNI == false);
    cout << "INGRESE EL NOMBRE: ";
    cin >> Nombre;
    cout << "INGRESE EL APELLIDO: ";
    cin >> Apellido;
    cout << "INGRESE EL EMAIL: ";
    cin >> Email;
    cout << "FECHA DE NACIMIENTO: " << endl;
    fechaIncorporacion.Carga();
    cout << "INGRESE EL TELEFONO: ";
    cin >> Tel;

    Estado=true;
}

void Cliente::Mostrar(){
    if(getEstado()==true){
        cout << "DNI DE CLIENTE: ";
        cout << DNI << endl;
        cout << "NOMBRE: ";
        cout << Nombre << endl;
        cout << "APELLIDO: ";
        cout << Apellido << endl;
        cout << "EMAIL: ";
        cout << Email << endl;
        cout << "FECHA DE NACIMIENTO: ";
        fechaIncorporacion.Muestra();
        cout << "TELEFONO: ";
        cout << Tel << endl;
        cout << "-------------------------------" << endl;
    }
}

///CARGA
bool CargaCliente(){

Cliente reg;
reg.Cargar();

FILE *pCliente;

pCliente=fopen("Cliente.dat", "ab");
if(pCliente==NULL){
    return false;
}

bool escribio;
escribio = fwrite(&reg, sizeof reg, 1, pCliente);
fclose(pCliente);

return escribio;

}

///LISTA TODOS
bool ListarRegistrosCliente(){

Cliente reg;

FILE *pCliente;
pCliente=fopen("cliente.dat", "rb");

if(pCliente==NULL){
    return false;
}
while(fread(&reg, sizeof reg, 1, pCliente)==1){
    reg.Mostrar();
}

fclose(pCliente);
return true;

}

///LISTA POR DNI
bool ListarRegistroPorDNI(){

Cliente reg;
int DNI;
bool idPasa = false;

cout << "INGRESE EL DNI DEL CLIENTE A BUSCAR: ";
cin >> DNI;
cout << endl;

FILE *pCliente;
pCliente=fopen("cliente.dat", "rb");

if(pCliente==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pCliente)==1){

    if(DNI==reg.getDni()){
    reg.Mostrar();
    idPasa = true;
    }
}

fclose(pCliente);

if(idPasa==false){
    cout << "ESTE DNI DE CLIENTE NO EXISTE" << endl;
}

return true;
}

///CONTAR REGISTRO
int ContarRegistrosCliente(){
  int cantReg;
  FILE *pCliente;
  pCliente=fopen("Cliente.dat", "rb");
  if(pCliente==NULL) return -1;
  fseek(pCliente,0,2);
  cantReg=ftell(pCliente)/sizeof(Cliente);
  fclose(pCliente);
  return cantReg;
}

///COPIA ARCHIVOS
void CopiarArchivoCliente(Cliente *pCliente, int CantClientes){
    int i;
    for(i=0;i<CantClientes;i++){
        pCliente[i].LeerDeDisco(i); ///AGREGAR
    }
}

///ORDENO ARCHIVO
void OrdenarClientes(Cliente *pCliente, int CantClientes){
    int i, j, posMin;
    Cliente aux;
    for(i=0;i<CantClientes-1;i++){
        posMin=i;
        for(j=i+1;j<CantClientes;j++){
            if(pCliente[j].getDni() < pCliente[posMin].getDni()){
                posMin=j;
            }
        }
        aux=pCliente[i];
        pCliente[i]=pCliente[posMin];
        pCliente[posMin]=aux;

    }
 }

///IMPRIMO
void MostrarVectorClientes(Cliente *pCliente,int CantClientes){
    int i;
    for(i=0;i<CantClientes;i++){
        pCliente[i].Mostrar();
    }
}

///LISTA ORDENADOS - A +
void ListarRegistroClienteOrdenadoMM(){
///Contar los registros.
    int CantClientes=ContarRegistrosCliente();
///Crear un vector mediante la asignación dinámica de memoria.
    Cliente *pCliente;
    pCliente=new Cliente[CantClientes];///o una dirección válida, o NULL
    if(pCliente==NULL){
        cout<<"ERROR DE ASIGNACION DE MEORIA";
        return;
    }

///Copiar los registros del archivo en el vector.
    CopiarArchivoCliente(pCliente, CantClientes);
///Ordeno el vector.
    OrdenarClientes(pCliente, CantClientes);
///Muestro (imprimo).
    MostrarVectorClientes(pCliente, CantClientes);
///Devolver la memoria pedida
    delete pCliente;
}

///CAMBIAR MAIL CLIENTE
bool CambiarMailCliente(){

Cliente reg;
int DNI;
char mail[30];

FILE *pCliente;
pCliente=fopen("Cliente.dat", "rb+");

cout << "INGRESE EL DNI DEL CLIENTE A BUSCAR: ";
cin >> DNI;
cout << endl;
cout << "INGRESE EL MAIL DEL CLIENTE A MODIFICAR: ";
cin >> mail;
cout << endl;

if(pCliente==NULL){
    return false;
}

while(fread(&reg, sizeof reg, 1, pCliente)==1){

    if(DNI==reg.getDni()){
            reg.setEmail(mail);
            fseek(pCliente, ftell(pCliente)-sizeof (Cliente), 0);
            fwrite(&reg, sizeof reg, 1, pCliente);
            fseek(pCliente,0,2);
        }
}

fclose(pCliente);
return true;
}

///BAJA LOGICA
bool DarBajaCliente(){

Cliente reg;
int DNI;

cout << "INGRESE EL DNI DEL CLIENTE A BUSCAR: ";
cin >> DNI;
cout << endl;

FILE *pCliente;
pCliente=fopen("Cliente.dat", "rb+");

if(pCliente==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pCliente)==1){

    if(DNI==reg.getDni()){
    reg.setEstado(false);
    fseek(pCliente, ftell(pCliente)-sizeof (Cliente), 0);
    fwrite(&reg, sizeof reg, 1, pCliente);
    fseek(pCliente,0,2);
    cout << "SU REGISTRO A SIDO ELIMINADO" << endl;
    }
}

fclose(pCliente);
return true;
}

///ALTA LOGICA
bool DarAltaCliente(){

Cliente reg;
int DNI;
cout << "INGRESE EL DNI DEL CLIENTE A BUSCAR: ";
cin >> DNI;
cout << endl;

FILE *pCliente;
pCliente=fopen("Cliente.dat", "rb+");

if(pCliente==NULL){
    return false;
}


while(fread(&reg, sizeof reg, 1, pCliente)==1){

    if(DNI==reg.getDni()){
    reg.setEstado(true);
    fseek(pCliente, ftell(pCliente)-sizeof (Cliente), 0);
    fwrite(&reg, sizeof reg, 1, pCliente);
    fseek(pCliente,0,2);
    cout << "SU REGISTRO A SIDO DADO DE ALTA" << endl;
    }
}

fclose(pCliente);
return true;
}

///OPCIONES LISTAR
bool ListarCL(){
    setlocale(LC_ALL, "spanish");
    setConsoleTitle("VIVIRE");
    AjustarVentana(120,30);
    const int ANCHO_MENU = 41;
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
      cout << "1. MOSTRAR CLIENTES CARGADOS";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. MOSTRAR CLIENTES POR DNI";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "3. MOSTRAR CLIENTES ORDENADOS POR DNI";
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
        case 1: ListarRegistrosCliente();
                system("pause");
                break;

        case 2: ListarRegistroPorDNI();
                system("pause");
                break;

        case 3: ListarRegistroClienteOrdenadoMM();
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
///OPCIONES LISTAR
void ListarCL(){
int Op;

cout << "SELECCIONAR LA FORMA PARA LISTAR:      " << endl;
cout << "---------------------------------------" << endl;
cout << "(1) MOSTRAR CLIENTES CARGADOS          " << endl;
cout << "(2) MOSTRAR CLIENTES POR DNI           " << endl;
cout << "(3) MOSTRAR CLIENTES ORDENADOS POR DNI " << endl;
cout << "---------------------------------------" << endl;
cout << "OPCION: ";
cin >> Op;
system("cls");

switch(Op){
case 1: ListarRegistrosCliente();
    break;
case 2: ListarRegistroPorDNI();
    break;
case 3: ListarRegistroClienteOrdenadoMM();
    break;

default:
    break;
}
}
*/
///OPCIONES DE MODIFICACION
bool ModificarCL(){
    setlocale(LC_ALL, "spanish");
    setConsoleTitle("VIVIRE");
    AjustarVentana(120,30);
    const int ANCHO_MENU = 26;
    const int ALTO_MENU = 9;
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
      cout << "1. MAIL";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "2. DAR DE BAJA";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "3. DAR DE ALTA";
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
        case 1: CambiarMailCliente();
                system("pause");
                break;

        case 2: DarBajaCliente();
                system("pause");
                break;

        case 3: DarAltaCliente();
                system("pause");
                break;

        case 0: return false;
                break;

        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }


}

bool MenuCliente(){
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
      cout << "MENU CLIENTE";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "1. CARGAR CLIENTE";
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
        case 1: if(CargaCliente()==false){
                cout << "ERROR EN LA CARGA DEL ARCHIVO" << endl;
            }
            else{
                cout << "REGISTRO CARGADO CON EXITO!" << endl;
            }
                system("pause");
                break;

        case 2: ListarCL();
                break;

        case 3: ModificarCL();
                break;

        case 0: return false;
                break;

        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }

}



#endif // CLIENTES_H_INCLUDED
