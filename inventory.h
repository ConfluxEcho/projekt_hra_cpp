#pragma once

#include <thread>
#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Stats hráče
struct Player {
    string name;
    int max_health;
    int health;
    int max_mana;
    int mana;
    int attack;
    int level;
    int experience;
    int number_of_abilities;

    int money;
    string inventory[10];
    string abilities[5];
};

// Funkce na převod řetězce na malá písmena
string lower(string &input){
    for(char &c : input){
        // static_cast<unsigned char> použito pro správné chování funkce tolower(), \
           která očekává nezápornou hodnotu typu char v ASCII tabulce
        c = tolower(static_cast<unsigned char>(c));
    }
    return input;
}

// Funkce na čekání
void wait(unsigned int duration){
    this_thread::sleep_for(chrono::seconds(duration));
}

// Definice kódu pro barev na barevný terminál
unordered_map<string, int> colors = {
    {"Black", 30}, // Obecný text či příběh, střídá se s bílou pro lepší čitelnost
    {"Red", 31}, // Game over stats nebo začátek nebezpečné sekce (bojování)
    {"Green", 32}, // Popis stats před nějakou akcí (hráčův pohyb v boji)
    {"Yellow", 33}, // Varování na nesprávný vstup nebo nedostatek měny
    {"Blue", 34}, // Informace o akcích monstra
    {"Magenta", 35}, // Inventář
    {"Cyan", 36}, // Informace o akcích či eventech hráče
    {"White", 37} // Obecný text či příběhm, střídá se s černou pro lepší čitelnost
};

void setColor(string col){
    cout << "\033[" << colors[col] << "m";
}

void resetColor(){
    cout << "\033[0m";
}

void get_int(int &input){
    while (true){
        cin >> input;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            setColor("Yellow");
            cout << "Nesprávný vstup, zkuste to znovu. \n";
            setColor("Black");
        } else{break;}
    }
}

// Funkce na používání itemů
string stats_update(string item, Player &player){
    // Stats itemů {Životy, Max Životy, Útok, Mana, Max Mana}
    unordered_map<string, array<int, 5> > items = {
        {"Lékárna", {20, 0, 0, 0, 0}},
        {"Elixír", {0, 0, 5, 0, 0}},
        {"Magická koule", {0, 0, 0, 0, 15}},
        {"Lektvar života", {0, 10, 0, 0, 0}}
    };
    if((item == "Magická koule" || item == "Dobíječ many") && player.name == "válečník"){
        setColor("Yellow"); cout << "Jakožo válečník nemůžete mít manu \n"; return item;}
    else if(item == "Dobíječ many"){
        setColor("Cyan");
        int mana_calc = player.max_mana - player.mana;
        if(mana_calc / 2 < 10){player.mana += 10; cout << "Získali jste 10 many. \n";}
        else{player.mana += mana_calc / 2; cout << "Získali jste " << mana_calc / 2 << " many. \n";}
    }
    else if(item == "Nápoj náhody"){ // 1 = Životy, 2 = Max životy, 3 = Útok, 4 = Mana, 5 = Max Mana
        setColor("Cyan");
        int effect;
        do{effect = rand() % 5;} while(player.name == "Válečník" && (effect == 4 || effect == 5)); // Válečník nemůže mít manu
        int positivity = rand() % 2;
        if(effect == 0){
            if(positivity == 0){player.health -= 10; cout << "Hráč přichází o 10 životů. \n";}
            else if(positivity==1){player.health += 10; cout << "Hráč získává 15 životů. \n";}
        } else if(effect == 1){
            if(positivity == 0){player.max_health -= 10; cout << "Hráč má nyní o 10 méně max životů než předtím. \n";}
            else if(positivity == 1){player.max_health += 10; cout << "Hráč má nyní o 20 více max životy než předtím. \n";}
        } else if(effect == 2){
            if(positivity == 0){player.attack -= 5; cout << "Hráč má nyní útok menší o 5. \n";}
            else if(positivity == 1){player.attack += 5; cout << "Hráč má nyní útok větší o 10. \n";}
        } else if(effect == 3){
            if(positivity == 0){player.mana -= 10; cout << "Hráč má nyní o 10 menší manu. \n";}
            else if(positivity == 1){player.mana += 10; cout << "Hráč má nyní o 15 větší manu. \n";}
        } else if(effect == 4){
            if(positivity == 0){player.max_mana -= 10; cout << "Hráčovi se max mana snížila o 10. \n";}
            else if(positivity == 1){player.max_mana += 10; cout << "Hráčovi se max mana zvýšila o 20. \n";}
        }
    }
    else if(item != "Placeholder"){
        player.health += items[item][0];
        player.attack += items[item][2];
        player.mana += items[item][3];
        player.max_mana += items[item][4];
        setColor("Cyan");
        cout << "Úspěšně jste použili " << item << endl;
    }
    if(player.mana > player.max_mana){player.mana = player.max_mana;}
    if(player.health > player.max_health){player.health = player.max_health;}
    return "Nic";
}

