#pragma once

#ifndef __MONSTER_HEADER_INCLUDED_

#define __MONSTER_HEADER_INCLUDED_

#include "Artifact.h"
#include "LivingThings.h"

class Monster : public Artifact, public LivingThings
{
public:
	Monster();
	Monster(const char* name, int power = 100, int blood = 1000);

	virtual void interact(LivingThings& interactWithArtifact) override;
	virtual void draw(std::ostream& os) const override;

	virtual Monster* clone() const override;
private:
	virtual void interact(Artifact& interactWithArtifact) override {}
};

#endif