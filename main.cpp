#include <iostream>
using namespace std;

// Stats hráče
struct Player {
    int max_health;
    int health;
    int max_mana;
    int mana;
    int attack;

    int money = 0;
    int inventory[10];
};

// Inicializace tříd (classes)
int Classes[4][3] = {
    {120, 20, 0}, // Válečník
    {70, 10, 100}, // Mág
    {85, 15, 30}, // Zloděj
    {100, 18, 60} // Paladin
};

int main(){
    Player player;
    string choice;
    char enter;

    cout << """ Vítejte v teto skvělé RPG hře, kde budete objevovat vesnice, \
bojovat proti monstrům, a bránit se proti bossům. Jako první si vyberte třídu. \
Pro pokračování stiskněte klávesu Enter.""";
    cin >> enter;
    cout << "--------- \n";
    while(true){
        cout << "Třídy na výběr: Válečník; Mág; Zloděj; Paladin \n";
        cout << "Napište jméno třídy, kterou si chcete vybrat či se o ní dozvědět více.";
        cin >> choice;
        if(choice == "Válečník"){

        } else if(choice == "Mág"){

        } else if(choice == "Zloděj"){

        } else if(choice == "Paladin"){

        } else {cout << "Vámi zadaná třída neexistuje, zkuste to znovu. \n"; continue;}

        cout << "Chcete si opravdu vybrat tuto třídu? (Ano/Ne): ";
        cin >>  choice;

        if (tolower(choice) == "Ano"){break;} // Nefunguje
    }

    return 0;
}