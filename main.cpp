#include <iostream>
#include <unordered_map>
#include <array>
#include <string>
#include "inventory.cpp" // Soubor C++ pro manipulaci s inventářem, momentálně ještě nedokončené
using namespace std;

// Stats hráče
struct Player {
    int max_health;
    int health;
    int max_mana;
    int mana;
    int attack;

    int money;
    string inventory[10];
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

// Funkce na budoucí bojování, příběh zatím není moc promyšlený a tak tu zatím nic není
int fight(string entity, Player &player, array<int, 2> stats, array<int, 5> abilities){
    int choice;
    int health = stats[0];
    while (true){
        // Akce hráče
        cout << "-----";
        cout << "Vaše životy: " << player.health << ", vaše mana: " << player.mana << endl;
        cout << "Životy monstra: " << stats[0] << endl;
        cout << "Jakou akci chcete udělat? \n 1) Zaútočit 2) Kouzlit 3) Použít item v inventáři 4) Utéct: ";
        cin >> choice;
        if(choice == 4){return 2;}
        switch(choice){
            case 1:
                health -= player.attack;
                cout << "Zaútočil jste na monstrum a ubral jste tomu " << player.attack << " životů.";
                break;
            case 2:
                break; // Zatím nic
            case 3:
                break; // Zatím nic
        }

        // Akce monstra
    }
}

void shop(string* inv, int &money){
    int pocet, akce;
    for(int i=0; i<10; i++){if(inv[i]=="Nic"){pocet=i; break;}}

    cout << "Vítejte v obchodě. Co si chcete koupit? \n";

    while(akce != 1){
        cout << "---- \n";
        cout << "1) Opustit obchod; 2) Popis itemů; 3) Lékárna - 10 zlatých; \
4) Elixír - 20 zlatých; 5) Nápoj náhody - 15 zlatých; 6) Magická koule - 25 zlatých \n";
        switch(akce){
            case 1:
                break;
            case 2:
                cout << "Lékárna: Regeneruje 10 životů; Elixír: Zvyšuje útok; Nápoj náhody: \
Dává náhodný efekt (dobrý či špatný); Magická koule: Zvyšuje maximální manu \n";
                break;
            case 3:
                if(money >= 10){
                    if(inventar(inv, money, money, "Lékárna") == 1){ // Money momentálně slouží jako placeholder
                        money -= 10;
                    }
                } else{
                    cout << "Nemáte dostatek peněz, zkuste to znovu až budete trochu bohatší. \n";
                }
                break;
            default:
                cout << "Zadejte platné číslo \n";
                break;
        }
    }
}

// Funkce na vstup do vesnice
void village(Player &player, int &money, int &health, int &max_health, int &mana, int &max_mana, int &attack){
    int town_choice;
    while(town_choice != 1){
        cout << "---";
        cout << "Peníze: " << money << "; Životy: " << health << "; Max životy: " << max_health << \
        "; Mana: " << mana << "; Max mana: " << max_mana << "; Útok: " << attack << endl;
        cout << "Co chcete dělat? Na výběr máte: \n 1) Odejít z vesnice a pokračovat ve hře; \
        2) Koupit si nějaký item do inventáře; 3) Otevřít a manipulovat s inventářem \n";
        cout << "Zvolte odpovídající číslo: ";
        cin >> town_choice;

        if(town_choice == 1){return;}
        else if(town_choice == 2){shop(player.inventory, player.money);}
        else if(town_choice == 3){inventar(player.inventory, player.health, player.attack, "Nic");}
    }
}

// Funkce na neúspěšné ukončení hry
void game_over(Player player){
    cout << "Prohráli jste";
}

int main(){
    Player player;
    string choice;
    char enter;
    int status;

    // Inicializace tříd (classes) {Životy, Škody, Mana}
    array<int, 3> warrior = {120, 20, 0};
    array<int, 3> mage = {70, 10, 100};
    array<int, 3> thief = {85, 15, 30};
    array<int, 3> paladin = {100, 18, 60};
    unordered_map<string, array<int, 3> > Classes;
    Classes["Válečník"] = warrior;
    Classes["Mág"] = mage;
    Classes["Zloděj"] = thief;
    Classes["Paladin"] = paladin;


    // Inicializace monster {Životy, Útok}
    array<int, 2> krysa = {150, 5};
    unordered_map<string, array<int, 2> > Monsters;
    Monsters["Jeskynní krysa"] = krysa;

    // Inicializace schopností monster
    unordered_map<string, array<int, 5> > Monster_abilities;

    cout << """ Vítejte v teto skvělé RPG hře, kde budete objevovat vesnice, \
bojovat proti monstrům, a bránit se proti bossům. Jako první si vyberte třídu. \
Pro pokračování stiskněte klávesu Enter. """;
    cin >> enter;
    while(true){
        cout << "---------- \n";
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

        // Přiřazení hodnot k hráči
        player.max_health = Classes[choice][0];
        player.attack = Classes[choice][1];
        player.max_mana = Classes[choice][2];
        cout << "--- \n";
        cout << "Chcete si opravdu vybrat tuto třídu? (Ano/Ne): ";
        cin >>  choice;

        if (lower(choice) == "ano"){break;}
    }
    cout << "----------\n";
    cout << "Skvěle, vybrali jste si třídu. Nyní se nacházíte v 1. vesnici. Zde můžete dělat pár akcí, \
jako doplňovat životy či vylepšovat maximální životy / manu / útok. V každé vesnici budete moct tyto akce \
opakovat neomezeně, dokud nezvolíte postup dále do hry. Ve všech případech budete moct otevřít svůj inventář \
pomocí vložení písmena 'I' místo dané akce. Ve vesnici to pak bude reprezentovat číslo, nicméně to bude napsané \
po každé návštěvě vesnice, takže se tím moc nemusíme zabývat. \n";

    village(player, player.money, player.health, player.max_health, player.mana, player.max_mana, player.attack);

    cout << "Teď když jste navštívili první vesnici, budete připraveni na první souboj. Nebojte, nebude to nic \
těžkého. Čeká vás souboj s jeskynní krysou. Toto monstrum je zajímavé svým vzhledem, nicméně moc škody nepáchá. \n";

    cout << "--------";
    cout << "Už se stmívá a chcete se schovat před špatným počasím. Jdete proto do jeskyně, abyste \
se tam do rána schovali. Bohužel nejste jediným stvořením, které se v jeskyni schovává. Pomocí pochodně \
v jeskyni uděláte světlo a objeví se velká krysa. 'Zde už bydlím já, bez boje mě nevyženete!' \n";
    cout << "----";
    cout << "V boji máte na výběr z několika akcí. Můžete zaútočit, kouzlit, použít item v inventáři nebo \
utéct z boje a vrátit se zpátky později. Monstra mají různé vlastnosti, avšak stále po vás budou útočit. \n";

    status = fight("Jeskynní krysa", player, Monsters["Jeskynní krysa"], Monster_abilities["Jeskynní krysa"]);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){ cout << "První souboj jste úspěšně zvládl, nyní se posuňme dál. \n"; }
    else if(status == 2){}

    

    return 0;
}
