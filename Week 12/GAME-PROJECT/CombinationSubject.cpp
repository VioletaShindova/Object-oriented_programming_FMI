#include "CombinationSubject.h"
#include "Teleport.h"
#include "Present.h"
#include "Subject.h"

CombinationSubject::CombinationSubject() : CombinationSubject(1, (int)PresentType::INVALID, 0) {}

CombinationSubject::CombinationSubject(int cageNumber, int type, int value)
    : Subject(), Teleport(cageNumber), Present(type, value) { }

void CombinationSubject::interact(LivingThings& interactWithArtifact)
{
    Present::interact(interactWithArtifact);
    Teleport::interact(interactWithArtifact);
}

void CombinationSubject::draw(std::ostream& os) const
{
    Teleport::draw(os);
    Present::draw(os);
}

Artifact* CombinationSubject::clone() const
{
    return new CombinationSubject(*this);
}
