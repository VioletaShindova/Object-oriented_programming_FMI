#include "Necromancer.h"
#include <ctime>

Necromancer::Necromancer() : Necromancer(0, "unknown", 0, 0,(int)Weapon::INVALID, 0) {}

Necromancer::Necromancer(int health, const char* name, int x, int y, int weapon, int attackDamage, const char* magic, double additionalDMG)
    : Mage(health, name, x, y, weapon, attackDamage, magic, additionalDMG) {}

Necromancer::Necromancer(int health, const char* name, const Point& other, int weapon, int attackDamage, const char* magic, double additionalDMG)
    : Mage(health, name, other, weapon, attackDamage, magic, additionalDMG) {}

Necromancer::Necromancer(const Player& other, const char* magic, double additionalDMG)
    : Mage(other, magic, additionalDMG) {}

Necromancer::Necromancer(const Mage& other)
    : Mage(other) {}

Necromancer::Necromancer(const Necromancer& other) : Mage(other), size(other.size), capacity(other.capacity)
{
    copyDynamic(other);
}

Necromancer& Necromancer::operator=(const Necromancer& other)
{
    if (this != &other)
    {
        Mage::operator=(other);
        size = other.size;
        capacity = other.capacity;
        freeDynamic();
        copyDynamic(other);
    }
    return *this;
}

Necromancer::~Necromancer() noexcept
{
    freeDynamic();
}

void Necromancer::attack(Player* enemy)
{
    if (!areNeighbors(this, enemy))
        throw std::logic_error("Players are not neighbors\n");

    Mage::attack(enemy);

    if (size > 0)
    {
        Player* randomPlayer = beatenPlayers[rand() % size];
        if (randomPlayer)
            enemy->handleAttack(randomPlayer);
    }

    if (enemy->getHealth() == 0)
    {
        if (size + 1 >= capacity)
            resize();

        beatenPlayers[size++] = enemy->clone();
    }
}

void Necromancer::handleAttack(const Player* other)
{
    if (!areNeighbors(this, other))
        throw std::logic_error("Players are not neighbors\n");

    Mage::handleAttack(other);
}

void Necromancer::print(std::ostream& os) const
{
    Mage::print(os);

    if (!os.good())
        throw std::runtime_error("Stream is not good\n");

    for (size_t i = 0; i < size; i++)
    {
        beatenPlayers[i]->print(os);
        os << '\n';
    }
}

Player* Necromancer::clone() const
{
    return new Necromancer(*this);
}

void Necromancer::freeDynamic()
{
    for (size_t i = 0; i < size; i++)
        delete beatenPlayers[i];
    delete[] beatenPlayers;

    beatenPlayers = nullptr;
}

void Necromancer::copyDynamic(const Necromancer& other)
{
    Player** temp = new (std::nothrow) Player*[other.capacity];

    if (!temp)
        throw std::bad_alloc();

    for (size_t i = 0; i < other.size; i++)
    {
        Player* tempPlayer = other.beatenPlayers[i]->clone();

        if (!tempPlayer)
        {
            delete[] temp;
            throw std::bad_alloc();
        }

        temp[i] = tempPlayer;
    }

    delete[] beatenPlayers;
    beatenPlayers = temp;
}

void Necromancer::resize()
{
    size_t tempCapacity = capacity * 2 + 1;
    Player** temp = new (std::nothrow) Player*[tempCapacity];

    if (!temp)
        throw std::bad_alloc();

    for (size_t i = 0; i < size; i++)
    {
        temp[i] = beatenPlayers[i];
    }

    delete[] beatenPlayers;
    beatenPlayers = temp;
    capacity = tempCapacity;
}