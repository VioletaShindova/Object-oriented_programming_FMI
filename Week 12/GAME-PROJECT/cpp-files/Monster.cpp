#include "Monster.h"
#include "Present.h"
#include "Teleport.h"

Monster::Monster() : Monster("unknown") {}

Monster::Monster(const char* name, int power, int blood) : Artifact(), LivingThings(name, power, blood) {}

void Monster::interact(LivingThings& interactWithArtifact)
{
	if (getBlood() <= interactWithArtifact.getPower())
	{
		setBlood(0);
		setPower(0);
	}
	else if(getPower() >= interactWithArtifact.getBlood())
	{
		interactWithArtifact.setBlood(0);
		interactWithArtifact.setPower(0);
		throw std::runtime_error("You lost!\n");
	}
	else
	{
		setBlood(getBlood() - interactWithArtifact.getPower());
		interactWithArtifact.setBlood(interactWithArtifact.getBlood() - getPower());
	}
}

void Monster::draw(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	os << "Name: " << getName() << "\nPower: " << getPower() << "\nBlood: " << getBlood() << '\n';
}

Monster* Monster::clone() const
{
	return new Monster(*this);
}
