    #include "Warrior.h"

    Warrior::Warrior() : Warrior(0, "unknown", 0, 0, (int)Weapon::INVALID, 0) {}

    Warrior::Warrior(int health, const char* name, int x, int y, int weapon, int attackDamage, int shield)
        : Player(health, name, x, y, weapon, attackDamage), shield(0)
    {
        setShield(shield);
    }

    Warrior::Warrior(int health, const char* name, const Point& other, int weapon, int attackDamage, int shield)
        : Player(health, name, other, weapon, attackDamage), shield(0)
    {
        setShield(shield);
    }

    Warrior::Warrior(const Player& other, int shield)
        : Player(other), shield(0)
    {
        setShield(shield);
    }

    void Warrior::setShield(int shield)
    {
        if (shield < 0)
            throw std::invalid_argument("Shield must be a positive number\n");

        this->shield = shield;
    }

    void Warrior::handleAttack(const Player* other)
    {
        if (!areNeighbors(this, other))
            throw std::logic_error("Players are not neighbors\n");

        if (shield > 0)
        {
            int res = shield - other->getAttackPower();

            if (res < 0)
            {
                Player::handleAttack(other); //remove from health
                shield = 0;
            }
            else
                shield = res;
        }
        else
            Player::handleAttack(other);
    }

    void Warrior::print(std::ostream& os) const
    {
        Player::print(os);

        if (!os.good())
            throw std::runtime_error("Invalid stream\n");

        os << '\n' << "Shield: " << shield;
    }

    Player* Warrior::clone() const
    {
        return new Warrior(*this);
    }
