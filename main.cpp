#include <iostream>
#include <unordered_map>
#include "inventory.h"
using namespace std;

int fight(Player &player, unordered_map<string, array<int, 3> > actions, array<int, 2> stats, vector<string> abilities, int speed){
    int choice;
    int damage = player.attack;
    int monster_health = stats[0];
    int monster_attack = stats[1];
    int number_of_abilities = abilities.size();
    int random_number;
    int temporary_heal=0, temporary_damage=0, temporary_lifesteal=0, temporary_stun=0;

    setColor("Red");
    cout << "---------------BOJ----------------\n";

    while (true){
        // Akce hráče
        setColor("White");
        cout << "---------------\n";
        setColor("Cyan");
        if(temporary_heal > 0){player.health += temporary_heal; temporary_heal--;
            cout << "Z dočasného healu jste dostali " << temporary_heal+1 << " životů. \n";}
        if(temporary_lifesteal>0){monster_health -= 5; player.health += 5; temporary_lifesteal--;
            cout << "Z dočasného lifestealu jste monstru ubrali a získali 5 životů. \n";}
        if(temporary_damage > 0){damage = player.attack + temporary_damage; temporary_damage-=5;
            cout << "Díky dočasnému zvýšení útoku nyní děláte " << temporary_damage+5+player.attack << " škody. \n";}
        if (player.health > player.max_health){player.health = player.max_health;}
        wait(speed * 1);

        setColor("Green");
        cout << "--\n";
        cout << "Vaše životy: " << player.health << ", vaše mana: " << player.mana << ", váš útok: " << damage << endl;
        cout << "Životy monstra: " << monster_health << endl;
        setColor("White");
        cout << "Jakou akci chcete udělat? \n";
        for(int i=0; i<player.number_of_abilities; i++){cout << i+1 << ") " << player.abilities[i] << " ";}
        cout << player.number_of_abilities+1 << ") Otevřít inventář \n";
        setColor("Black");
        cout << "Zadejte odpovídající číslo: "; get_int(choice);
        choice--;

        setColor("Cyan");
        if(choice == player.number_of_abilities){ inventar(player, "Nic"); damage = player.attack + temporary_damage;}
        else if(player.abilities[choice] == "Normální útok"){
            monster_health -= damage;
            cout << "Zaútočili jste na monstrum a ubrali jste tomu " << damage << " životů. \n";
        }
        else if(player.abilities[choice] == "Hodně slabý heal" || player.abilities[choice] == "Slabý heal" \
                || player.abilities[choice] == "Silný heal" || player.abilities[choice] == "Hodně silný heal"){
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                player.health += actions[player.abilities[choice]][1];
                cout << "Použili jste heal a zvedly se vám životy o " << actions[player.abilities[choice]][1] << endl;
                if(player.health > player.max_health){player.health = player.max_health;}
            } else {setColor("Yellow"); cout << "Nemáte dostatek many na tuto akci. \n";}
        }
        else if(player.abilities[choice] == "Dočasné zvýšení útoku"){
            if(actions["Dočasné zvýšení útoku"][0] <= player.mana){
                player.mana -= actions["Dočasné zvýšení útoku"][0];
                temporary_damage = 15; cout << "Dočasně jste navýšili svůj damage \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "Dočasný heal"){
            if(actions["Dočasný heal"][0] <= player.mana){
                player.mana -= actions["Dočasný heal"][0];
                temporary_heal = 10; cout << "Dočasně se budete postupně healovat \n";
            } else {setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "Dočasný lifesteal"){
            if(actions["Dočasný lifesteal"][0] <= player.mana){
                player.mana -= actions["Dočasný lifesteal"][0];
                temporary_lifesteal = 7; cout << "Dočasně budete mít lifesteal \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "% škody"){
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                monster_health *= (1 - (float(damage) / 100));
                cout << "Ubrali jste monstru " << damage << "% škody a nyní má " << monster_health << " životů. \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        } else if(player.abilities[choice] == "Magický šíp"){
                monster_health -= damage * 2;
                cout << "Monstru jste ubrali dvojnásobek svého útoku (" << damage*2 << ") životů. \n";
        } 
        else{
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                player.health += actions[player.abilities[choice]][1];
                monster_health -= actions[player.abilities[choice]][2];
                cout << "Ubrali jste monstru " << actions[player.abilities[choice]][2] << " životů a \
získali jste " << actions[player.abilities[choice]][1] << " životů. \n";
                if(player.health > player.max_health){player.health = player.max_health;}
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }

        if(monster_health <= 0){return 1;}

        wait(speed * 1);


        cout << "--\n";
        setColor("Blue");
        if(temporary_stun > 0){
            temporary_stun--;
            cout << "Monstrum je ovlivněno dočasným omráčením a svůj tah vynechává \n";
            wait(speed * 1);
            continue;
        }

        // Akce monstra na bázi náhodného čísla
        random_number = rand() % number_of_abilities;
        if(abilities[random_number] == "Normální útok"){
            cout << "Monstrum útočí na hráče, hráč má o " << monster_attack << " HP méně. \n";
            player.health -= monster_attack;
        }
        else if(abilities[random_number] == "Hodně slabý heal"){
            cout << "Monstrum se healuje, monstrum má o 5 HP více. \n";
            monster_health += 5;
        } else if(abilities[random_number] == "Útok kladivem"){
            random_number = rand() % 2 + 1;
            if(random_number == 1){
                player.health -= 15;
                cout << "Trpaslík úspěšně použil útok kladivem, hráč má o 15 životů méně \n";
            } else if(random_number == 2){
                temporary_stun = 3;
                cout << "Trpaslík neúspěšně použil útok kladivem, je omráčen na 3 tahy \n";
            }
        } else if(abilities[random_number] == "Spin sekerou"){
            random_number = random() % 20 + 1;
            player.health -= random_number;
            temporary_stun = 1;
            cout << "Trpaslík použil spin sekerou, hráčovi bylo ubráno " << random_number << " životů a trpaslík je omráčen na 1 tah \n";
        }

        if(player.health <= 0){return 0;}

        wait(speed * 1);
    }
}

int double_fight(Player &player, unordered_map<string, array<int, 3> > actions, array<int, 2> stats1, array<int, 2> stats2, vector<string> abilities1, vector<string> abilities2, int speed){
    int choice; // Výběr akce
    int monster_select; // Výběr, na které monstrum použít akci
    int damage = player.attack;
    int monster_health1 = stats1[0];
    int monster_health2 = stats2[0];
    int monster_attack1 = stats1[1];
    int monster_attack2 = stats2[1];
    int number_of_abilities1 = abilities1.size();
    int number_of_abilities2 = abilities2.size();
    int monsters_alive;
    int random_number;
    int temporary_heal=0, temporary_damage=0, temporary_lifesteal=0, temporary_stun1=0, temporary_stun2=0;
    int player_stun = 0, temporary_poison=0, immunity1=0, immunity2=0;

    setColor("Red");
    cout << "---------------BOJ S 2 MONSTRY----------------\n";

    while(true){
        //Akce hráče
        setColor("White");
        cout << "---------------\n";
        setColor("Cyan");
        if(temporary_heal > 0){player.health += temporary_heal; temporary_heal--;
            cout << "Z dočasného healu jste dostali " << temporary_heal+1 << " životů. \n";}
        if(temporary_lifesteal>0){monster_health1 -= 5; monster_health2 -= 5; player.health += monsters_alive*5; temporary_lifesteal--;
            cout << "Z dočasného lifestealu jste každému monstru ubrali 5 životů a získali tím " << monsters_alive*5 << " životů. \n";}
        if(temporary_damage > 0){damage = player.attack + temporary_damage; temporary_damage-=5;
            cout << "Díky dočasnému zvýšení útoku nyní děláte " << temporary_damage+5+player.attack << " škody. \n";}
        if (player.health > player.max_health){player.health = player.max_health;}

        setColor("Blue");
        if(temporary_poison > 0){wait(speed * 1); player.health -= 1; temporary_poison--; cout << "Hráč kvůli dočasnému poisonu přichází o 1 život. \n";}
        wait(speed * 1);

        setColor("Yellow");
        if(immunity1>0 && monster_health1 > 0){cout << "1. monstrum je imunní  ";}
        if(immunity2>0 && monster_health2 > 0){cout << "2. monstrum je imunní";} cout << endl;

        setColor("Green");
        cout << "--\n";
        cout << "Vaše životy: " << player.health << ", vaše mana: " << player.mana << ", váš útok: " << damage << endl;
        if(monster_health1 > 0){cout << "Životy 1. monstra: " << monster_health1 << endl;}
        if(monster_health2 > 0){cout << "Životy 2. monstra: " << monster_health2 << endl;}
        wait(speed * 1);

        if(player_stun > 0){choice = -1; player_stun--; setColor("Yellow"); cout << "Jste omráčeni, nemůžete nic dělat. \n";}
        else{
            setColor("White");
            cout << "Jakou akci chcete udělat? \n";
            for(int i=0; i<player.number_of_abilities; i++){cout << i+1 << ") " << player.abilities[i] << " ";}
            cout << player.number_of_abilities+1 << ") Otevřít inventář \n";
            setColor("Black");
            do{ cout << "Zadejte odpovídající číslo: "; get_int(choice); } while(choice < 1 || choice > player.number_of_abilities+1);
            choice--;
        }
        setColor("Cyan");
        if(choice==-1){ /* Nic */}
        else if(choice == player.number_of_abilities){ inventar(player, "Nic"); damage = player.attack + temporary_damage; }
        else if(player.abilities[choice] == "Hodně slabý heal" || player.abilities[choice] == "Slabý heal" \
                || player.abilities[choice] == "Silný heal" || player.abilities[choice] == "Hodně silný heal"){
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                player.health += actions[player.abilities[choice]][1];
                cout << "Použili jste heal a zvedly se vám životy o " << actions[player.abilities[choice]][1] << endl;
                if(player.health > player.max_health){player.health = player.max_health;}
            } else {setColor("Yellow"); cout << "Nemáte dostatek many na tuto akci. \n";}
        }
        else if(player.abilities[choice] == "Dočasné zvýšení útoku"){
            if(actions["Dočasné zvýšení útoku"][0] <= player.mana){
                player.mana -= actions["Dočasné zvýšení útoku"][0];
                temporary_damage = 15; cout << "Dočasně jste navýšili svůj damage \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "Dočasný heal"){
            if(actions["Dočasný heal"][0] <= player.mana){
                player.mana -= actions["Dočasný heal"][0];
                temporary_heal = 10; cout << "Dočasně se budete postupně healovat \n";
            } else {setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "Dočasný lifesteal"){
            if(actions["Dočasný lifesteal"][0] <= player.mana){
                player.mana -= actions["Dočasný lifesteal"][0];
                temporary_lifesteal = 7; cout << "Dočasně budete mít lifesteal \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else{
            setColor("White");
            do{cout << "Na jaké monstrum chcete použít akci? (1/2): "; get_int(monster_select);} while(monster_select < 1 || monster_select > 2);
            setColor("Cyan");
            if((monster_select==1 && immunity1>0) || (monster_select==2 && immunity2>0)){
                setColor("Yellow");
                cout << "Toto monstrum je pro toto kolo imunní. Váš útok na toto monstrum proto nic nedělá. Na řadě je nyní monstrum. \n";
            }
            else if(player.abilities[choice] == "Normální útok"){
                if(monster_select == 1){monster_health1 -= damage;}
                else if(monster_select == 2){monster_health2 -= damage;}
                cout << "Monstru jste ubrali " << damage << " životů. \n";
            } else if(player.abilities[choice] == "% škody"){
                if(actions[player.abilities[choice]][0] <= player.mana){
                    player.mana -= actions[player.abilities[choice]][0];
                    if(monster_select == 1){monster_health1 *= (1 - float(damage) / 100);}
                    else if(monster_select == 2){monster_health2 *= (1- float(damage) / 100);}
                    cout << "Ubrali jste monstru " << float(damage)/100 << "% životů. \n";
                } else{setColor("Yellow"); cout << "Nemáte dostatek many. \n";}
            } else if(player.abilities[choice] == "Magický šíp"){
                if(monster_select == 1){monster_health1 -= damage * 2;}
                else if(monster_select == 2){monster_health2 -= damage * 2;}
                cout << "Monstru jste ubrali dvojnásobek svého útoku (" << damage*2 << ") životů. \n";
            } else{
                if(actions[player.abilities[choice]][0] <= player.mana){
                    player.mana -= actions[player.abilities[choice]][0];
                    player.health += actions[player.abilities[choice]][1];
                    if(monster_select == 1){monster_health1 -= actions[player.abilities[choice]][2];}
                    else if(monster_select == 2){monster_health2 -= actions[player.abilities[choice]][2];}
                    cout << "Ubrali jste monstru " << actions[player.abilities[choice]][2] << " životů a \
získali jste " << actions[player.abilities[choice]][1] << " životů. \n";
                    if(player.health > player.max_health){player.health = player.max_health;}
                } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
            }
        }

        monsters_alive = 0;
        if(monster_health1 > 0){monsters_alive++;}if(monster_health2 > 0){monsters_alive++;}
        if(monsters_alive==0){return 1;}
        if(immunity1 > 0){immunity1--;}if(immunity2 > 0){immunity2--;}
        wait(speed * 1);

        //Akce obou monster
        for(int i=1; i<3; i++){
            if(i==1 && monster_health1 <= 0){continue;}
            else if(i==2 && monster_health2 <= 0){continue;}
            setColor("Black");
            cout << i << ". monstrum je na řadě \n";
            wait(speed * 1);
            setColor("Blue");
            if(i==1 && temporary_stun1>0){temporary_stun1--; cout << "Monstrum je ovlivněno dočasným omráčením a svůj tah vynechává \n"; continue;}
            else if(i==2 && temporary_stun2>0){temporary_stun2--; cout << "Monstrum je ovlivněno dočasným omráčením a svůj tah vynechává \n"; continue;}

            if(i==1){random_number = rand() % number_of_abilities1;}
            else if(i==2){random_number = rand() % number_of_abilities2;}

            if((i==1 && abilities1[random_number] == "Normální útok") || (i==2 && abilities2[random_number] == "Normální útok")){
                if(i==1){player.health -= stats1[1];}
                else if(i==2){player.health -= stats2[1];}
                cout << "Monstrum zaútočilo na hráče, hráč přichází o ";
                if(i==1){cout << stats1[1];} else if(i==2){cout << stats2[1];} cout << " životů \n"; 

            } else if((i==1 && abilities1[random_number] == "Slabý heal") || (i==2 && abilities2[random_number] == "Slabý heal")){
                if(i==1){monster_health1 += 10;} else if(i==2){monster_health2 += 10;}
                cout << "Monstrum dostává heal. Získá tím 10 životů. \n";
            } else if((i==1 && abilities1[random_number] == "Hodně slabý heal") || (i==2 && abilities2[random_number] == "Hodně slabý heal")){
                if(i==1){monster_health1 += 5;} else if(i==2){monster_health2 += 5;}
                cout << "Monstrum dostává heal. Získá tím 5 životů. \n";
            } else if((i==1 && abilities1[random_number] == "Krve sání") || (i==2 && abilities2[random_number] == "Krve sání")){
                player.health -= 5;
                if(i==1){monster_health1 += 5;} else if(i==2){monster_health2 += 5;}
                cout << "Monstrum hráčovi vysálo 5 životů, které získává ke svým vlastním životům. \n";

            } else if((i==1 && abilities1[random_number] == "Činely clap") || (i==2 && abilities2[random_number] == "Činely clap")){
                random_number = rand() % 2 + 1;
                if(random_number == 1){
                    player_stun = 1;
                    cout << "Nestvůra vás omráčila klapnutím svými činely, jedno kolo nemůžete nic dělat. \n";
                } else if(random_number == 2){
                    if(i==1){temporary_stun2 = 1;} else if(i==2){temporary_stun1 = 1;}
                    cout << "Nestvůra se vás pokusila omráčit pomocí činel, avšak se moc netrefila a místo toho omráčila druhé monstrum. \n";
                }

            } else if((i==1 && abilities1[random_number] == "Kousnutí") || (i==2 && abilities2[random_number] == "Kousnutí")){
                player.health -= 3; temporary_poison = 2;
                cout << "Nestvůra vás kousla. Máte o 3 životy méně a dostanete 1 škodu na začátku příštích 2 kol. \n";

            } else if((i==1 && abilities1[random_number] == "Houslový play") || (i==2 && abilities2[random_number] == "Houslový play")){
                if(i==1){temporary_stun2 = 2; monster_health2 -= 5;} else if(i==2){temporary_stun1 = 2; monster_health1 -= 5;}
                player.health -= 5; player_stun = 1;
                cout << "Houslista se pustil do svého obávaného hraní. Jak vy, tak druhé monstrum utrpíte velkou sluchovou škodu. Jste \
omráčeni na 1 tah, druhé monstrum na 2 tahy. Také ubere vám i druhému monstru 5 životů. To je vskutku dobrý houslista. \n";
                wait(speed * 2);

            } else if((i==1 && abilities1[random_number] == "Činelový štít") || (i==2 && abilities2[random_number] == "Činelový štít")){
                if(i==1){immunity1 = 1;} else if(i==2){immunity2 = 0;}
                cout << "Monstrum se brání činelovým štítem: dostává imunitu na 1 tah, avšak může stále provádět akce. \n";

            } else if((i==1 && abilities1[random_number] == "Houslový slam") || (i==2 && abilities2[random_number] == "Houslový slam")){
                player.health -= 5;
                if(i==1){monster_health2 -= 5; temporary_stun1 = 1;} else if(i==2){monster_health1 -= 5; temporary_stun2 = 1;}
                cout << "Houslista hodí svými houslemi o zem a třísky z těchto houslí uberou jak vám tak druhému monstru 5 životů. \
Houslista je ze svých rozbitých houslích v depresích a tak na 1 tah nic nedělá. (Toto však bohužel neznamená, že housle už nemůže použít.) \n";
            } else if((i==1 && abilities1[random_number] == "Bodnutí mečem") || (i==2 && abilities2[random_number] == "Bodnutí mečem")){
                player.health -= 15; temporary_poison = 2;
                cout << "Strážný vás bodnul mečem. Hned dostáváte 15 životů dolů a 1 život dolů v příštích 2 tazích. \n";
            } else if((i==1 && abilities1[random_number] == "Střela z kuše") || (i==2 && abilities2[random_number] == "Střela z kuše")){
                random_number = rand() % 2 + 1;
                if(random_number == 2){if(i==1){temporary_stun2 = 1;} else if(i==2){temporary_stun1 = 1;}}
                player_stun = 1; player.health -= 3;
                cout << "Strážný vystřelil z kuše. Jste omráčeni na jedno kolo a ztrácíte 3 životy. \n";
                if(random_number == 2){cout << "Střela z kuše také zasáhla druhého strážného, ten je omráčen na 1 kolo. \n";}
            } else if(i==1 && abilities1[random_number] == "Bodnutí dýkou"){
                player.health -= 10; temporary_poison = 5;
                cout << "Lupič vás bodl dýkou. 10 instantní damage a 1 další v 5 příštích kolech. \n";
            } else if(i==2 && abilities2[random_number] == "Výstřel revolverem"){
                cout << "Lupič se pokouší vystřelit z revolveru - jen jedna z komor obsahuje náboj. \n";
                random_number = rand() % 6 + 1;
                if(random_number == 1){
                    player.health -= 40; player_stun = 1;
                    temporary_stun1 = 2;
                    cout << "Lupič vystřelil ze správné komory! Hráč přichází o 40 životů a je omráčen na 1 tah. Druhý lupič je \
také omráčen, a to na 2 tahy. \n";
                } else {cout << "Lupičovi se nepodařilo vystřelit. Náboj byl v jiné komoře. \n";}
            } else if((i==1 && abilities1[random_number] == "Krádež") || (i==2 && abilities2[random_number] == "Krádež")){
                if(inventar(player, "Krádež") == 1){ cout << "Lupič vám ukradl item z inventáře \n"; }
                else{
                    random_number = rand() % 2 + 1;
                    if(random_number == 1){ player.health -= 5; cout << "Lupič vám ukradl 5 životů. \n"; }
                    else if(random_number == 2){ player.mana -= 5; cout << "Lupič vám ukradl 5 many. \n"; }
                    if(i==1){monster_health1 += 5;} else if(i==2){monster_health2 += 5;}
                    cout << "Lupič získává 5 životů za ukradené staty. \n";
                }
            }

            if(player.health <= 0){return 0;}
            wait(speed * 1);
        }
    }
}

int triple_fight(Player &player, unordered_map<string, array<int, 3> > actions, array<int, 2> stats1, array<int, 2> stats2, array<int, 2> stats3, vector<string> abilities1, vector<string> abilities2, vector<string> abilities3, int speed){
    int choice; // Výběr akce
    int monster_select; // Výběr, na které monstrum použít akci
    int damage = player.attack;
    int monster_health1 = stats1[0];
    int monster_health2 = stats2[0];
    int monster_health3 = stats3[0];
    int monster_attack1 = stats1[1];
    int monster_attack2 = stats2[1];
    int monster_attack3 = stats3[1];
    int number_of_abilities1 = abilities1.size();
    int number_of_abilities2 = abilities2.size();
    int number_of_abilities3 = abilities3.size();
    int monsters_alive;
    int random_number;
    int temporary_heal=0, temporary_damage=0, temporary_lifesteal=0, temporary_stun1=0, temporary_stun2=0, temporary_stun3=0;
    int temporary_poison=0, immunity1=0, immunity2=0, immunity3=0, player_stun=0;

    setColor("Red");
    cout << "---------------BOJ S 3 MONSTRY----------------\n";

    while(true){
        //Akce hráče
        setColor("White");
        cout << "---------------\n";
        setColor("Cyan");
        if(temporary_heal > 0){player.health += temporary_heal; temporary_heal--;
            cout << "Z dočasného healu jste dostali " << temporary_heal+1 << " životů. \n";}
        if(temporary_lifesteal>0){monster_health1 -= 5; monster_health2 -= 5; monster_health3 -= 5; player.health += monsters_alive*5; \
        temporary_lifesteal--; cout << "Z dočasného lifestealu jste každému monstru ubrali 5 životů a získali tím " << monsters_alive*5 << " životů. \n";}
        if(temporary_damage > 0){damage = player.attack + temporary_damage; temporary_damage-=5;
            cout << "Díky dočasnému zvýšení útoku nyní děláte " << temporary_damage+5+player.attack << " škody. \n";}
        if (player.health > player.max_health){player.health = player.max_health;}
        wait(speed * 1);
        setColor("Blue");
        if(temporary_poison > 0){wait(speed * 1); player.health -= 1; temporary_poison--; cout << "Hráč kvůli dočasnému poisonu přichází o 1 život. \n";}

        setColor("Yellow");
        if(immunity1>0 && monster_health1 > 0){cout << "1. monstrum je imunní   ";}if(immunity2>0 && monster_health2 > 0)
        {cout << "2. monstrum je imunní    ";} if(immunity3>0 && monster_health3 > 0){cout << "3. Monstrum je imunní";} cout << endl;

        setColor("Green");
        cout << "--\n";
        cout << "Vaše životy: " << player.health << ", vaše mana: " << player.mana << ", váš útok: " << damage << endl;
        if(monster_health1 > 0){cout << "Životy 1. monstra: " << monster_health1 << endl;}
        if(monster_health2 > 0){cout << "Životy 2. monstra: " << monster_health2 << endl;}
        if(monster_health3 > 0){cout << "Životy 3. monstra: " << monster_health3 << endl;}

        if(player_stun <= 0){
            wait(speed * 1);
            setColor("White");
            cout << "Jakou akci chcete udělat? \n";
            for(int i=0; i<player.number_of_abilities; i++){cout << i+1 << ") " << player.abilities[i] << " ";}
            cout << player.number_of_abilities+1 << ") Otevřít inventář \n";
            setColor("Black");
            do{ cout << "Zadejte odpovídající číslo: "; get_int(choice); } while(choice < 1 || choice > player.number_of_abilities+1);
            choice--;
        } else {player_stun--; choice = -1; setColor("Yellow"); cout << "Jste omráčeni, a proto toto kolo vynecháváte. \n";}

        setColor("Cyan");
        if(choice == -1){/* Nic */}
        else if(choice == player.number_of_abilities){ inventar(player, "Nic"); damage = player.attack + temporary_damage; }
        else if(player.abilities[choice] == "Hodně slabý heal" || player.abilities[choice] == "Slabý heal" \
                || player.abilities[choice] == "Silný heal" || player.abilities[choice] == "Hodně silný heal"){
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                player.health += actions[player.abilities[choice]][1];
                cout << "Použili jste heal a zvedly se vám životy o " << actions[player.abilities[choice]][1] << endl;
                if(player.health > player.max_health){player.health = player.max_health;}
            } else {setColor("Yellow"); cout << "Nemáte dostatek many na tuto akci. \n";}
        }
        else if(player.abilities[choice] == "Dočasné zvýšení útoku"){
            if(actions["Dočasné zvýšení útoku"][0] <= player.mana){
                player.mana -= actions["Dočasné zvýšení útoku"][0];
                temporary_damage = 15; cout << "Dočasně jste navýšili svůj damage \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}}
        else if(player.abilities[choice] == "Dočasný heal"){
            if(actions["Dočasný heal"][0] <= player.mana){
                player.mana -= actions["Dočasný heal"][0];
                temporary_heal = 10; cout << "Dočasně se budete postupně healovat \n";
            } else {setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "Dočasný lifesteal"){
            if(actions["Dočasný lifesteal"][0] <= player.mana){
                player.mana -= actions["Dočasný lifesteal"][0];
                temporary_lifesteal = 7; cout << "Dočasně budete mít lifesteal \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else{
            setColor("White");
            do{cout << "Na jaké monstrum chcete použít akci? (1/2/3): "; get_int(monster_select);} while(monster_select < 1 || monster_select > 3);
            setColor("Cyan");
            if((monster_select==1 && immunity1>0) || (monster_select==2 && immunity2>0) || (monster_select==3 && immunity3>0)){
                setColor("Yellow");
                cout << "Toto monstrum je pro toto kolo imunní. Váš útok na toto monstrum proto nic nedělá. Na řadě je nyní monstrum. \n";
            }
            else if(player.abilities[choice] == "Normální útok"){
                if(monster_select == 1){monster_health1 -= damage;}
                else if(monster_select == 2){monster_health2 -= damage;}
                else if(monster_select == 3){monster_health3 -= damage;}
                cout << "Monstru jste ubrali " << damage << " životů. \n";
            } else if(player.abilities[choice] == "Magický šíp"){
                if(monster_select == 1){monster_health1 -= damage * 2;}
                else if(monster_select == 2){monster_health2 -= damage * 2;}
                else if(monster_select == 3){monster_health3 -= damage * 2;}
                cout << "Monstru jste ubrali dvojnásobek svého útoku (" << damage*2 << ") životů. \n";
            } else if(player.abilities[choice] == "% škody"){
                if(actions[player.abilities[choice]][0] <= player.mana){
                    player.mana -= actions[player.abilities[choice]][0];
                    if(monster_select == 1){monster_health1 *= (1 - float(damage) / 100);}
                    else if(monster_select == 2){monster_health2 *= (1- float(damage) / 100);}
                    else if(monster_select == 3){monster_health3 *= (1- float(damage) / 100);}
                    cout << "Ubrali jste monstru " << float(damage)/100 << "% životů. \n";
                } else{setColor("Yellow"); cout << "Nemáte dostatek many. \n";}
            } else{
                if(actions[player.abilities[choice]][0] <= player.mana){
                    player.mana -= actions[player.abilities[choice]][0];
                    player.health += actions[player.abilities[choice]][1];
                    if(monster_select == 1){monster_health1 -= actions[player.abilities[choice]][2];}
                    else if(monster_select == 2){monster_health2 -= actions[player.abilities[choice]][2];}
                    else if(monster_select == 3){monster_health3 -= actions[player.abilities[choice]][2];}
                    cout << "Ubrali jste monstru " << actions[player.abilities[choice]][2] << " životů a \
získali jste " << actions[player.abilities[choice]][1] << " životů. \n";
                    if(player.health > player.max_health){player.health = player.max_health;}
                } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
            }
        }

        if(immunity1>0){immunity1--;}if(immunity2>0){immunity2--;}if(immunity3>0){immunity3--;}

        monsters_alive = 0;
        if(monster_health1 > 0){monsters_alive++;}if(monster_health2 > 0){monsters_alive++;}if(monster_health3 > 0){monsters_alive++;}
        if(monsters_alive == 0){return 1;}
        wait(speed * 1);

        //Akce všech monster
        for(int i=1; i<4; i++){
            if(i==1 && monster_health1 <= 0){continue;}
            else if(i==2 && monster_health2 <= 0){continue;}
            else if(i==3 && monster_health3 <= 0){continue;}
            setColor("Black");
            cout << i << ". monstrum je na řadě \n";
            wait(speed * 1);
            setColor("Blue");
            if(i==1 && temporary_stun1>0){ temporary_stun1--; cout << "Monstrum je ovlivněno dočasným omráčením a svůj tah vynechává \n"; continue;}
            else if(i==2 && temporary_stun2>0){ temporary_stun2--; cout << "Monstrum je ovlivněno dočasným omráčením a svůj tah vynechává \n"; continue;}
            else if(i==3 && temporary_stun3>0){ temporary_stun3--; cout << "Monstrum je ovlivněno dočasným omráčením a svůj tah vynechává \n"; continue;}

            if(i==1){random_number = rand() % number_of_abilities1;}
            else if(i==2){random_number = rand() % number_of_abilities2;}
            else if(i==3){random_number = rand() % number_of_abilities3;}
            if((i==1 && abilities1[random_number] == "Normální útok") || (i==2 && abilities2[random_number] == "Normální útok") || \
                    (i==3 && abilities3[random_number] == "Normální útok")){
                if(i==1){player.health -= stats1[1];}
                else if(i==2){player.health -= stats2[1];}
                else if(i==3){player.health -= stats3[1];}
                cout << "Monstrum zaútočilo na hráče, hráč přichází o ";
                if(i==1){cout << stats1[1];} else if(i==2){cout << stats2[1];} else if(i==3){cout << stats3[1];} cout << " životů \n"; 
            } else if((i==1 && abilities1[random_number] == "Jedovaté kousnutí") || (i==2 && abilities2[random_number] \
                        == "Jedovaté kousnutí") || (i==3 && abilities3[random_number] == "Jedovaté kousnutí")){
                player.health -= 5; temporary_poison = 3; cout << "Pavouk zaútočil nahráče jedovatým kousnutím. 5 životů dolů a poision na 3 tahy. \n";
            } else if((i==1 && abilities1[random_number] == "Pavučina") || (i==2 && abilities2[random_number] == "Pavučina") || \
                        (i==3 && abilities3[random_number] == "Pavučina")){
                if(i==1){temporary_stun1=2; immunity1=2;}else if(i==2){temporary_stun2=2; immunity2=2;}else if(i==3){temporary_stun3=2; immunity3=2;}
                cout << "Pavouk se zabalil do pavučiny na 2 tahy. Nyní na něj nelze útočit, avšak on nemůže provádět žádné akce. \n";
            } else if(i==1 && abilities1[random_number] == "Medvědí kousnutí"){
                player.health -= 10; temporary_poison = 3;
                cout << "Medvědice vás kousla. 10 životů dolů a 1 damage v příštích 3 tazích. \n";
                if(monster_health1 <= 20){wait(1); return 2;}
            } else if(i==1 && abilities1[random_number] == "Paw slam"){
                player_stun = 1; player.health -= 5;
                cout << "Medvědice vám dala facku s její tlapou. Jste omráčeni na 1 kolo a ztrácíte 5 životů. \n";
                if(monster_health1 <= 20){wait(1); return 2;}
            } else if(i==1 && abilities1[random_number] == "Mateřský heal"){
                monster_health2 += 40; monster_health3 += 40;
                cout << "Medvědice zpřístupňuje životy svým mláďatům. Obě z nich získávají 40 životů. \n";
                if(monster_health1 <= 20){wait(1); return 2;}
            }


            if(player.health <= 0){return 0;}
            wait(1 * speed);
        }
    }
}

int miniboss(Player &player, unordered_map<string, array<int, 3> > actions, array<int, 2> stats, vector<string> abilities, int speed){
    int choice, damage=player.attack, mb_health=stats[0], mb_attack=stats[1], number_of_abilities = abilities.size(), random_number;
    int temporary_heal=0, temporary_damage=0, temporary_lifesteal=0, temporary_stun=0;
    int temporary_poison=0, immunity=0, player_stun=0;

    setColor("Red");
    cout << "---------------MINIBOSS FIGHT-------------------\n";

    wait(speed * 1);
    while(true){
        // Akce minibosse
        setColor("Blue");
        cout << "-----\n";
        if(temporary_stun > 0){
            temporary_stun--;
            cout << "Miniboss je ovlivněn dočasným omráčením a tento tah vynechává. \n";
        } else{
            random_number = rand() % number_of_abilities;
            if(abilities[random_number] == "Normální útok"){
                player.health -= mb_attack;
                cout << "Miniboss útočí na hráče a ubírá mu " << mb_attack << " životů. \n";
            }
            else if(abilities[random_number] == "Spánek"){
                temporary_stun = 5; mb_health += 20;
                cout << "Obr uprostřed boje usnul. Bude spát ještě dalších 5 tahů. Tento spánek je velice prospěšný - obr získává 20 životů. \n";
            }
            else if(abilities[random_number] == "Body slam"){
                player_stun = 2; player.health -= 20;
                cout << "Obr vezme hráče a hodí s ním o zem. Hráč je omráčen na 2 tahy a ztrácí 20 životů. \n";
            }
            else if(abilities[random_number] == "Zakopnutí"){
                player.health -= 5;
                temporary_stun = 2;
                cout << "Obr zakopl na zem. Hráčovi to ubírá 5 životů a obr je omráčen na 2 tahy. \n";
            }
            else if(abilities[random_number] == "Rage mode"){
                random_number = rand() % 4 + 1;
                if(random_number == 1){
                    mb_attack += 15; mb_health *= 1.1;
                    cout << "Obr úspěšně aktivoval rage mode. Nyní má o 15 větší škody a o 10% víc životů. \n";
                } else{
                    mb_attack -= 5; mb_health *= 0.9; temporary_stun = 1;
                    cout << "Obr se neúspěšně pokusil aktivovat rage mode. Má o 5 menší škody, o 10% méně životů a je omráčen na 1 tah. \n";
                }
            }
            else if(abilities[random_number] == "Znehybnění"){
                temporary_stun = 1; immunity = 1;
                cout << "Golem znehybněl. Nemůže útočit na 1 tah, avšak je tento tah imunní. \n";
            }
            else if(abilities[random_number] == "Obětování"){
                mb_health *= 0.8; player.health *= 0.8;
                cout << "Golem si ubral 20% životů, aby mohl ubrat 20% životů hráčovi. \n";
            }
            else if(abilities[random_number] == "Odcizení"){
                player.health -= damage;
                cout << "Golem použil hráčův útok na hráče. \n";
            }
            else if(abilities[random_number] == "Regenerace"){
                mb_health *= 1.2;
                cout << "Golem si obnovil 20% životů. \n"; 
            }
        }

        wait(speed * 1);
        if(player.health <= 0){return 0;}

        setColor("Cyan");
        if(temporary_heal > 0){player.health += temporary_heal; temporary_heal--;
            cout << "Z dočasného healu jste dostali " << temporary_heal+1 << " životů. \n";}
        if(temporary_lifesteal>0){mb_health -= 5; player.health += 5; \
        temporary_lifesteal--; cout << "Z dočasného lifestealu jste minibossu ubrali 5 životů a získali tím 5 životů. \n";}
        if(temporary_damage > 0){damage = player.attack + temporary_damage; temporary_damage-=5;
            cout << "Díky dočasnému zvýšení útoku nyní děláte " << temporary_damage+5+player.attack << " škody. \n";}
        if (player.health > player.max_health){player.health = player.max_health;}
        wait(speed * 1);
        setColor("Yellow");
        if(immunity>0){setColor("Yellow"); cout << "Miniboss má dočasnou imunitu. \n";}
        setColor("Green");
        cout << "-----\n";
        cout << "Vaše životy: " << player.health << ", vaše mana: " << player.mana << ", váš útok: " << damage << endl;
        cout << "Životy minibosse: " << mb_health << endl;
        if(player_stun <= 0){
            for(int i=1; i<=player.number_of_abilities; i++){cout << i << ") " << player.abilities[i-1] << " ";} cout << player.number_of_abilities+1 << ") Inventář \n";
            setColor("Black"); do{cout << "Jakou akci chcete udělat? "; get_int(choice);} while(choice < 1 || choice > player.number_of_abilities+1);
            choice--;
        } else{choice = -1; setColor("Yellow"); player_stun--; cout << "Hráč je omráčen, toto kolo proto vynecháváte. \n";}
        setColor("Cyan");
        if(choice == -1){/* Nic */}
        else if(choice == player.number_of_abilities){ inventar(player, "Nic"); damage = player.attack + temporary_damage; }
        else if(player.abilities[choice] == "Hodně slabý heal" || player.abilities[choice] == "Slabý heal" \
                || player.abilities[choice] == "Silný heal" || player.abilities[choice] == "Hodně silný heal"){
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                player.health += actions[player.abilities[choice]][1];
                cout << "Použili jste heal a zvedly se vám životy o " << actions[player.abilities[choice]][1] << endl;
                if(player.health > player.max_health){player.health = player.max_health;}
            } else {setColor("Yellow"); cout << "Nemáte dostatek many na tuto akci. \n";}
        }
        else if(player.abilities[choice] == "Dočasné zvýšení útoku"){
            if(actions["Dočasné zvýšení útoku"][0] <= player.mana){
                player.mana -= actions["Dočasné zvýšení útoku"][0];
                temporary_damage = 15; cout << "Dočasně jste navýšili svůj damage \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}}
        else if(player.abilities[choice] == "Dočasný heal"){
            if(actions["Dočasný heal"][0] <= player.mana){
                player.mana -= actions["Dočasný heal"][0];
                temporary_heal = 10; cout << "Dočasně se budete postupně healovat \n";
            } else {setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "Dočasný lifesteal"){
            if(actions["Dočasný lifesteal"][0] <= player.mana){
                player.mana -= actions["Dočasný lifesteal"][0];
                temporary_lifesteal = 7; cout << "Dočasně budete mít lifesteal \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(immunity <= 0){
            if(player.abilities[choice] == "Normální útok"){
                mb_health -= damage;
                cout << "Minibossu jste ubrali " << damage << " životů. \n";
            } else if(player.abilities[choice] == "Magický šíp"){
                mb_health -= damage * 2;
                cout << "Minibossu jste ubrali dvojnásobek svého útoku (" << damage*2 << ") životů. \n";
            } else if(player.abilities[choice] == "% škody"){
                if(actions[player.abilities[choice]][0] <= player.mana){
                    player.mana -= actions[player.abilities[choice]][0];
                    mb_health *= (1 - float(damage) / 100);
                    cout << "Ubrali jste minibossu " << float(damage) << "% životů. \n";
                } else{setColor("Yellow"); cout << "Nemáte dostatek many. \n";}
            } else{
                if(actions[player.abilities[choice]][0] <= player.mana){
                    player.mana -= actions[player.abilities[choice]][0];
                    player.health += actions[player.abilities[choice]][1];
                    mb_health -= actions[player.abilities[choice]][2];
                    cout << "Ubrali jste monstru " << actions[player.abilities[choice]][2] << " životů a \
získali jste " << actions[player.abilities[choice]][1] << " životů. \n";
                    if(player.health > player.max_health){player.health = player.max_health;}
                } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
            }
        } else{ setColor("Yellow"); cout << "Miniboss má dočasnou imunitu. Váš útok proto nic nedělá a nyní je na řadě miniboss. \n"; }

        if(immunity>0){immunity--;}

        if(mb_health <= 0){return 1;}
        wait(speed * 1);
    }
}

int bossfight(Player &player, unordered_map<string, array<int, 3> > actions, int speed){
    int boss_health = 300;
    int boss_attack = 5;
    int blooms = 1;
    bool activation = false, aggressive = false;
    int lastAttack = 3;
    int random_number;
    int number_of_attacks=0, bloomHP=0, spell_immunity=0, player_stun=0, burst_hit=0;

    int damage=player.attack, temporary_lifesteal=0, temporary_damage=0, temporary_heal=0;
    int choice, number_of_choices;

    vector<string> abilities = {"Stun", "Lifesteal", "Parazit", "Obrana", "Výstřel trnů", "Posilování", "Bloom damage"};

    setColor("Red");
    cout << "--------FINÁLNÍ SOUBOJ---------\n";
    wait(speed * 1);
    setColor("White");
    cout << "Květina se zatím zdá být v klidu, ale najednou slyšíte ozvěnu 'Mé jméno je Bloomshade'. Nevíte, co si o tom myslet, \
ale asi to nebude úplně jednoduchý boj. \n";
    wait(speed * 1);
    setColor("Yellow");
    cout << "Tip: Čím více budete útočit, tím více se kytka stává agresivní. \n";
    cout << "Tip: Pokud chcete kytku uklidnit, zkuste pár tahů neútočit. \n";
    wait(speed * 2);

    while(true){
        setColor("Red");
        cout << "-------------------\n";
        // Akce bosse
        setColor("Blue");
        if(activation == false && lastAttack == 0){
            activation = true;
            aggressive = true;
            cout << "Kytka vzrostla, nyní má dvojnásobnou výšku, co hráč. Asi bude bojovat zpět. \n";
            wait(speed * 1);
        }
        if(activation == false){ cout << "Kytka se nezdá, že by něco dělala. \n"; }
        else{
            cout << "Bloomshade ze svých květů dělá pasivní damage, hráčovi ubírá " << boss_attack << " životů. \n";
            if(aggressive == false && lastAttack == 0){
                aggressive = true;
                cout << "Kytka vzrostla, nyní má dvojnásobnou výšku, co hráč. Asi bude bojovat zpět. \n";
                wait(speed * 1);
            }
            if(lastAttack > 2){aggressive = false;}
            else if(lastAttack == 2){aggressive = false; cout << "Bloomshade se zklidnil, počet květů a škody je nižší. \n"; boss_attack = 5; blooms = 1;}
            else{aggressive = true;}
            if(aggressive == true){
                blooms *= 2; boss_attack += 5;
                setColor("Yellow");
                cout << "-----\n";
                cout << "Narůstají květy a damage bosse \n";
                cout << "Počet květů: " << blooms << "; Attack bosse: " << boss_attack << endl;

                setColor("Blue");
                random_number = rand() % abilities.size();
                
                if(abilities[random_number] == "Stun"){
                    player_stun = 1; player.health -= 2;
                    cout << "Bloomshade hráče obrosty svými listy a kořeny. Hráč se na jedno kolo nemůže hnout, nemůže tedy \
provádět žádné akce. Hráč také ztrácí 2 životy. \n";
                }
                else if(abilities[random_number] == "Lifesteal"){
                    player.health -= 10; boss_health += 10;
                    player.attack -= 1; boss_attack += 1; damage = player.attack + temporary_damage;
                    cout << "Bloomshade si pomocí kořenů od hráče vzal 10 životů a 1 útok. \n";
                }
                else if(abilities[random_number] == "Parazit"){
                    bloomHP += 10; boss_health -= 10;
                    cout << "Bloomshade oživuje malý květ na hráčovi, přidává mu 10 životů. Tyto životy jsou odečteny od jeho životů. \n";
                }
                else if(abilities[random_number] == "Obrana"){
                    spell_immunity = 3;
                    cout << "Bloomshade se obalí v pylu a zakazuje všechny akce vyžadující manu na 3 kola. \n";
                }
                else if(abilities[random_number] == "Výstřel trnů"){
                    for(int i=0; i<6; i++){
                        random_number = rand() % 4;
                        if (random_number == 1){
                            player.health -= 5;
                            burst_hit++;
                        }
                    }
                    cout << "Bloomshade vystřeluje trny jako ze samopalu. Z 6 trnů jich " << burst_hit << " úspěšně trefí a hráč \
dostává " << burst_hit * 5 << " škody. \n";
                    burst_hit=0;
                }
                else if(abilities[random_number] == "Posilování"){
                    random_number = rand() % 4;
                    if(random_number == 3){
                        boss_attack += number_of_attacks * 3;
                        cout << "Bloomshade posiluje svůj attack, za každý hráčův tah, kdy zaútočil, si přidává 3 útoku. Celkem \
tedy +" << number_of_attacks * 3 << "útoku. \n";
                    }
                    else{
                        boss_attack -= 5; damage += 5;
                        cout << "Bloomshade se neúspěšně pokusil o posilování útoku. Hráčovi předává 5 útoku. \n";
                    }
                }
                else if(abilities[random_number] == "Bloom damage"){
                    player.health -= blooms;
                    cout << "Bloomshade vysílá své květy do útoku! Za každý květ hráč ztrácí 1 život (Dohromady " << blooms << " životů). \n";
                }
            }
        }

        if(player.health <= 0){return 0;}

        wait(speed * 1);
        setColor("White");
        cout << "\n------HRÁČŮV TAH-------\n\n";
        wait(speed * 1);

        if(bloomHP > 0){
            player.attack -= 2; boss_attack += 2; damage = player.attack + temporary_damage;
            setColor("Blue");
            cout << "Malý květ parazitující na hráčovi vám ubral 2 útoky a přidal je k Bloomshade. \n";
            setColor("Yellow");
            cout << "Malý květ HP: " << bloomHP << endl;
            wait(speed * 1);
        }

        lastAttack++;
        // Akce hráče
        setColor("Cyan");
        if(temporary_heal > 0){player.health += temporary_heal; temporary_heal--;
            cout << "Z dočasného healu jste dostali " << temporary_heal+1 << " životů. \n";}
        if(temporary_lifesteal>0){boss_health -= 5; player.health += 5; \
        temporary_lifesteal--; cout << "Z dočasného lifestealu jste Bloomshade ubrali 5 životů a získali tím 5 životů. \n";}
        if(temporary_damage > 0){damage = player.attack + temporary_damage; temporary_damage-=5;
            cout << "Díky dočasnému zvýšení útoku nyní děláte " << temporary_damage+5+player.attack << " škody. \n";}
        if (player.health > player.max_health){player.health = player.max_health;}
        wait(speed * 1);
        setColor("Yellow");
        if(spell_immunity>0){setColor("Yellow"); cout << "V tomto tahu nelze používat manu. \n";}
        setColor("Green");
        cout << "-----\n";
        cout << "Vaše životy: " << player.health << ", vaše mana: " << player.mana << ", váš útok: " << damage << endl;
        cout << "Životy bosse: " << boss_health << endl;
        if(player_stun <= 0){
            for(int i=1; i<=player.number_of_abilities; i++){cout << i << ") " << player.abilities[i-1] << " ";}
            cout << player.number_of_abilities+1 << ") Inventář ";
            if(bloomHP > 0){setColor("Yellow"); cout << player.number_of_abilities+2 << ") Zaútočit na malý květ";}
            cout << endl;
            if(bloomHP > 0){number_of_choices = player.number_of_abilities+2;}else{number_of_choices = player.number_of_abilities+1;}
            setColor("Black"); do{cout << "Jakou akci chcete udělat? "; get_int(choice);} while(choice < 1 || choice > number_of_choices);
            choice--;
        } else{choice = -1; setColor("Yellow"); player_stun--; cout << "Hráč je omráčen, toto kolo proto vynecháváte. \n";}
        setColor("Cyan");
        if(choice == -1){/* Nic */}

        else if(choice == player.number_of_abilities+1){bloomHP -= damage; if(bloomHP<0){bloomHP=0;} cout << "Malému květu na \
hráčovi jste ubrali " << damage << "životů. Nyní má " << bloomHP << " životů. \n";}
        else if(choice == player.number_of_abilities){ inventar(player, "Nic"); damage = player.attack + temporary_damage; }
        else if(player.abilities[choice] == "Normální útok"){
                        boss_health -= damage;
                        cout << "Minibossu jste ubrali " << damage << " životů. \n";
                        lastAttack = 0; number_of_attacks++;
        }
        else if(player.abilities[choice] == "Hodně slabý heal" || player.abilities[choice] == "Slabý heal"){
            player.health += actions[player.abilities[choice]][1];
            cout << "Použili jste heal a zvedly se vám životy o " << actions[player.abilities[choice]][1] << endl;
            if(player.health > player.max_health){player.health = player.max_health;}
        }

        else if(spell_immunity > 0){ setColor("Yellow"); cout << "V tomto kole nelze používat manu a proto vaše akce nic nedělá. Na tahu je Bloomshade. \n"; }
        else if(player.abilities[choice] == "Silný heal" || player.abilities[choice] == "Hodně silný heal"){
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                player.health += actions[player.abilities[choice]][1];
                cout << "Použili jste heal a zvedly se vám životy o " << actions[player.abilities[choice]][1] << endl;
                if(player.health > player.max_health){player.health = player.max_health;}
            } else {setColor("Yellow"); cout << "Nemáte dostatek many na tuto akci. \n";}
        }
        else if(player.abilities[choice] == "Dočasné zvýšení útoku"){
            if(actions["Dočasné zvýšení útoku"][0] <= player.mana){
                player.mana -= actions["Dočasné zvýšení útoku"][0];
                temporary_damage = 15; cout << "Dočasně jste navýšili svůj damage \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}}
        else if(player.abilities[choice] == "Dočasný heal"){
            if(actions["Dočasný heal"][0] <= player.mana){
                player.mana -= actions["Dočasný heal"][0];
                temporary_heal = 10; cout << "Dočasně se budete postupně healovat \n";
            } else {setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "Dočasný lifesteal"){
            if(actions["Dočasný lifesteal"][0] <= player.mana){
                player.mana -= actions["Dočasný lifesteal"][0];
                temporary_lifesteal = 7; cout << "Dočasně budete mít lifesteal \n";
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }
        else if(player.abilities[choice] == "Magický šíp"){
            boss_health -= damage * 2;
            cout << "Minibossu jste ubrali dvojnásobek svého útoku (" << damage*2 << ") životů. \n";
            lastAttack = 0;
        } else if(player.abilities[choice] == "% škody"){
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                boss_health *= (1 - float(damage) / 100);
                cout << "Ubrali jste Bloomshade " << float(damage) << "% životů. \n";
                lastAttack = 0; number_of_attacks++;
            } else{setColor("Yellow"); cout << "Nemáte dostatek many. \n";}
        } else{
            if(actions[player.abilities[choice]][0] <= player.mana){
                player.mana -= actions[player.abilities[choice]][0];
                player.health += actions[player.abilities[choice]][1];
                boss_health -= actions[player.abilities[choice]][2];
                cout << "Ubrali jste monstru " << actions[player.abilities[choice]][2] << " životů a \
získali jste " << actions[player.abilities[choice]][1] << " životů. \n";
                lastAttack = 0; number_of_attacks++;
                if(player.health > player.max_health){player.health = player.max_health;}
            } else{setColor("Yellow"); cout << "Nemáte dostatek many \n";}
        }

        if(spell_immunity>0){spell_immunity--;}

        if(boss_health <= 0){return 1;}
        wait(speed * 1);
    }
}

void shop(Player &player, int speed){
    int pocet, akce=0;
    string placeholder = "Placeholder";
    bool running = true;

    setColor("White");
    cout << "Vítejte v obchodě. Co si chcete koupit? \n";

    while(true){
        setColor("Black");
        cout << "---- \n";
        cout << "1) Opustit obchod; 2) Popis itemů; 3) Lékárna - 10 zlatých; \
4) Elixír - 20 zlatých; 5) Nápoj náhody - 15 zlatých; 6) Magická koule - 25 zlatých \
7) Lektvar zdraví - 30 zlatých; 8) Dobíječ many - 15 zlatých \n";
        setColor("White");
        cout << "Zadejte odpovídající číslo: ";
        get_int(akce);
        setColor("Cyan");
        switch(akce){
            case 1:
                return;
            case 2:
                setColor("Green");
                cout << "Lékárna: Regeneruje 15 životů; Elixír: Zvyšuje útok o 5; Nápoj náhody: \
Dává náhodný efekt (dobrý či špatný); Magická koule: Zvyšuje manu o 15; Lektvar zdraví: Zvýší maximální \
životy o 10; Dobíječ many: Zvýší manu o 50% zbývající many do max many (nejméně však 10) \n";
            break;
            case 3:
                if(player.money >= 10){
                    if(inventar(player, "Lékárna") == 1){
                        player.money -= 10;
                        cout << "Úspěšně jste si zakoupili lékárnu. \n";
                    }
                } else{
                    setColor("Yellow");
                    cout << "Nemáte dostatek peněz, zkuste to znovu až budete trochu bohatší. \n";
                }
                break;
            case 4:
                if(player.money >= 20){
                    if(inventar(player, "Elixír") == 1){
                        player.money -= 20;
                        cout << "Úspěšně jste si zakoupili elixír. \n";
                    }
                } else{
                    setColor("Yellow");
                    cout << "Nemáte dostatek peněz, zkuste to znovu až budete trochu bohatší. \n";
                }
                break;
            case 5:
                if(player.money >= 15){
                    if(inventar(player, "Nápoj náhody") == 1){
                        player.money -= 15;
                        cout << "Úspěšně jste si zakoupili nápoj náhody. \n";
                    }
                } else{setColor("Yellow");
                    cout << "Nemáte dostatek peněz, zkuste to znovu až budete trochu bohatší. \n";
                }
                break;
            case 6:
                if(player.money >= 25){
                    if(inventar(player, "Magická koule") == 1){
                        player.money -= 25;
                        cout << "Úspěšně jste si zakoupili magickou kouli. \n";
                    }
                } else{
                    setColor("Yellow");
                    cout << "Nemáte dostatek peněz, zkuste to znovu až budete trochu bohatší. \n";
                }
                break;
            case 7:
                if(player.money >= 30){
                    if(inventar(player, "Lektvar zdraví") == 1){
                        player.money -= 30;
                        cout << "Úspěšně jste si zakoupili lektvar zdraví. \n";
                    }
                } else{
                    setColor("Yellow");
                    cout << "Nemáte dostatek peněz, zkuste to znovu až budete trochu bohatší. \n";
                }
                break;
            case 8:
                if(player.money >= 15){
                    if(inventar(player, "Dobíječ many") == 1){
                        player.money -= 15;
                        cout << "Úspěšně jste si zakoupili dobíječ many. \n";
                    }
                } else{
                    setColor("Yellow");
                    cout << "Nemáte dostatek peněz, zkuste to znovu až budete trochu bohatší. \n";
                }
                break;
            default:
                setColor("Yellow");
                cout << "Zadejte platné číslo \n";
                break;
        }
        wait(speed * 1);
    }
}

// Funkce na vstup do vesnice
void village(Player &player, int speed){
    int town_choice = 0;
    while(town_choice != 1){
        setColor("Black");
        cout << "--- \n";
        setColor("Green");
        cout << "Peníze: " << player.money << "; Životy: " << player.health << "; Max životy: " << player.max_health << \
        "; Mana: " << player.mana << "; Max mana: " << player.max_mana << "; Útok: " << player.attack << endl;
        wait(speed * 1);
        setColor("White");
        cout << "Co chcete dělat? Na výběr máte: \n 1) Odejít z vesnice a pokračovat ve hře; \
2) Koupit si nějaký item do inventáře; 3) Otevřít a manipulovat s inventářem \n";
        wait(speed * 1);
        setColor("Black");
        cout << "Zvolte odpovídající číslo: ";
        get_int(town_choice);

        if(town_choice == 1){return;}
        else if(town_choice == 2){shop(player, speed);}
        else if(town_choice == 3){
            setColor("Magenta");
            inventar(player, "Nic");
        }
        else { setColor("Yellow"); cout << "Neplatný vstup, zkuste to znovu. \n"; }
    }
}

// Check na level-up
void new_level(Player &player, int speed){
    int random_number;
    if (player.experience / 10 > player.level){
        for(int i=player.level; i<player.experience/10; i++){
            player.level = player.experience / 10;
            do {random_number = rand() % 3 + 1;} while(player.name == "Válečník" && random_number == 2); // 1 = max životy, 2 = max mana, 3 = útok
            setColor("Cyan");
            cout << "Nová úroveň! \n";
            wait(speed * 1);
            if(random_number == 1){player.max_health += 10; cout << "Max životy " << player.max_health-10 << " -> " << player.max_health << endl;}
            else if(random_number == 2){player.max_mana += 15; cout << "Max mana " << player.max_mana-15 << " -> " << player.max_mana << endl;}
            else if(random_number == 3){player.attack += 5; cout << "Útok " << player.attack-5 << " -> " << player.attack << endl;}
            wait(speed * 1);
        }
    }
}

// Funkce na neúspěšné ukončení hry
void game_over(Player player){
    setColor("Red");
    cout << "---------------------Prohráli jste----------------------\n";
    cout << "Dosáhli jste " << player.level << " úrovně \n";
    cout << "Měli jste: \n";
    cout << player.money << " peněz" << endl;
    cout << player.mana << " many" << endl;
    cout << player.attack << " úrovně útoku" << endl;
    cout << player.level << ". úroveň a " << player.experience << " celkové zkušenosti" << endl;
}

int main(){
    Player player; // Struct hráče
    string choice; // Hráčův výběr jakožto string
    char enter; // Vstoupení do hry
    int status; // Vrácení hodnoty z jiných funkcí, např. fight()
    int speed; // Rychlost programu
    int number; // Všemožné použití s číslem

    srand(time(0)); // Inicializace generátoru

    // Nastavení inventáře hráče, aby všechny jeho hodnoty byly "Nic" - potřebné pro zjišťování velikosti
    for(int i=0; i<10; i++){player.inventory[i] = "Nic";}

    // Inicializace tříd (classes) {Životy, Škody, Mana, Počet schopností}
    unordered_map<string, array<int, 4> > Classes = {
        {"válečník", {150, 24, 0, 2}},
        {"mág", {90, 10, 175, 5}},
        {"zloděj", {85, 15, 30, 4}},
        {"paladin", {100, 12, 90, 5}}
    };

    // Inicializace monster a minibossů {Životy, Útok}
    unordered_map<string, array<int, 2> > Monsters = {
        {"Jeskynní krysa", {50, 3}},
        {"Trpaslík", {100, 5}},
        {"Netopýr", {80, 5}},
        {"Pavouk", {70, 7}},
        {"Nestvůra s činely", {50, 0}}, // Nemá schopnost normálního útoku
        {"Nestvůra s houslemi", {50, 0}}, // Nemá schopnost normálního útoku
        {"Strážný s mečem", {70, 10}},
        {"Strážný s kuší", {70, 5}},
        {"Obr", {200, 15}}, // Miniboss
        {"Vlk", {60, 7}},
        {"Červený motýl", {30, 5}},
        {"Modrý motýl", {30, 5}},
        {"Žlutý motýl", {30, 5}},
        {"Medvědice", {120, 0}}, // Nemá schopnost normálního útoku
        {"Medvídě", {40, 2}},
        {"Lupič s dýkou", {70, 0}},
        {"Lupič s revolverem", {70, 5}},
        {"Golem", {250, 20}} // Miniboss
    };

    // Inicializace schopností monster a minibossů
    unordered_map<string, vector<string> > Monster_abilities = {
        {"Jeskynní krysa", {"Normální útok", "Hodně slabý heal"}},
        {"Trpaslík", {"Normální útok", "Spin sekerou", "Útok kladivem"}},
        {"Netopýr", {"Normální útok", "Krve sání"}},
        {"Pavouk", {"Normální útok", "Jedovaté kousnutí", "Pavučina"}},
        {"Nestvůra s činely", {"Činely clap", "Kousnutí", "Činelový štít"}},
        {"Nestvůra s houslemi", {"Houslový play", "Kousnutí", "Houslový slam"}},
        {"Strážný s mečem", {"Normální útok", "Bodnutí mečem", "Slabý heal"}},
        {"Strážný s kuší", {"Normální útok", "Střela z kuše", "Slabý heal"}},
        {"Obr", {"Normální útok", "Spánek", "Body slam", "Zakopnutí", "Rage mode"}}, // Miniboss
        {"Vlk", {"Normální útok", "Slabý heal"}},
        {"Červený motýl", {"Normální útok", "Stun s životy"}},
        {"Modrý motýl", {"Normální útok", "Stun s manou"}},
        {"Žlutý motýl", {"Normální útok", "Stun s útokem"}},
        {"Medvědice", {"Medvědí kousnutí", "Paw slam", "Mateřský heal"}},
        {"Medvídě", {"Normální útok"}},
        {"Lupič s dýkou", {"Bodnutí dýkou", "Hodně slabý heal", "Krádež"}},
        {"Lupič s revolverem", {"Normální útok", "Výstřel revolverem", "Krádež"}},
        {"Golem", {"Normální útok", "Znehybnění", "Obětování", "Odcizení", "Regenerace"}} // Miniboss
    };

    unordered_map<string, array<string, 5> > class_abilities = {
        {"válečník", {"Normální útok", "Hodně slabý heal"}},
        {"mág", {"Normální útok", "Magický šíp", "Silný heal", "Dočasné zvýšení útoku", "% škody"}},
        {"zloděj", {"Normální útok", "Slabý heal", "Magický backstab", "Dočasný lifesteal"}},
        {"paladin", {"Normální útok", "Slabý heal", "Silný heal", "Hodně silný heal", "Dočasný heal"}}
    };

    // Inicializace akcí {Mana, Heal, Škody}
    unordered_map<string, array<int, 3> > actions = {
        {"Normální útok", {0, 0, 0}}, // Damage lze zvyšovat pomocí jiné akce a proto je na tuto akci vytvořena speciální podmínka
        {"Hodně slabý heal", {0, 5, 0}},
        {"Slabý heal", {0, 10, 0}},
        {"Magický šíp", {5, 0, 0}}, // Dvojnásobek útoku
        {"Silný heal", {10, 15, 0}},
        {"Hodně silný heal", {15, 20, 0}},
        {"Magický backstab", {5, 3, 20}},
        {"% škody", {20, 0, 0}},
        {"Dočasný heal", {10, 0, 0}},
        {"Dočasný lifesteal", {10, 0, 0}},
        {"Dočasné zvýšení útoku", {15, 0, 0}}
    };

    setColor("White");
    cout << "Jakou rychlostí chcete, aby se hra odehrávala? (0-2) (instantí-nejpomalejší), doporučeno 1: ";
    do{get_int(speed);} while(speed < 0 || speed > 2);

    setColor("Black");
    cout << """ Vítejte v teto skvělé RPG hře, kde budete objevovat vesnice, \
bojovat proti monstrům, a bránit se proti bossům. Jako první si vyberte třídu. \
Pro pokračování zadejte jakékoliv písmeno. """;
    cin >> enter;
    while(true){
        cout << "---------- \n";
        setColor("White");
        cout << "Třídy na výběr: Válečník; Mág; Zloděj; Paladin \n";
        wait(speed * 1);
        setColor("Black");
        cout << "Napište jméno třídy, kterou si chcete vybrat či se o ní dozvědět více: ";
        cin >> choice;
        cout << "- \n";
        lower(choice);
        setColor("White");
        if(choice == "válečník"){
            cout << "Tato třída se specializuje na útok zblízka. Má nejvíce životů \
a dělá nejvíce škody zblízka, avšak nemá žádnou manu. \n Životy: 150; Škody: 24; Mana: 0 \n";
        } else if(choice == "mág"){
            cout << "Tato třída vyniká v kouzlech, jelikož má vysoký počet many a speciální schopnosti. \
Nicméně na útok zblízka se moc nehodí. \n Životy: 90; Škody: 10; Mana: 175 \n";
        } else if(choice == "zloděj"){
            cout << "Pokud chcete decentní útok zblízka, ale také kouzlení, tato třída je pro vás. \
Její speciální schopnosti vám také pomohou. \n Životy: 85; Škody: 15; Mana: 30 \n";
        } else if(choice == "paladin"){
            cout << "Tato třída vám bude vyhovovat pokud chcete spolehlivé healovací schopnosti. \
Má decentní útok i manu. Životy: 100; Škody: 12; Mana: 90 \n";
        } else {cout << "Vámi zadaná třída neexistuje, zkuste to znovu. \n --- \n"; continue;}

        // Přiřazení hodnot k hráči
        player.name = choice;
        player.max_health = Classes[choice][0];
        player.health = player.max_health;
        player.attack = Classes[choice][1];
        player.max_mana = Classes[choice][2];
        player.mana = player.max_mana;
        player.money = 2000;
        player.experience = 0;
        player.level = 0;
        for(int i=0; i<5; i++){player.abilities[i] = class_abilities[choice][i];}
        player.number_of_abilities = Classes[choice][3];
        wait(speed * 2);
        setColor("Black");
        cout << "--- \n";
        cout << "Chcete si opravdu vybrat tuto třídu? (Ano/Ne): ";
        cin >>  choice;

        if (lower(choice) == "ano"){break;}
    }

    setColor("White");
    cout << "----------\n";
    cout << "Skvěle, vybrali jste si třídu. Nyní se nacházíte v 1. vesnici. Zde můžete dělat pár akcí, \
jako doplňovat životy či vylepšovat maximální životy / manu / útok. V každé vesnici budete moct tyto akce \
opakovat neomezeně, dokud nezvolíte postup dále do hry. \n";

    wait(speed * 3);
    village(player, speed);

    setColor("Black");
    cout << "--------\n";
    cout << "Teď když jste navštívili první vesnici, budete připraveni na první souboj. Nebojte, nebude to nic \
těžkého. Čeká vás souboj s jeskynní krysou. Toto monstrum je zajímavé svým vzhledem, nicméně moc škody nepáchá. \n";

    wait(speed * 3);

    setColor("White");
    cout << "-------- \n";
    cout << "Už se stmívá a chcete se schovat před špatným počasím. Jdete proto do jeskyně, abyste \
se tam do rána schovali. Bohužel nejste jediným stvořením, které se v jeskyni schovává. Pomocí pochodně \
v jeskyni uděláte světlo a objeví se velká krysa. 'Zde už bydlím já, bez boje mě nevyženete!' \n";
    wait(speed * 4);
    setColor("Black");
    cout << "---- \n";
    cout << "V boji máte na výběr z několika akcí. Můžete zaútočit, kouzlit či použít item v inventáři. \
Monstra mají různé vlastnosti, avšak stále po vás budou útočit. \n";
    wait(speed * 2);

    status = fight(player, actions, Monsters["Jeskynní krysa"], Monster_abilities["Jeskynní krysa"], speed);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){ setColor("Black"); cout << "První souboj jste úspěšně zvládl, nyní se posuňme dál. \n"; }

    setColor("Cyan");
    number = rand() % 2 + 1;
    player.experience += number * 5;
    new_level(player, speed);
    if (number == 2){
        player.money += 15;
        cout << "Z jeskynní krysy jste získali 15 zlatých \n";
    }

    wait(speed * 1);
    
    setColor("White");
    cout << "Nyní můžete bezpečně přespat v jeskyni. Po tom, co jste porazili jeskynní krysu, je v jeskyni zvlášťně \
ticho. Zítra je čas jít dále do jeskyně. \n";
    wait(speed * 3);

    setColor("Black");
    cout << "----------------\n";
    wait(speed * 1);
    cout << "Ráno je velice chladné a větrné. Rozhodnete se proto jít dál do jeskyně s nadějí, že se vám podaří najít \
něco užitečného. Jdete vzdálenost, která se vám zdá jako desítky kilometrů, když nakonec najdete rozsáhlý areál \
připomínající důl. Důl to opravduje je – opuštěný. Zde se může skrývat spousta artefaktů. Jdete proto prozkoumat celý důl. \n";
    wait(speed * 2);

    setColor("White");
    cout << "--\n";
    cout << "Najdete velkou truhlu a zkusíte ji otevřít. Uvnitř je malá páka, kterou můžete pohnout doleva nebo doprava. Kam ji pohnete?    \
1) Doleva; 2) Doprava:  ";
    get_int(number);
    setColor("Cyan");
    if(number == 1){
        number = rand() % 2 + 1;
        if(number == 1){
            cout << "V truhle jste našli elixír, tento item vám po použití zvýší útok o 5. \n";
            inventar(player, "Elixír");
        } else if(number == 2){
            cout << "V truhle jste našli magickou kouli, po použití tohoto itemu vám zvedne max manu o 15. \n";
            inventar(player, "Magická koule");
        }
    } else if(number == 2){
        number = rand() % 3 + 1;
        if(number == 1){
            cout << "V truhle jste našli nápoj náhody. Když tento nápoj použijete, dostanete náhodný efekt. \n";
            inventar(player, "Nápoj náhody");
        } else if(number == 2){
            cout << "V truhle jste našli lektvar zdraví – tento nápoj vám přidá 10 životů k hodnotě max zdraví. \n";
            inventar(player, "Lektvar zdraví");
        } else if(number == 3){
            cout << "V truhle jste našli lékárnu, tento item vám dodá 10 životů. \n";
            inventar(player, "Lékárna");
        }
    }
    setColor("White");
    cout << "--\n";
    cout << "Pro pokračování zadejte jakékoliv písmeno: ";
    cin >> enter;

    setColor("Black");
    cout << "---\n";
    cout << "Najednou se otočíte a uvidíte poněkud nadstandardně velkého trpaslíka. Rozhodně nevypadá přátelsky. \"Co kradeš??\", \
řekl trpaslík. Poté se připravil se svou sekerou a pokusil se s ní hráče uhodit. Vyhnuli jste se jen těsně. Nyní je jasné, že bude boj. \n";
    wait(speed * 3);

    status = fight(player, actions, Monsters["Trpaslík"], Monster_abilities["Trpaslík"], speed);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){ setColor("Black"); cout << "Trpaslíka jste úspěšně porazili, ale nebylo to jednoduché. \n"; }
    wait(speed * 1);

    setColor("Cyan");
    number = rand() % 4 + 1;
    player.experience += number * 2;
    new_level(player, speed);
    if (number < 3){
        player.money += 20;
        cout << "Z trpaslíka jste získali 20 zlatých \n";
    } if (number == 1){
        wait(speed * 1);
        cout << "Z trpaslíka jste také získali elixír. \n";
        inventar(player, "Elixír");
    }

    setColor("White");
    cout << "Pro pokračování zadejte jakékoliv písmeno: ";
    cin >> enter;

    setColor("Black");
    cout << "Ani jste se nestačili rozhlédnout a letí proti vám celý roj netopírů. Většina z nich kolem vás proletí, avšak \
2 netopýři, mnohem větší než ostatní, se u vás zastaví a nadávají: 'Tato jeskyně patří nám! Zmizte nebo bude po vás!' \n";
    wait(speed * 2);

    status = double_fight(player, actions, Monsters["Netopýr"], Monsters["Netopýr"], Monster_abilities["Netopýr"], \
                            Monster_abilities["Netopýr"], speed);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){setColor("Black"); cout << "Náročný boj proti 2 netopýrům jste úspěšně zvládli, je čas odejít dřív, než se něco znovu objeví. \n";}
    cout << "-----\n";

    player.money += 30;
    setColor("Cyan");
    number = rand() % 4 + 1;
    player.experience += number * 3;
    new_level(player, speed);
    if(number < 3){
        player.money += 30;
        cout << "Z netopýrů jste získali 30 zlatých. \n";
    }
    if(number == 1){
        cout << "Z netopýrů jste také získali dobíječ many. \n";
        inventar(player, "Dobíječ many");
    }
    cout << "-----\n";

    setColor("White");
    cout << "Pro pokračování zadejte jakékoliv písmeno: ";
    cin >> enter;
    cout << endl;

    setColor("Black");
    cout << "Po střetu s netopýry rychle odejdete z opuštěného dolu. Nějakou dobu jdete rychlou chůzí a najednou před sebou uvidíte \
podzemní vesnici. Vyskytuje se na vznášejícím se kusu ostrova a vede k němu 500 metrů dlouhý a ne moc kvalitně vypadající most ze dřeva a lana. \n";
    wait(speed * 2);
    cout << endl;

    setColor("White");
    cout << "Projdete mostem bez větších potíží, ale když z mostu na druhé straně sestoupíte, uvidíte za sebou několik nadstandardně \
velkých pavouků. Cesta zpět nebude tak lehká, nicméně je to jediná cesta spojující vesnici a zbytek světa. Na tomto létajícím ostrově \
jste pro nyní alespoň v bezpečí. Využijte toho, protože vás nejspíše čekají další boje. \n";
    wait(speed * 3);

    village(player, speed);
    cout << "----\n";

    cout << "Nyní nadešel čas na střet s těmi pavouky na mostě. Most je jediná cesta ven z vesnice a nyní je jasné, že se tomuto \
střetu s pavouky nevyhnete. Jdete proto jejich směrem a vidíte, že už tam jsou 3 chystající se na boj. Toto bude vskutku náročná bitva. \n";
    wait(speed * 3);

    status = triple_fight(player, actions, Monsters["Pavouk"], Monsters["Pavouk"], Monsters["Pavouk"], Monster_abilities["Pavouk"], \
                            Monster_abilities["Pavouk"], Monster_abilities["Pavouk"], speed);
    setColor("Black");
    if(status == 0){game_over(player); return 0;}
    else{cout << "Boj s pavouky jste úspěšně zvládli, nyní můžete přes most přejít bez dalších potíží. \n";}

    number = rand() % 4 + 1;
    player.experience += number * 5;
    new_level(player, speed);
    setColor("Cyan");
    if(number < 3){
        player.money += 40;
        cout << "Z pavouků jste získali 40 zlatých. \n";
    }
    if(number == 1){
        cout << "Z pavouků jste také dostali nápoj náhody. \n";
        inventar(player, "Nápoj náhody");
    }

    wait(speed * 1);
    cout << endl;

    setColor("White");
    cout << "-----\n";
    cout << "Chcete se z jeskyně už dostat ven a tak se pokoušíte najít východní cestu. Už jste zapomněli, kudy jste sem přišli, protože \
tato jeskyně je vskutku masivní. Víte, co je ještě masivní? Ten obr 10 stop od vás! Kouknete se na něj, ale než stihnete něco udělat, \
uděří vás svou palicí a upadnete do bezvědomí. \n";
    wait(speed * 3);
    cout << endl;
    setColor("Black");
    cout << "Později se probudíte v dost malé vězeňské cele a vůbec nevíte kde jste. Mimo celu vidíte 2 strážníky. Jeden má meč a ten \
druhý má kuš. Nejspíš se s nimi budete muset střetnout, než se budete moct vydat z věznice. Nejdříve je ale třeba dostat se z cely. Na \
stěně vedle vás je otvor do šachty. Vlezete do ní s nadějí, že vás povede ven z cely. Všechno jde tak, jak má, ale najednou se před vámi \
objeví malá nestvůra, která drží činely a bouchá s nimi o sebe. Chcete jít zpět ale tam je druhá malá nestvůra, která má housle a pokouší \
se na ně hrát. Zvuk pocházející z houslí vás dost znepokojuje. Pak se k vám obě nestvůry začnou přibližovat a nezbývá nic jiného, než s \
nimi bojovat. \n";

    cout << endl;
    setColor("White");
    cout << "Pro pokračování zadejte jakékoliv písmeno: ";
    cin >> enter;

    status = double_fight(player, actions, Monsters["Nestvůra s činely"], Monsters["Nestvůra s houslemi"], Monster_abilities["Nestvůra s činely"], \
                            Monster_abilities["Nestvůra s houslemi"], speed);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){setColor("Black"); cout << "Obě nestvůry jste úspěšně porazili. \n";}

    wait(speed * 1);
    setColor("Cyan");
    number = rand() % 2 + 1;
    player.experience += number * 4;
    new_level(player, speed);
    if(number == 1){
        player.money += 10;
        cout << "Z tohoto boje jste si odnesli 10 zlatých. \n";
    }
    number = rand() % 3 + 1;
    if(number == 1){
        cout << "Z nestvůry s činely jste dostali lékárnu. \n";
        inventar(player, "Lékárna");
    }
    number = rand() % 3 + 1;
    if(number == 1){
        cout << "Z nestvůry s houslemi jste dostali magickou kouli. \n";
        inventar(player, "Magická koule");
    }

    wait(speed * 1);
    setColor("Black");
    cout << "-----\n";
    cout << "Souboj s miniaturní příšerou, která pořád jen klape s činely a s nejhorším houslistou, kterého jste kdy viděli, \
jste opravdu nečekali. Moc velká překážka to nebyla, nicméně na vás zanechala zvlášťní pocit. \n";

    wait(speed * 2);

    cout << "Z šachty se po chvíli dostanete ven, na místo, kam jste před chvíli z cely koukali. Zkoušíte se proplížit kolem 2 strážných, \
bohužel si vás ale všimnou. 'To je ten vězeň, že?' řekne strážný s mečem. 'Je to tak, na něj!' odpoví strážný s kuší. \n";

    status = double_fight(player, actions, Monsters["Strážný s mečem"], Monsters["Strážný s kuší"], Monster_abilities["Strážný s mečem"], \
                            Monster_abilities["Strážný s kuší"], speed);
    if(status == 0){game_over(player); return 0;}
    else{setColor("White"); cout << "Oba strážníky jste úspěšně porazili. \n";}

    wait(speed * 1);

    setColor("Cyan");
    number = rand() % 4 + 1;
    player.experience += number * 4;
    new_level(player, speed);
    if(number < 3){
        player.money += 35;
        cout << "Ze strážců jste získali 35 zlatých. \n";
    } else if(number == 3){
        cout << "Ze strážců jste získali elixír. \n";
        inventar(player, "Elixír");
    } else if(number == 4){
        cout << "Ze strážců jste získali nápoj náhody. \n";
        inventar(player, "Nápoj náhody");
    }

    wait(speed * 1);

    setColor("White");
    cout << "Pro pokračování zadejte jakékoliv písmeno:"; cin >> enter;

    setColor("Black");
    cout << "Projdete bránami do věznice ven, ale spatřili jste něco hrozného: ten obr, který vás sem odnesl, se objevil hned před vámi. \
Chtěl vás udeřit už podruhé, tentokrát neúspěšně. Chcete zdrhnout, on vás ale vezme a sází první ránu v boji. \n";

    status = miniboss(player, actions, Monsters["Obr"], Monster_abilities["Obr"], speed);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){cout << "Minibosse jste úspěšně porazili. Ne každému se toto podaří. \n";}

    player.experience += 25;
    new_level(player, speed);
    setColor("Cyan");
    player.money += 50;
    cout << "Z obra jste získali 50 zlatých. \n";
    cout << "Z obra jste také získali lékárnu, lektvar zdraví a dobíječ many. \n";
    inventar(player, "Lékárna");
    inventar(player, "Lektvar zdraví");
    inventar(player, "Dobíječ many");

    setColor("Black");
    cout << "Pro pokračování zadejte jakékoliv písmeno: "; cin >> enter;

    setColor("White");
    cout << "Jste stále v jeskyni. Musíte se dostat ven. Tato jeskyně je ovšem jiná. V dálce vidíte další podzemní vesnici, \
vydáte se proto tím směrem. Cestu vám ale překazí nepřátelský vlk. Asi už je jasné, že ho musíte porazit předtím, než půjdete dál. \n";

    status = fight(player, actions, Monsters["Vlk"], Monster_abilities["Vlk"], speed);
    if(status == 0){game_over(player); return 0;}
    else{setColor("Black"); cout << "Vlka jste úspěšně porazili, nyní můžete pokračovat k vesnici. \n";}
    wait(speed * 1);

    setColor("Cyan");
    number = rand() % 2 + 1;
    player.experience += number * 5;
    new_level(player, speed);
    if(number == 1){
        player.money += 10;
        cout << "Hráč z vlka získal 10 zlatých. \n";
    }

    setColor("White");
    cout << "Po dlouhé chůzi jste konečně dorazili do vesnice. Připravte se, protože vás čeká ještě spousta bojů. \n";
    wait(speed * 1);
    cout << "-----\n";
    village(player, speed);

    wait(speed * 1);
    setColor("Black");
    cout << "-----\n";
    cout << "Vyjdete z vesnice a zahlédnete louku s velice světle zelenou trávou. Celá se třpytí. Zajdete tam s domněnkou, \
že najdete nějaké itemy. Dojdete tam, ale žádné itemy tam nejsou. Našli jste ovšem 3 motýly, kteří nevypadají moc přátelsky. \
Jeden je žlutý, druhý je modrý a ten poslední je červený. Než půjdete dál, budete se jich muset zbavit. \n";

    wait(speed * 2);
    status = triple_fight(player, actions, Monsters["Červený motýl"], Monsters["Žlutý motýl"], Monsters["Modrý motýl"], \
                            Monster_abilities["Červený motýl"], Monster_abilities["Žlutý motýl"], Monster_abilities["Modrý motýl"], speed);
    if(status == 0){game_over(player); return 0;}
    else{setColor("White"); cout << "Motýly jste úspěšně porazili. \n";}

    setColor("Cyan");
    number = rand() % 2 + 1;
    player.experience += number * 7;
    new_level(player, speed);
    if(number == 1){
        player.money += 30;
        cout << "Hráč získal 30 zlatých. \n";
        cout << "Z červeného hráč motýla získal lékárnu. \n";
        inventar(player, "Lékárna");
        cout << "Z modrého motýla hráč získal dobíječ many. \n";
        inventar(player, "Dobíječ many");
        cout << "Ze žlutého motýla hráč získal elixír. \n";
        inventar(player, "Elixír");
    } else{
        cout << "Z červeného motýla hráč získal lektvar života. \n";
        inventar(player, "Lektvar života");
        cout << "Z modrého motýla hráč získal magickou kouli. \n";
        inventar(player, "Magická koule");
        cout << "Ze žlutého motýla hráč získal nápoj náhody. \n";
        inventar(player, "Nápoj náhody");
    }

    setColor("Black");
    cout << "Pro pokračování zadejte jakékoliv písmeno: "; cin >> enter;

    setColor("White");
    cout << "----\n";
    cout << "Vypadá to, že po motýlech jdete lovit medvědy. Proti vám se řítí velká medvědice se 2 mláďaty. \
Je to zvlášťní chování od této medvědice, ale nejspíš je budete také muset porazit. \n"; setColor("Yellow");
    cout << "(Tip) Asi bude nejlepší, když se nejdřív postaráte o medvědici. (1. monstrum) \n";
    wait(speed * 3);

    status = triple_fight(player, actions, Monsters["Medvědice"], Monsters["Medvídě"], Monsters["Medvídě"], Monster_abilities["Medvědice"], \
                            Monster_abilities["Medvídě"], Monster_abilities["Medvídě"], speed);
    setColor("White");
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){cout << "Medvědy jste úspěšně porazili. \n";}
    else if(status == 2){cout << "Medvědice s medvíďaty utekla z boje. \n";}

    wait(speed * 1);
    setColor("Cyan");
    number = rand() % 2 + 1;
    player.experience += number * 7;
    new_level(player, speed);
    if(number == 1){player.money += 20; cout << "Z medvědů jste získali 20 zlatých. \n";}

    setColor("Black");
    cout << "Cestujete jeskyní, a najednou vás přepadnou lupičové. Z motýlů jste dostali dost itemů, a nyní jsou v ohrožení. \
Musíte se tedy bránit. Pozor, jeden z lupičů má revolver. \n";

    wait(speed * 2);

    status = double_fight(player, actions, Monsters["Lupič s dýkou"], Monsters["Lupič s revolverem"], Monster_abilities["Lupič s dýkou"], \
                            Monster_abilities["Lupič s revolverem"], speed);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){setColor("Black"); cout << "Lupiče jste úspěšně porazili, nyní rychle odsud. \n";}
    wait(speed * 1);

    setColor("Cyan");
    number = rand() % 2;
    player.experience += number * 9;
    new_level(player, speed);
    if(number == 1){player.money += 50; cout << "Z lupičů jste dostali 5O zlatých. \n";}
    cout << "Z lupičů jste dostali elixír, dobíječ many a lektvar života. \n";
    inventar(player, "Elixír");
    inventar(player, "Dobíječ many");
    inventar(player, "Lektvar života");

    setColor("White");
    cout << "Pro pokračování zadejte jakékoliv písmeno: "; cin >> enter;

    setColor("Black");
    cout << "Jdete dále jeskyní a najednou vidíte světlo - denní světlo! To by dost pravděpodobně mohla být cesta ven. \
Před otvorem, odkud světlo pochází, je také vidět vesnice. Je to ještě poměrně daleko odsud, ale lze tam dorazit do půl hodiny. \n";
    wait(speed * 2);

    setColor("White");
    cout << "---\n";
    cout << "Blížíte se víc a víc k vesnici, a najednou vás napadne velké stvoření. Železný golem. Vůbec nevíte odkud se vzal. \
Golem na vás mluví: 'Má práce je chránit tuto vesnici. Nikdo nepovolaný do ní nesmí vstoupit.' Golemovi nevystvětlíte, že nemáte \
žádné špatné úmysly a tudíž s ním musíte bojovat. \n";
    wait(speed * 3);

    status = miniboss(player, actions, Monsters["Golem"], Monster_abilities["Golem"], speed);
    if(status == 0){game_over(player); return 0;}
    else if(status == 1){setColor("White"); cout << "Golema jste úspěšně porazili, nyní rychle do vesnice! \n";}

    player.experience += 25;
    new_level(player, speed);
    setColor("Cyan");
    player.money += 50;
    cout << "Z golema jste získali 50 zlatých a nápoj náhody. \n";
    inventar(player, "Nápoj náhody");

    wait(speed * 1);
    setColor("Black");
    cout << "Dorazili jste do vesnice. Dobře se připravte, nejspíš vás čeká poslední boj. \n";
    wait(speed * 1);

    cout << "-----\n";
    village(player, speed);
    cout << "-----\n";

    setColor("White");
    cout << "Po návštěvě poslední vesnice jdete blíže k onomu otvoru vyzařující denní světlo. Jdete k němu a opravdu to vypadá, \
že je to cesta ven. Jdete dál, a jeskyni už začíná pokrývat mechová vrstva s trávou. Nedaleko od vás se nachází hodně zajímavá kytka. \
chytí vaši pozornost, a jdete si ji prohlédnout. \n";
    wait(speed * 3);

    cout << "Chcete se jí dotknout, ale";
    wait(speed * 1);
    for(int i=0; i<5; i++){
        if(i==0){setColor("Yellow");}
        else if(i==1){setColor("Green");}
        else if(i==2){setColor("Red");}
        else if(i==3){setColor("Blue");}
        else if(i==4){setColor("Cyan");}
        cout << ".";
        wait(1);
    }

    setColor("Black");
    cout << "\nKytka najednou vzroste. Ne o moc, nyní má ale stejnou výšku jako hráč. Kytka je dost možná poslední věc, která vám \
brání v tom, abyste vyšli ven, a tak jí chcete porazit co nejrychleji. Ovšem nevíte, jaké další schopnosti skrývá... \n";

    status = bossfight(player, actions, speed);
    if(status == 0){game_over(player); return 0;}
    
    setColor("Green");
    cout << "----------\n";
    cout << "Porazili jste finálního bosse! Nyní můžete po dlouhé době vyjít z jeskyně bez dalších potíží. \n";
    wait(speed * 2);

    setColor("White");
    cout << endl;
    cout << "Jdete dál jeskynním otvorem. Trávy a mechu přibývá a dokonce už můžete zahlédnout samotné slunce. V této \
jeskyni jste strávili mnohem víc času, než jste původně zamýšleli. To ale nevadí, jelikož už jste venku a nehrozí zde žádné nebezpečí. \n";

    wait(speed * 3);
    cout << endl << endl << endl;
    setColor("Yellow");
    cout << "Vyhráhli jste! \n";
    cout << "Dosáhli jste " << player.level << ". úrovně a celkem jste nasbírali " << player.experience << " EXP" << endl;
    cout << "Teď nějaké staty: \n";
    cout << player.money << " peněz" << endl;
    cout << player.mana << " many" << endl;
    cout << player.max_mana << " max many" << endl;
    cout << player.attack << " úrovně útoku" << endl;
    cout << player.health << " životů" << endl;
    cout << player.max_health << " max životů" << endl;

    return 0;
}