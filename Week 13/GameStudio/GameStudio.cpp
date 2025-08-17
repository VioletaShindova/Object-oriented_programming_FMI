// GameStudio.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PlayerCollection.h"
#include "Player.h"
#include "Warrior.h"
#include "Mage.h"
#include "Necromancer.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    Player** players = new Player*[3];

    players[0] = new Warrior();
    players[1] = new Mage(10, "Morgana", 50, 3, 2, 0, "spell", 0.01);
    players[2] = new Necromancer(20, "Lux", 100, 2, 2,0,"ult", 0.1);

    PlayerCollection pc;

    if (pc.addPlayer(players[0]))
        std::cout << "Succesfully added new player\n";

    Mage* temp = dynamic_cast<Mage*>(players[1]);

    temp->attack(players[2]);

    for (size_t i = 0; i < 3; i++)
    {
        delete players[i];
    }
    delete[] players;
}

