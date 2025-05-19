#include <iostream>
#include <unordered_map>
#include <array>
#include <string>
#include <ctime>
#include <cstdlib>
#include "inventory.cpp"
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
int fight(string entity, Player &player, array<int, 2> stats, vector<string> abilities){
    int choice;
    int health = stats[0];
    int number_of_abilities = abilities.size();
    int random_number;
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

        // Akce monstra na bázi náhodného čísla
        random_number = rand() % number_of_abilities + 1;
        if(abilities[random_number] == "..."){
            // ...
        }
    }
}

void shop(string* inv, int &money){
    int pocet, akce=0;
    string placeholder = "Placeholder";
    for(int i=0; i<10; i++){if(inv[i]=="Nic"){pocet=i; break;}}

    cout << "Vítejte v obchodě. Co si chcete koupit? \n";

    while(akce != 1){
        cout << "---- \n";
        cout << "1) Opustit obchod; 2) Popis itemů; 3) Lékárna - 10 zlatých; \
4) Elixír - 20 zlatých; 5) Nápoj náhody - 15 zlatých; 6) Magická koule - 25 zlatých \n";
        cout << "Zadejte odpovídající číslo: ";
        cin >> akce;
        switch(akce){
            case 1:
                break;
            case 2:
                cout << "Lékárna: Regeneruje 10 životů; Elixír: Zvyšuje útok o 10; Nápoj náhody: \
Dává náhodný efekt (dobrý či špatný); Magická koule: Zvyšuje maximální manu o 15 \n";
                break;
            case 3:
                if(money >= 10){
                    if(inventar(inv, money, money, "Lékárna", placeholder) == 1){ // Money momentálně slouží jako placeholder
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
void village(Player &player){
    int town_choice = 0;
    string placeholder = "Placeholder";
    while(town_choice != 1){
        cout << "--- \n";
        cout << "Peníze: " << player.money << "; Životy: " << player.health << "; Max životy: " << player.max_health << \
        "; Mana: " << player.mana << "; Max mana: " << player.max_mana << "; Útok: " << player.attack << endl;
        cout << "Co chcete dělat? Na výběr máte: \n 1) Odejít z vesnice a pokračovat ve hře; \
2) Koupit si nějaký item do inventáře; 3) Otevřít a manipulovat s inventářem \n";
        cout << "Zvolte odpovídající číslo: ";
        cin >> town_choice;

        if(town_choice == 1){return;}
        else if(town_choice == 2){shop(player.inventory, player.money);}
        else if(town_choice == 3){inventar(player.inventory, player.health, player.attack, "Nic", placeholder);}
        else { cout << "Neplatný vstup, zkuste to znovu. \n"; }
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

    srand(time(0)); // Inicializace generátoru

    // Stats itemů {Životy, Útok, Mana}
    array<int, 3> medkit = {10, 0, 0};
    array<int, 3> elixir = {0, 10, 0};
    array<int, 3> ball = {0, 0, 15};
    unordered_map<string, array<int, 3> > items;
    items["lékárna"] = medkit;
    items["elixír"] = elixir;
    items["koule"] = ball;

    // Inicializace tříd (classes) {Životy, Škody, Mana}
    array<int, 3> warrior = {120, 20, 0};
    array<int, 3> mage = {70, 10, 100};
    array<int, 3> thief = {85, 15, 30};
    array<int, 3> paladin = {100, 18, 60};
    unordered_map<string, array<int, 3> > Classes;
    Classes["válečník"] = warrior;
    Classes["mág"] = mage;
    Classes["zloděj"] = thief;
    Classes["paladin"] = paladin;


    // Inicializace monster {Životy, Útok}
    array<int, 2> krysa = {150, 5};
    unordered_map<string, array<int, 2> > Monsters;
    Monsters["Jeskynní krysa"] = krysa;

    // Inicializace schopností monster
    unordered_map<string, vector<string> > Monster_abilities;

    cout << """ Vítejte v teto skvělé RPG hře, kde budete objevovat vesnice, \
bojovat proti monstrům, a bránit se proti bossům. Jako první si vyberte třídu. \
Pro pokračování stiskněte klávesu Enter. """; // Pouze enter nefunguje, musí se zadat právě jedno písmeno (fix později)
    cin >> enter;
    while(true){
        cout << "---------- \n";
        cout << "Třídy na výběr: Válečník; Mág; Zloděj; Paladin \n";
        cout << "Napište jméno třídy, kterou si chcete vybrat či se o ní dozvědět více: ";
        cin >> choice;
        cout << "- \n";
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
        player.health = player.max_health;
        player.attack = Classes[choice][1];
        player.max_mana = Classes[choice][2];
        player.mana = player.max_mana;
        player.money = 20;
        cout << "--- \n";
        cout << "Chcete si opravdu vybrat tuto třídu? (Ano/Ne): ";
        cin >>  choice;

        if (lower(choice) == "ano"){break;}
    }
    cout << "----------\n";
    cout << "Skvěle, vybrali jste si třídu. Nyní se nacházíte v 1. vesnici. Zde můžete dělat pár akcí, \
jako doplňovat životy či vylepšovat maximální životy / manu / útok. V každé vesnici budete moct tyto akce \
opakovat neomezeně, dokud nezvolíte postup dále do hry. \n";

    village(player);
    cout << "--------\n";

    cout << "Teď když jste navštívili první vesnici, budete připraveni na první souboj. Nebojte, nebude to nic \
těžkého. Čeká vás souboj s jeskynní krysou. Toto monstrum je zajímavé svým vzhledem, nicméně moc škody nepáchá. \n";

    cout << "-------- \n";
    cout << "Už se stmívá a chcete se schovat před špatným počasím. Jdete proto do jeskyně, abyste \
se tam do rána schovali. Bohužel nejste jediným stvořením, které se v jeskyni schovává. Pomocí pochodně \
v jeskyni uděláte světlo a objeví se velká krysa. 'Zde už bydlím já, bez boje mě nevyženete!' \n";
    cout << "---- \n";
    cout << "V boji máte na výběr z několika akcí. Můžete zaútočit, kouzlit, použít item v inventáři nebo \
utéct z boje a vrátit se zpátky později. Monstra mají různé vlastnosti, avšak stále po vás budou útočit. \n";

    status = fight("Jeskynní krysa", player, Monsters["Jeskynní krysa"], Monster_abilities["Jeskynní krysa"]);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){ cout << "První souboj jste úspěšně zvládl, nyní se posuňme dál. \n"; }
    else if(status == 2){}

    

    return 0;
}
