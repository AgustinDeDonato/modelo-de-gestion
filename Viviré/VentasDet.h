#ifndef VENTASDET_H_INCLUDED
#define VENTASDET_H_INCLUDED

class VentasDetalle{
private:
    int nVentaDetalle;
    int DNIventa;

public:

    void Cargar();
    void Mostrar();

///SETS
    void setNumVentaDetalle(int nVd){
        nVentaDetalle=nVd;
    }
    void setDniVenta(int dV){
        DNIventa=dV;
    }

///GETS
    int getNumVentaDetalle(){
        return nVentaDetalle;
        }
    int getDniVenta(){
        return DNIventa;
        }
};

void Desc_PrecUni(int Art){
Habitaciones reg;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return;
}
while(fread(&reg, sizeof reg, 1, pHabitaculos)==1){
    if(reg.getIDarticulo()==Art){
        cout << "DESCRIPCION: "<< reg.getDescripcion() << endl;
        cout << "PRECIO UNITARIO: $" << reg.getPrecio() << endl;
    }
}

fclose(pHabitaculos);
}

void PrecioFinal(int idArticulo, int cantV, int MedPago){

Habitaciones obj;
float importeV=0;
float imp_t=0;

FILE *pHabitaculos;
pHabitaculos=fopen("Habitaciones.dat", "rb");

if(pHabitaculos==NULL){
    return;
}
while(fread(&obj, sizeof obj, 1, pHabitaculos)==1){
        switch(MedPago){
                    case 1:
                        imp_t = obj.getPrecio()*cantV;
                        importeV = imp_t*1.07;
                        cout << "--------------------------------------------------" << endl;
                        cout << "PRECIO FINAL: $" << importeV << endl;
                        cout << "--------------------------------------------------" << endl;
                        break;
                    case 2:
                        imp_t = obj.getPrecio()*cantV;
                        importeV = imp_t*1.15;
                        cout << "--------------------------------------------------" << endl;
                        cout << "PRECIO FINAL: $" << importeV << endl;
                        cout << "--------------------------------------------------" << endl;
                        break;
                    case 3:
                        importeV = obj.getPrecio()*cantV;
                        cout << "--------------------------------------------------" << endl;
                        cout << "PRECIO FINAL: $" << importeV << endl;
                        cout << "--------------------------------------------------" << endl;
                        break;

                    default:
                        break;
                        }
 }
    fclose(pHabitaculos);
}

int PrecioFinal(int idArticulo, int cantV){

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

void Mos_Dat(){

Ventas reg;
int IDH=0;
int CVH=0;
float ImporteFinal=0;
///int MDH=0;

FILE *pVentas;
pVentas=fopen("ventasCab.dat", "rb");

if(pVentas==NULL){
    cout << "ERROR DE CARGA" << endl;
    return;
}

while(fread(&reg, sizeof reg, 1, pVentas)==1){
    IDH=reg.getIdArticulo();
    CVH=reg.getCantVend();
    ///MDH=reg.getMedpago();

    float importeF = PrecioFinal(IDH, CVH);
    ImporteFinal+=importeF;
}

fclose(pVentas);
cout << "--------------------------------------------------" << endl;
cout << "TOTAL: $" << ImporteFinal << endl;
}

void VerVenta(int DNIventa){

Ventas reg;
int Art=0;

FILE *pVentas;
pVentas=fopen("ventasCab.dat", "rb");

if(pVentas==NULL){
    cout << "ERROR DE CARGA" << endl;
}

while(fread(&reg, sizeof reg, 1, pVentas)==1){
    if(reg.getDniCliente()==DNIventa){
            cout << "--------------------------------------------------" << endl;
            cout << "NUMERO DE VENTA: " << reg.getNumVenta() << endl;
            cout << "ID DE ARTICULO: " << reg.getIdArticulo() << endl;
            ///FUNCION (DESCRIPCION Y PRECIO UNITARIO)
            Art=reg.getIdArticulo();
            Desc_PrecUni(Art);
            cout << "CANTIDAD SELECCIONADA: " << reg.getCantVend() << endl;

            /**if(reg.getMedpago()==1){
                cout << "METODO DE PAGO: DEBITO" << endl;
            }
            if(reg.getMedpago()==2){
                cout << "METODO DE PAGO: CREDITO" << endl;
            }
            if(reg.getMedpago()==3){
                cout << "METODO DE PAGO: TRANSFERENCIA" << endl;
            }*/

    }
}

fclose(pVentas);
}

void VentasDetalle::Cargar(){
///AUTONUMERICO
    cout << "DNI DEL CLIENTE: ";
    cin >> DNIventa;

}

void VentasDetalle::Mostrar(){


VerVenta(DNIventa);
Mos_Dat();

}

bool CargaVentaDetalle(){
VentasDetalle reg;
reg.Cargar();

FILE *pVentasDET;

pVentasDET=fopen("ventasDET.dat", "ab");
if(pVentasDET==NULL){
    return false;
}

bool escribio;
escribio = fwrite(&reg, sizeof reg, 1, pVentasDET);
fclose(pVentasDET);

return escribio;
}

bool ListarRegistroVentaDetalle(){

VentasDetalle reg;

FILE *pVentasDET;
pVentasDET=fopen("ventasDET.dat", "rb");

if(pVentasDET==NULL){
    return false;
}
while(fread(&reg, sizeof reg, 1, pVentasDET)==1){
    reg.Mostrar();
}

fclose(pVentasDET);
return true;
}

void MenuDetalle(){
CargaVentaDetalle();
ListarRegistroVentaDetalle();
system("pause");
}

#endif // VENTASDET_H_INCLUDED
