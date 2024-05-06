#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

///CLASE FECHA
class Fecha{
private:
    int dia, mes, anio;

public:
    Fecha(){
    dia=00;
    mes=00;
    anio=0000;
    }

    void Carga();
    void Muestra();

    ///sets
    void setDia(int d){
        if(d>0 && d<32){
            dia=d;
        }
        else{
            dia=0;
        }
    }

    void setMes(int d){
        if(d>0 && d<13){
            mes=d;
        }
        else{
            mes=0;
        }
    }

    void setAnio(int d){
        if(d>0){
            anio=d;
        }
        else{
            anio=0;
        }
    }
    ///gets
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}

};

/// CARGA Y MUESTRA DE FECHA
void Fecha::Carga(){
int aux;

cout << "INGRESE EL DIA: ";
cin >> aux;
setDia(aux);
cout << "INGRESE EL MES: ";
cin >> aux;
setMes(aux);
cout << "INGRESE EL ANIO: ";
cin >> aux;
setAnio(aux);
}

void Fecha::Muestra(){
        cout << dia << "/" << mes << "/" << anio << endl;
    }


#endif // FECHA_H_INCLUDED
