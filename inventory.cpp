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

void pridejPredmet(string inventar[], int &pocet, string item, string itemy[4]){
    char check = 'N';
    for(int i=0; i<5; i++){ if (item == itemy[i]){check = 'Y'; break;} }
    if( check == 'Y' && pocet != 10){
        inventar[pocet] = item;
        pocet ++;
    } else if(pocet == 10){ cout << "V inventáři máte moc itemů, zkuste něco nejdříve odebrat \n"; }
    else {cout << "Item je neplatný, zkuste to znovu \n"; }
}

void odeberPredmet(string inventar[], int &pocet, int poradi){
    if( poradi > 0 && poradi < 11){
        inventar[poradi-1] = "Nic";
        usporadatInventar(inventar, pocet);
        pocet--;
    } else {cout << "Neplatné pořadí, zkuste to znovu \n";}
}


// Následující funkce z nějakého důvodu nefunguje
void pouzijPredmet(string inventar[], int&pocet, int &zivoty, int &utok, string vyber){
    int idx = -1;
    for(int i = pocet-1; i>=0; i--){
        if (inventar[i] == vyber){idx = i; break;}
    }
    if(idx == -1){cout << "Vámi uvedený item není v inventáři, zkuste to znovu \n";}
    else {
        if(vyber == "lékárna"){zivoty += 10;}
        else if(vyber == "elixír"){utok += 5;}
        else if(vyber == "otrava"){zivoty -= 10;}
        else if(vyber == "tajemný_svitek"){/*Zatím nic*/}
        inventar[idx] = "Nic";
        usporadatInventar(inventar, pocet);
        pocet --;
    }
}

void vypisInventar(string inventar[], int pocet){
    cout << "Itemy v inventáři: \n";
    for (int i=0; i<pocet; i++){ cout << inventar[i] << "  |  "; }
    cout << endl;
}

int inventar(){
    string inventar[10], select;
    int akce, pocet=0, zivoty, utok, select_int;
    bool running = true;
    string itemy[4] = {"lékárna", "elixír", "otrava", "tajemný_svitek"};

    while(running){
        cout << "------------------------------------------------------------------------------------------------------------\n";
        cout << "Co chcete udelat? 1 - pridat predmet; 2 - odebrat predmet; 3 - pouzit predmet; 4 - zobrazit inventar; 5 - ukoncit \n";
        cin >> akce;

        switch(akce){
            case 1:
                cout << "Který předmět chcete přidat? \n";
                for(string item : itemy){ cout << item << "  |  " ;}
                cout << endl;
                cin >> select;
                pridejPredmet(inventar, pocet, select, itemy);
                break;
            case 2:
                if(pocet <= 0){pocet = 0; cout << "V inventáři není nic, co byste mohli odstranit \n"; break;}
                cout << "Zadejte pořadí itemu, který chcete odstranit (od 1); Aktuální počet itemů --> " << pocet << ": ";
                cin >> select_int;
                odeberPredmet(inventar, pocet, select_int);
                break;
            case 3:
                cout << "Zadejte jméno itemu, který chcete použít: ";
                cin >> select;
                pouzijPredmet(inventar, pocet, zivoty, utok, select);
                break;
            case 4:
                vypisInventar(inventar, pocet);
                break;
            case 5:
                running = false;
                break;
            default:
                cout << "Neplatný příkaz, zkuste to znovu \n";
        }
    }

    return 0;
}
