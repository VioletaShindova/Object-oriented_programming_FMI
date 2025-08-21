#include "Present.h"
#include "Artifact.h"
#include "Player.h"

Present::Present() : Present((int)PresentType::INVALID, 0) {}

Present::Present(int type, int value)
	: type(PresentType::INVALID), value(0)
{
	setType(type);
	setValue(value);
}

void Present::setType(int type)
{
	if (type <= (int)PresentType::INVALID || type >= (int)PresentType::COUNT)
		throw std::invalid_argument("Invalid type\n");

	this->type = (PresentType)type;
}

void Present::setValue(int value)
{
	if (value < 0)
		throw std::invalid_argument("Invalid value\n");

	this->value = value;
}

void Present::interact(LivingThings& interactWithArtifact)
{
	if (Player* p = dynamic_cast<Player*>(&interactWithArtifact))
	{
		unsigned tempBlood = p->getBlood();
		if (tempBlood + value > p->getMaxBlood())
			p->setBlood(p->getMaxBlood());
		else
			p->setBlood(tempBlood + value);
		
		int temp = value - tempBlood;
		if (temp < 0)
			value = 0;
		else
			value -= tempBlood;
	}
}

void Present::draw(std::ostream& os) const
{
	if (!os.good())
		throw std::runtime_error("Stream is not good\n");

	os << "Present type: " << (int)type << "\nValue: " << value;
}

Artifact* Present::clone() const
{
	return new Present(*this);
}
