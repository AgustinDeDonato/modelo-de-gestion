#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED

void MenuReportes(){

int opcion;

do{
        system ("cls");

        cout << "    - MENU REPORTES -    " << endl;
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

#endif // REPORTES_H_INCLUDED
