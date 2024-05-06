#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

///BKP HABITACULOS
bool BKPhabitaculos(){
    FILE *p,*i;
    Habitaciones reg;

    int pos=0;
    p=fopen("Habit.bkp","wb");
    if(p==NULL) return false;

    while(reg.LeerDeDisco(pos++)==1){
        fwrite(&reg, sizeof reg, 1, p);
    }
    fclose(p);

    pos=0;
    i=fopen("ARCHINIhabit.bkp","wb");
    if(i==NULL) return false;
    while(reg.LeerDeDisco(pos++)==1){
        fwrite(&reg, sizeof reg, 1,i);
    }
    fclose(i);
    cout<<"ARCHIVO CON DATOS DE INICIO!"<<endl;
    return true;
}

bool RestablecerArchHabitaculos(){
    FILE *p, *bk;
    Habitaciones reg;

    bk=fopen("Habit.bkp", "rb");
    if(bk==NULL) return false;

    p=fopen("","wb");
    if(p==NULL) {
            fclose(bk);
            return false;
    }

    fclose(p);

    while(fread(&reg, sizeof reg, 1, bk)==1){
         reg.GrabarEnDisco();
    }

    fclose(bk);
    system("pause");

    return true;
}

///BKP CLIENTES
bool BKPclientes(){
    FILE *p,*i;
    Cliente reg;

    int pos=0;
    p=fopen("Client.bkp","wb");
    if(p==NULL) return false;

    while(reg.LeerDeDisco(pos++)==1){
        fwrite(&reg, sizeof reg, 1, p);
    }
    fclose(p);

    pos=0;
    i=fopen("ARCHINIclient.bkp","wb");
    if(i==NULL) return false;
    while(reg.LeerDeDisco(pos++)==1){
        fwrite(&reg, sizeof reg, 1,i);
    }
    fclose(i);
    cout<<"ARCHIVO CON DATOS DE INICIO!"<<endl;
    return true;
}

bool RestablecerArchClientes(){
    FILE *p, *bk;
    Cliente reg;

    bk=fopen("Client.bkp", "rb");
    if(bk==NULL) return false;

    p=fopen("","wb");
    if(p==NULL) {
            fclose(bk);
            return false;
    }

    fclose(p);

    while(fread(&reg, sizeof reg, 1, bk)==1){
         reg.GrabarEnDisco();
    }

    fclose(bk);
    system("pause");

    return true;
}

///BKP VENTAS CABECERA
bool BKPventasCab(){
    FILE *p,*i;
    VentasCab reg;

    int pos=0;
    p=fopen("ventCab.bkp","wb");
    if(p==NULL) return false;

    while(reg.LeerDeDisco(pos++)==1){
        fwrite(&reg, sizeof reg, 1, p);
    }
    fclose(p);

    pos=0;
    i=fopen("ARCHINIventCab.bkp","wb");
    if(i==NULL) return false;
    while(reg.LeerDeDisco(pos++)==1){
        fwrite(&reg, sizeof reg, 1,i);
    }
    fclose(i);
    cout<<"ARCHIVO CON DATOS DE INICIO!"<<endl;
    return true;
}

bool RestablecerArchVentasCab(){
    FILE *p, *bk;
    VentasCab reg;

    bk=fopen("ventCab.bkp", "rb");
    if(bk==NULL) return false;

    p=fopen("","wb");
    if(p==NULL) {
            fclose(bk);
            return false;
    }

    fclose(p);

    while(fread(&reg, sizeof reg, 1, bk)==1){
         reg.GrabarEnDisco();
    }

    fclose(bk);
    system("pause");

    return true;
}

///BKP VENTAS DETALLE
bool BKPventasDet(){
    FILE *p,*i;
    VentasDet reg;

    int pos=0;
    p=fopen("ventDab.bkp","wb");
    if(p==NULL) return false;

    while(reg.LeerDeDisco(pos++)==1){
        fwrite(&reg, sizeof reg, 1, p);
    }
    fclose(p);

    pos=0;
    i=fopen("ARCHINIventDab.bkp","wb");
    if(i==NULL) return false;
    while(reg.LeerDeDisco(pos++)==1){
        fwrite(&reg, sizeof reg, 1,i);
    }
    fclose(i);
    cout<<"ARCHIVO CON DATOS DE INICIO!"<<endl;
    return true;
}

bool RestablecerArchVentasDet(){
    FILE *p, *bk;
    VentasDet reg;

    bk=fopen("ventDab.bkp", "rb");
    if(bk==NULL) return false;

    p=fopen("","wb");
    if(p==NULL) {
            fclose(bk);
            return false;
    }

    fclose(p);

    while(fread(&reg, sizeof reg, 1, bk)==1){
         reg.GrabarEnDisco();
    }

    fclose(bk);
    system("pause");

    return true;
}

///MENU
void MenuConfig(){
int opcion;

do{
        system ("cls");

        cout << "    - MENU CONFIGURACION -    " << endl;
        cout << "-----------------------------" << endl;
        cout << "1 - " << endl;
        cout << "2 - " << endl;
        cout << "3 - " << endl;
        cout << "4 - " << endl;
        cout << "5 - " << endl;
        cout << "6 - " << endl;
        cout << "-----------------------------" << endl;
        cout << "0 - SALIR                    " << endl;

        cout << "OPCION:                      " << endl;

        cin >> opcion;
        system("cls");

        switch(opcion)
        {
        case 1:
                system("pause");
            break;

        case 2:
                system("pause");
            break;

        case 3:
                system("pause");
            break;

        case 4:
                system("pause");
            break;

        case 5:
                system("pause");
            break;

        case 6:
                system("pause");
            break;

        default:
            break;
        }

    }
    while(opcion != 0);
}

#endif // CONFIGURACION_H_INCLUDED
