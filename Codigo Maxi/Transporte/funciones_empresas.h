#ifndef FUNCIONES_EMPRESAS_H_INCLUDED
#define FUNCIONES_EMPRESAS_H_INCLUDED

void menuEmpresas(){
    struct empresa reg;
    int opc;
    const int ANCHO_MENU = 23;
    const int ALTO_MENU = 7;
    while(true){
      setBackgroundColor(COLOR_PANTALLA);
      cls();
      setBackgroundColor(FONDO);
      recuadro(POSMENUX,POSMENUY, ANCHO_MENU,ALTO_MENU,LETRA,FONDO);
      separadorH(POSMENUX,POSMENUY+2,ANCHO_MENU,LETRA,FONDO);
      locate(POSMENUX+6,POSMENUY+1);
      cout << "MENÚ EMPRESAS";
      locate(POSMENUX+3,POSMENUY+3);
      cout << "1. ALTA";
      locate(POSMENUX+3,POSMENUY+4);
      cout << "2. BAJA";
      locate(POSMENUX+3,POSMENUY+5);
      cout << "3. LISTADO";
      locate(POSMENUX+3,POSMENUY+6);
      cout << "0. VOLVER";
      locate(POSMENUX,POSMENUY+ALTO_MENU+1);
      cout << " SELECCIONE UNA OPCION: ";
      hidecursor();
      cin>>opc;
      setBackgroundColor(COLOR_PANTALLA);
      cls();
      setBackgroundColor(FONDO);
      switch(opc){
        case 1: reg=cargarEmpresa();
                if(reg.estado==true){
                  if(grabarRegistroEmpresa(reg)==true){
                    cout<<"REGISTRO GRABADO EN EL ARCHIVO"<<endl;
                  }
                  else{
                    cout<<"NO SE PUDO GRABAR EL REGISTRO"<<endl;
                  }
                }
                else{
                  cout<<"ERROR DE DATOS"<<endl;
                }
                break;
        case 2:
                break;
        case 3: listarEmpresas();
                break;
        case 0: return;
                break;
        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
    }
    return;
}

int contarRegistrosEmpresa(){
  int cantReg;
  FILE *p;
  p=fopen(ARCHIVO_EMPRESAS, "rb");
  if(p==NULL) return -1;
  fseek(p,0,2);
  cantReg=ftell(p)/sizeof(struct empresa);
  fclose(p);
  return cantReg;

}


struct empresa cargarEmpresa(){
    dibujarTablaListadoEmpresas(5);
    ampliarTabla(5);
    recuadro(5,15,83,10,LETRA,FONDO);
    locate(6,16);
    cout<<"-EL CÓDIGO DEBE SER DE CUATRO CARACTERES MÁXIMO (LETRAS Y NÚMEROS)";
    locate(6,17);
    cout<<"-EL NOMBRE DEBE TENER COMO MÁXIMO 29 CARACTERES";
    locate(6,18);
    cout<<"-LA DIRECCIÓN DEBE TENER COMO MÁXIMO 39 CARACTERES";
    locate(6,19);
    cout<<"-NOMBRE DEBE TENER COMO MÁXIMO 29 CARACTERES";
    locate(6,20);
    cout<<"-EL TIPO DE EMPRESA PUEDE SER:";
    locate(6,21);
    cout<<"\t\t1: LOCAL";
    locate(6,22);
    cout<<"\t\t2: INTERURBANO";
    locate(6,23);
    cout<<"\t\t3: NACIONAL";
    locate(6,24);
    cout<<"\t\t4: INTERNACIONAL";
    empresa reg;
    showcursor();
    locate(7,5);
    cargarCadena(reg.codigoEmpresa,5);
    locate(13,5);
    cargarCadena(reg.nombreEmpresa,30);
    locate(43,5);
    cargarCadena(reg.direccion,40);
    locate(85,5);
    cin>>reg.tipoEmpresa;
    reg.estado=true;
    return reg;
}

void mostrarEmpresa(empresa var){
  if(var.estado==true){
      cls();
      cout<<"CODIGO: ";
      cout<<var.codigoEmpresa<<endl;
      cout<<"NOMBRE: ";
      cout<<var.nombreEmpresa<<endl;
      cout<<"DIRECCION: ";
      cout<<var.direccion<<endl;
      cout<<"TIPO: ";
      cout<<var.tipoEmpresa<<endl;
      anykey();
  }
}


bool grabarRegistroEmpresa(empresa aux){
    FILE *p;
		p=fopen(ARCHIVO_EMPRESAS, "ab");
		///devuelve NULL si no se pudo abrir

		if(p==NULL) return false;

    fwrite(&aux,sizeof aux,1 ,p);

    fclose(p);
    return true;
}

bool leerArchivoEmpresa(){
    FILE *pColor;
    empresa aux;
		pColor=fopen(ARCHIVO_EMPRESAS, "rb");
		///devuelve NULL si no se pudo abrir

		if(pColor==NULL) return false;
    while(fread(&aux,sizeof aux,1 ,pColor)==1){
        mostrarEmpresa(aux);
        cout<<endl;
    }
    fclose(pColor);
    return true;
}


struct empresa leerEmpresa(int pos){
  FILE *p=NULL;
  struct empresa reg;
  p=fopen(ARCHIVO_EMPRESAS, "rb");
  if(p==NULL) return reg;///????
  fseek(p, sizeof reg*pos,0);
  fread(&reg, sizeof reg, 1, p);
  fclose(p);
  return reg;
};

void listarEmpresas(){
    int fila, cant;
    cant=contarRegistrosEmpresa();
    fila=7;
    empresa reg;
    dibujarTablaListadoEmpresas(fila);
    for(int i=0;i<cant;i++){
        reg=leerEmpresa(i);
        if(reg.estado==true){
            ampliarTabla(fila);
            mostrarEmpresaRecuadro(reg, fila);
            fila++;
            if(i!=cant-1){
                separadorH(5,fila,83,LETRA,FONDO);
                setlocale(LC_ALL,"C");
                locate(12, fila);
                cout<<(char)206;
                locate(42, fila);
                cout<<(char)206;
                locate(82, fila);
                cout<<(char)206;
                setlocale(LC_ALL,"spanish");
                fila++;
            }
        }
    }
    hidecursor();
    anykey();
    showcursor();
}

void mostrarEmpresaRecuadro(empresa reg, int fila){
    locate(7, fila);
    cout<<reg.codigoEmpresa;
    locate(13, fila);
    cout<<reg.nombreEmpresa;
    locate(43, fila);
    cout<<reg.direccion;
    locate(85, fila);
    cout<<reg.tipoEmpresa;
}

/*void dibujarTablaListadoEmpresas(int fila, int cant){
    recuadro(5,fila-3,83,2,LETRA,FONDO);
    recuadro(5,fila-1,83,2*cant,LETRA,FONDO);
    locate(6,fila-2);
    cout<<"CÓDIGO";
    locate(13,fila-2);
    cout<<"NOMBRE";
    locate(43,fila-2);
    cout<<"DIRECCIÓN";
    locate(83,fila-2);
    cout<<"TIPO";
    separadorV(12,fila-3,2*cant+2,LETRA,FONDO);
    separadorV(42,fila-3,2*cant+2,LETRA,FONDO);
    separadorV(82,fila-3,2*cant+2,LETRA,FONDO);
    separadorH(5,fila-1,83,LETRA,FONDO);
    setlocale(LC_ALL,"C");
    locate(12, fila-1);
    cout<<(char)206;
    locate(42, fila-1);
    cout<<(char)206;
    locate(82, fila-1);
    cout<<(char)206;
    setlocale(LC_ALL,"spanish");
}*/

void dibujarTablaListadoEmpresas(int fila){
    recuadro(5,fila-3,83,2,LETRA,FONDO);
    separadorV(12,fila-3,2,LETRA,FONDO);
    separadorV(42,fila-3,2,LETRA,FONDO);
    separadorV(82,fila-3,2,LETRA,FONDO);
    locate(6,fila-2);
    cout<<"CÓDIGO";
    locate(13,fila-2);
    cout<<"NOMBRE";
    locate(43,fila-2);
    cout<<"DIRECCIÓN";
    locate(83,fila-2);
    cout<<"TIPO";
}

void ampliarTabla(int fila){
    recuadro(5, fila-1, 83, 2, LETRA, FONDO);
    separadorV(12,fila-1,2,LETRA,FONDO);
    separadorV(42,fila-1,2,LETRA,FONDO);
    separadorV(82,fila-1,2,LETRA,FONDO);
    separadorH(5,fila-1,83,LETRA,FONDO);
    setlocale(LC_ALL,"C");
    locate(12, fila-1);
    cout<<(char)206;
    locate(42, fila-1);
    cout<<(char)206;
    locate(82, fila-1);
    cout<<(char)206;
    setlocale(LC_ALL,"spanish");
}

#endif // FUNCIONES_EMPRESAS_H_INCLUDED
