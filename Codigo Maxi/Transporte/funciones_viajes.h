#ifndef FUNCIONES_VIAJES_H_INCLUDED
#define FUNCIONES_VIAJES_H_INCLUDED


void menuViajes(){
    struct viaje reg;
    int opc;
    while(true){
      system("cls");
      cout << "-----MENU DE VIAJES-----" << endl;
      cout << "-------------------------" << endl;
      cout << "1. ALTA DE VIAJE" << endl;
      cout << "2. BAJA DE VIAJE"<<endl;
      cout << "3. LISTAR VIAJE" << endl;
      cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
      cout << "- SELECCIONE UNA OPCION: - " << endl;
      cout << "-------------------------" << endl;
      cin>>opc;
      system("cls");
      switch(opc){
        case 1: reg=cargarViaje();
                if(reg.estado==true){
                  if(grabarRegistroViaje(reg)==true){
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
        case 3: leerArchivoViaje();
                break;
        case 0: return;
                break;
        default:cout<<" OPCION INCORRECTA"<<endl;
                break;
      }
      system("pause");
    }
    return;
}


int contarRegistrosViaje(){
  int cantReg;
  FILE *p;
  p=fopen(ARCHIVO_VIAJES, "rb");
  if(p==NULL) return -1;
  fseek(p,0,2);
  cantReg=ftell(p)/sizeof(struct viaje);
  fclose(p);
  return cantReg;

}


struct viaje cargarViaje(){
  system("cls");
  struct viaje var;
  cout<<"INGRESE EL NUMERO DE VIAJE: ";
  cin>>var.numeroViaje;
  cout<<"INGRESE LA MARCA DEL VEHICULO: " ;
  cin>>var.marca;
  cout<<"INGRESE LA EMPRESA: ";
  cargarCadena(var.codigoEmpresa, 5);
  cout<<"INGRESE LA CANTIDAD DE KM: ";
  cin>>var.cantidadKm;
  cout<<"INGRESE CANTIDAD DE COMBUSTIBLE: "<<endl;
  cin>>var.cantidadCombustible;
  cout<<"INGRESE LA FECHA (DD/MM/AAAA): ";
  cin>>var.fechaViaje.dia;
  cin>>var.fechaViaje.mes;
  cin>>var.fechaViaje.anio;

  var.estado=true;
  return var;
}

void mostrarViaje(viaje var){
  if(var.estado==true){
    system("cls");
    cout<<"NUMERO DE VIAJE: ";
    cout<<var.numeroViaje<<endl;
    cout<<"MARCA DEL VEHICULO: " ;
    cout<<var.marca<<endl;
    cout<<"EMPRESA: ";
    cout<<var.codigoEmpresa<<endl;
    cout<<"CANTIDAD DE KM: ";
    cout<<var.cantidadKm<<endl;
    cout<<"CANTIDAD DE COMBUSTIBLE: ";
    cout<<var.cantidadCombustible<<endl;
    cout<<"FECHA: ";
    cout<<var.fechaViaje.dia<<"/";
    cout<<var.fechaViaje.mes<<"/";
    cout<<var.fechaViaje.anio<<endl;

    system("pause>nul");
  }
}


bool grabarRegistroViaje(viaje aux){
    FILE *p;
		p=fopen(ARCHIVO_VIAJES, "ab");
		///devuelve NULL si no se pudo abrir

		if(p==NULL) return false;

    fwrite(&aux,sizeof aux,1 ,p);

    fclose(p);
    return true;
}

bool leerArchivoViaje(){
    FILE *pColor;
    viaje aux;
		pColor=fopen(ARCHIVO_VIAJES, "rb");
		///devuelve NULL si no se pudo abrir

		if(pColor==NULL) return false;
    while(fread(&aux,sizeof aux,1 ,pColor)==1){
        mostrarViaje(aux);
        cout<<endl;
    }
    fclose(pColor);
    return true;
}


struct viaje leerViaje(int pos){
  FILE *p=NULL;
  struct viaje reg;
  p=fopen(ARCHIVO_VIAJES, "rb");
  if(p==NULL) return reg;///????
  fseek(p, sizeof reg*pos,0);
  fread(&reg, sizeof reg, 1, p);
  fclose(p);
  return reg;
};


void menuReportes(){

}


#endif // FUNCIONES_VIAJES_H_INCLUDED
