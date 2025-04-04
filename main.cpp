#include <iostream>
using namespace std;

// Vytvoření objektu hráče (doufám že se to může)
struct Player {
    int health = 100;
    int attack = 5;
    int speed = 1;

    int money = 0;
    int inventory[10];
};

// Inicializace tříd (classes); Hodnoty jsou zatím jen placeholdery
int Classes[4][3] = {
    {150, 5, 2}, // Class 1
    {100, 10, 1}, // Class 2
    {90, 5, 5}, // Class 3
    {200, 1, 1} // Class 4
};

int main(){
    Player player;
    int choice;

    cout << """ Vítejte v teto skvělé RPG hře, kde budete objevovat vesnice, \
bojovat proti monstrům, a bránit se proti bossům. Jako první si vyberte třídu: """;
    cout << "--------- \n";
    cout << "Vyberte číslo 1-4: ";
    cin >> choice;

    player.health = Classes[choice-1][0];
    player.attack = Classes[choice-1][1];
    player.speed = Classes[choice-1][2];

    return 0;
}