void usporadatInventar(string inventar[10], int pocet){
    int check = 0; // Pomocná proměnná, pokud 0, tak se nic neděje, pokud 1, začne posouvat všechny následující itemy dopředu
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
    } else if(pocet == 10){ setColor("Yellow"); cout << "V inventáři máte moc itemů, nové itemy nemohou být přidány dokud si inventář nevyprázdníte \n"; }
    return 0;
}

void odeberPredmet(string inventar[], int &pocet, int poradi){
    if( poradi > 0 && poradi < 11){
        inventar[poradi-1] = "Nic";
        usporadatInventar(inventar, pocet);
        pocet--;
    } else {setColor("Yellow"); cout << "Neplatné pořadí, zkuste to znovu \n";}
}

void pouzijPredmet(Player &player, int &pocet, int idx){
    if(player.inventory[idx] == "Nic"){setColor("Yellow"); cout << "Daný index nedrží žádný item \n";}
    else {
        player.inventory[idx] = stats_update(player.inventory[idx], player);
        usporadatInventar(player.inventory, pocet);
        pocet--;
    }
}

void vypisInventar(string inventar[], int pocet){
    cout << "Itemy v inventáři: \n";
    for (int i=0; i<pocet; i++){ cout << inventar[i] << "  |  "; }
    cout << endl;
}


int inventar(Player &player, string pridat){
    string select, placeholder="Placeholder";
    int akce, pocet=10, select_int;
    bool running = true;
    for(int i=0; i<10; i++){if(player.inventory[i] == "Nic"){pocet=i; break;}} // Zjišťování počet itemů v inventáři

    if(pridat == "Krádež"){
        if(pocet == 0){return 0;}
        odeberPredmet(player.inventory, pocet, pocet-1);
        return 1;
    }
    if(pridat != "Nic"){return pridejPredmet(player.inventory, pocet, pridat);}

    while(running){
        setColor("Magenta");
        cout << "------------------------------------------------------------------------------------------------------------\n";
        cout << "Co chcete udělat? 1 - Odebrat předmět; 2 - Použít předmět; 3 - Zobrazit inventář; 4 - Ukončit \n";
        get_int(akce);

        switch(akce){
            case 1:
                if(pocet <= 0){pocet = 0; setColor("Yellow"); cout << "V inventáři není nic, co byste mohli odstranit \n"; break;}
                cout << "Zadejte pořadí itemu, který chcete odstranit (od 1); Aktuální počet itemů --> " << pocet << ": ";
                get_int(select_int);
                odeberPredmet(player.inventory, pocet, select_int);
                break;
            case 2:
                cout << "Zadejte index itemu v inventáři, který chcete použít (od 1): ";
                get_int(select_int);
                if(select_int < 1 || select_int > 10){
                    setColor("Yellow");
                    cout << "Tento index neexistuje. \n";
                }
                select_int--;
                pouzijPredmet(player, pocet, select_int);
                break;
            case 3:
                vypisInventar(player.inventory, pocet);
                break;
            case 4:
                running = false;
                break;
            default:
                cout << "Neplatný příkaz, zkuste to znovu \n";
        }
        wait(1);
    }

    return 0;
}