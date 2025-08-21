#pragma once

#ifndef __COMBINATION_SUBJECT_HEADER_INCLUDED_

#define __COMBINATION_SUBJECT_HEADER_INCLUDED_

#include "Teleport.h"
#include "Present.h"

class Player;

class CombinationSubject : public Teleport, public Present
{
public:
	CombinationSubject();
	CombinationSubject(int cageNumber, int type = 0, int value = 0);

	virtual void interact(LivingThings& interactWithArtifact) override;
	virtual void draw(std::ostream& os) const override;
	virtual Artifact* clone() const override;
private:
};

#endif