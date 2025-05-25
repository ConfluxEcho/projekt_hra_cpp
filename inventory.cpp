#include <iostream>
using namespace std;

void usporadatInventar(string inventar[10], int pocet){
    int check = 0; // Pomocné proměnné, pokud 0, tak se nic neděje, pokud 1, začne posouvat všechny následující itemy dopředu
    for(int i = 0; i < pocet; i++){
        if(check == 1){inventar[i-1] = inventar[i];}
        else if(inventar[i] == "Nic"){check = 1;}
        if(i == pocet-1){inventar[i] = "Nic";}
    }
}

int pridejPredmet(string inventar[], int pocet, string item){
    if(pocet != 10){
        inventar[pocet] = item;
        return 1;
    } else if(pocet == 10){ cout << "V inventáři máte moc itemů, zkuste něco nejdříve odebrat \n"; }
    return 0;
}

void odeberPredmet(string inventar[], int &pocet, int poradi){
    if( poradi > 0 && poradi < 11){
        inventar[poradi-1] = "Nic";
        usporadatInventar(inventar, pocet);
        pocet--;
    } else {cout << "Neplatné pořadí, zkuste to znovu \n";}
}

string pouzijPredmet(string inventar[], int pocet, int &zivoty, int &utok, string vyber){
    int idx = -1;
    for(int i = pocet-1; i>=0; i--){
        if (inventar[i] == vyber){idx = i; break;}
    }
    if(idx == -1){cout << "Vámi uvedený item není v inventáři, zkuste to znovu \n"; return "Nic"; }
    else {
        inventar[idx] = "Nic";
        usporadatInventar(inventar, pocet);
        return vyber;
    }
}

void vypisInventar(string inventar[], int pocet){
    cout << "Itemy v inventáři: \n";
    for (int i=0; i<pocet; i++){ cout << inventar[i] << "  |  "; }
    cout << endl;
}


int inventar(string (&inv)[10], int &zivoty, int &utok, string pridat, string &item){
    string select;
    int akce, pocet, select_int;
    bool running = true;
    for(int i=0; i<10; i++){if(inv[i] == "Nic"){pocet=i; break;}} // Zjišťování počet itemů v inventáři

    if(pridat != "Nic"){return pridejPredmet(inv, pocet, pridat);}

    while(running){
        cout << "------------------------------------------------------------------------------------------------------------\n";
        cout << "Co chcete udělat? 1 - Odebrat předmět; 2 - Použít předmět; 3 - Zobrazit inventář; 4 - Ukončit \n";
        cin >> akce;

        switch(akce){
            case 1:
                if(pocet <= 0){pocet = 0; cout << "V inventáři není nic, co byste mohli odstranit \n"; break;}
                cout << "Zadejte pořadí itemu, který chcete odstranit (od 1); Aktuální počet itemů --> " << pocet << ": ";
                cin >> select_int;
                odeberPredmet(inv, pocet, select_int);
                break;
            case 2:
                cout << "Zadejte jméno itemu, který chcete použít: ";
                cin >> select;
                select = pouzijPredmet(inv, pocet, zivoty, utok, select);
                if (select == "Nic"){break;}
                item = select;
                return 1;
            case 3:
                vypisInventar(inv, pocet);
                break;
            case 4:
                running = false;
                break;
            default:
                cout << "Neplatný příkaz, zkuste to znovu \n";
        }
    }

    return 0;
}
