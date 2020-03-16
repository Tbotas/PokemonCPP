#include <iostream>
#include <ctime>
#include "console.h"
#include "pokemon.h"

Console* console;

std::vector<Pokemon*> ownedPokemons;

std::vector<Pokemon*> pokemonDataList = {
    new Pokemon("Bulbizarre", Type::Plante, Type::Poison, 1, 45, 49, 49, *new Move("Charge", Type::Normal, 35, 95)),
    new Pokemon("Salamèche", Type::Feu, Type::None, 1, 39, 52, 43, *new Move("Griffe", Type::Normal, 40, 100)),
    new Pokemon("Carapuce", Type::Eau, Type::None, 1, 44, 48, 65, *new Move("Charge", Type::Normal, 35, 95))  
};

void tutorial();
void printTeam();
bool turn(Pokemon* ally, Pokemon* enemy);
bool capturer(Pokemon p);
void heal();
void fight(bool wild);

int main(void) {
    std::srand(std::time(nullptr));
    
    console = Console::get();

    tutorial();
    std::cout << ownedPokemons.size();

    while(true) {
        int choice = console->newChoice("Que voulez vous faire ?")
            ->addChoice("Combattre un pokemon sauvage.")
            ->addChoice("Combattre un dresseur.")
            ->addChoice("Voir les pokémons dans la team.")
            ->addChoice("Quitter.")
            ->getInput(true);

        switch (choice) {
            case 0:
                fight(true);
                break;
            case 1:
                fight(false);
                break;
            case 2:
                printTeam();
                continue;
            case 3:
                return 0;
        }
        
        int endFightChoice = console->newChoice("Voulez-vous soigner vos pokemons ?")
                ->addChoice("Oui.")
                ->addChoice("Non.")
                ->getInput(true);

        switch (endFightChoice) {
            case 0:
                heal();
                break;
            case 1:
                break;
        }
    }

    return 0;
}

void heal() {
    for (auto &pokemon : ownedPokemons) {
        pokemon->m_hp = pokemon->m_maxhp;
    }
}

void fight(bool wild) {
    Pokemon enemy = *pokemonDataList.at(std::rand() % 3);
    
    Pokemon* ally = ownedPokemons.at(0);

    while (true) {
        std::cout << ally->m_name + " Niv." + std::to_string(ally->m_level) + "(" + std::to_string(ally->m_hp) + "/" + std::to_string(ally->m_maxhp) + ")"+ "\t\t" +
                     enemy.m_name + " Niv." + std::to_string(enemy.m_level) + "(" + std::to_string(enemy.m_hp) + "/" + std::to_string(enemy.m_maxhp) + ")\n\n";
        
        console->newChoice("Que voulez vous faire ?")
            ->addChoice("Attaquer");

        if (wild) {
            console->addChoice("Lancer une pokeball")
                ->addChoice("Fuir");
        }
            
        int choice = console->getInput(false);

        switch (choice) {
            case 0:
                if (turn(ally, &enemy)) {
                    return;
                }
                break;
            case 1:
                if (capturer(enemy)) {
                    console->newText()
                    ->addText("Bravo vous venez de capturer " + enemy.m_name)
                    ->drawText(true);
                    
                    ownedPokemons.push_back(&enemy);
                    return;
                } else {
                    console->newText()
                    ->addText("Malheureusement " + enemy.m_name + " s'est échappé.")
                    ->drawText(true);
                }
                break;
            case 2:
                return;
        }
    }
}

bool turn(Pokemon* ally, Pokemon* enemy) {
    int damageAlly = ((((2*ally->m_level) / 5.0 + 2) * ally->m_move.m_basePower * ally->m_attack / enemy->m_defense) / 50.0) + 2 * ((std::rand() % (100 - 85) + 85) / 100);
    int damageEnemy = ((((2*enemy->m_level) / 5.0 + 2) * enemy->m_move.m_basePower * enemy->m_attack / ally->m_defense) / 50.0) + 2 * ((std::rand() % (100 - 85) + 85) / 100);

    enemy->m_hp -= damageAlly;

    console->newText()
        ->addText("Votre " + ally->m_name + " attaque le " + enemy->m_name + " adverse et lui retire " + std::to_string(damageAlly) + " hp.");

    if (enemy->m_hp <= 0) {
        console->addText("Le " + enemy->m_name + " adverse est KO.")
            ->addText("Bravo vous avez gagné le combat !")
            ->drawText(true);
        return true;
    }

    console->drawText(true);

    console->newText()
        ->addText("Le " + enemy->m_name + " adverse attaque votre " + ally->m_name + " et lui retire " + std::to_string(damageAlly) + " hp.");

    if (ally->m_hp <= 0) {
        console->addText("Votre " + ally->m_name + " est KO. ");
        console->drawText(true);
        return true;
    }

    console->drawText(true);

    return false;
}

bool capturer(Pokemon p) {
    int N = rand() % 256;
    float f = (p.m_maxhp * 255 * 4.0) / (p.m_hp * 12.0);
    return f >= N;
}

void tutorial() {
    std::cout << "Bonjour, bienvenue dans ce Pokemon en CLI." << std::endl
              << "Pour avancer dans le texte appuyez sur la touche entrée." << std::endl
              << "Lorsque vous devez faire un choix entrez le numéro du choix correspondant." << std::endl
              << "Lors d'un combat votre pokemon est situé à gauche et celui de l'adversaire à droite." << std::endl;
    getchar();

    while (true) {
        int choice = console->newChoice("Veuillez choisir votre pokemon de départ.")
            ->addChoice("Bulbizarre")
            ->addChoice("Salamèche")
            ->addChoice("Carapuce")
            ->getInput(true);

        std::string pokemonText;
        switch (choice) {
            case 0:
                pokemonText = "Bulbizarre: Pokémon de type plante.";
                break;
            case 1:
                pokemonText = "Salamèche: Pokémon de type feu.";
                break;
            case 2:
                pokemonText = "Carapuce: Pokémon de type eau.";
                break;
        }

        int confirm = console->newChoice(pokemonText + "\nConfirmez-vous ce choix ?")
            ->addChoice("Oui")
            ->addChoice("Non")
            ->getInput(true);
        
        if (confirm == 0) {
            ownedPokemons.push_back(pokemonDataList[choice]);
            return;
        }
    }
}

void printTeam() {
    console->newText();
    console->addText("Votre team:\n");
    for (unsigned int i = 0; i < ownedPokemons.size(); i++) {
        auto pokemon = ownedPokemons.at(i);
        console->addText(pokemon->m_name + " Niv." + std::to_string(pokemon->m_level));
    }
    console->drawText(true);
}