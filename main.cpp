#include <iostream>
#include <unordered_map>
using namespace std;

// Stats hráče
struct Player {
    int max_health;
    int health;
    int max_mana;
    int mana;
    int attack;

    int money;
    int inventory[10];
};

// Inicializace tříd (classes) {Životy, Škody, Mana}
unordered_map<string, array<int, 3> > Classes = {
    {"Válečník", {120, 20, 0}},
    {"Mág", {70, 10, 100}},
    {"Zloděj", {85, 15, 30}},
    {"Paladin", {100, 18, 60}}
};

// Funkce na přeměnu řetězce na malá písmena
string lower(string &input){
    for(char &c : input){
        // static_cast<unsigned char> použito pro správné chování funkce tolower(), \
           která očekává nezápornou hodnotu typu char v ASCII tabulce
        c = tolower(static_cast<unsigned char>(c));
    }
    return input;
}

int main(){
    Player player;
    string choice;
    char enter;

    cout << """ Vítejte v teto skvělé RPG hře, kde budete objevovat vesnice, \
bojovat proti monstrům, a bránit se proti bossům. Jako první si vyberte třídu. \
Pro pokračování stiskněte klávesu Enter. """;
    cin >> enter;
    while(true){
        cout << "--------- \n";
        cout << "Třídy na výběr: Válečník; Mág; Zloděj; Paladin \n";
        cout << "Napište jméno třídy, kterou si chcete vybrat či se o ní dozvědět více. ";
        cin >> choice;
        lower(choice);
        if(choice == "válečník"){
            cout << "Tato třída se specializuje na útok zblízka. Má nejvíce životů \
a dělá nejvíce škody zblízka, avšak nemá žádnou manu. \n Životy: 120; Škody: 20; Mana: 0 \n";
        } else if(choice == "mág"){
            cout << "Tato třída vyniká v kouzlech, jelikož má vysoký počet many a speciální schopnosti. \
Nicméně na útok zblízka se moc nehodí. \n Životy: 70; Škody: 10; Mana: 100 \n";
        } else if(choice == "zloděj"){
            cout << "Pokud chcete decentní útok zblízka, ale také kouzlení, tato třída je pro vás. \
Její speciální schopnosti vám také pomohou. \n Životy: 85; Škody: 15; Mana: 30 \n";
        } else if(choice == "paladin"){
            cout << "Tato třída vám bude vyhovovat pokud chcete spolehlivé healovací schopnosti. \
Má decentní útok i manu. Životy: 100; Škody: 18; Mana: 60 \n";
        } else {cout << "Vámi zadaná třída neexistuje, zkuste to znovu. \n --- \n"; continue;}

        player.max_health = Classes[choice][0];
        player.attack = Classes[choice][1];
        player.max_mana = Classes[choice][2];
        cout << "--- \n";
        cout << "Chcete si opravdu vybrat tuto třídu? (Ano/Ne): ";
        cin >>  choice;

        if (lower(choice) == "ano"){break;}
    }

    

    return 0;
}