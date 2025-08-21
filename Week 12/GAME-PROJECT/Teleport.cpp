#include "Teleport.h"
#include "Game.h"
#include "Player.h"

unsigned Teleport::currID = 0;

Teleport::Teleport() : Teleport(1) {}

Teleport::Teleport(int cageNumber)
    : cageNumber(0)
{
    setCageNumber(cageNumber);
}

void Teleport::setCageNumber(int cageNumber)
{
    if (cageNumber < 1)
        throw std::invalid_argument("Invalid cage number\n");

    this->cageNumber = cageNumber;
}

void Teleport::interact(LivingThings& interactWithArtifact)
{
    int currPosition = rand() % GlobalConstants::MAX_BORDER;

    if (Player* p = dynamic_cast<Player*>(&interactWithArtifact))
        p->setCurrentPosition(currPosition);
}

void Teleport::draw(std::ostream& os) const
{
    if (!os.good())
        throw std::runtime_error("Stream is not good\n");

    os << "ID: " << id << "\nCage number: " << cageNumber << '\n';
}

Artifact* Teleport::clone() const
{
    return new Teleport(*this);
}

unsigned Teleport::getNextID()
{
    return currID++;
}
