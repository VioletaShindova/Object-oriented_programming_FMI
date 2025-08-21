#pragma once

#ifndef __TELEPORT_HEADER_INCLUDED_

#define __TELEPORT_HEADER_INCLUDED_

#include "Subject.h"
class LivingThings;
class Player;

class Teleport : virtual public Subject
{
public:
	Teleport();

	explicit Teleport(int cageNumber);

	void setCageNumber(int cageNumber);

	inline unsigned getCageNumber() const noexcept { return cageNumber; }

	virtual void interact(LivingThings& interactWithArtifact) override;
	virtual void draw(std::ostream& os) const override;
	virtual Artifact* clone() const override;
private:
	static unsigned getNextID();

	unsigned cageNumber;

	unsigned id;
	static unsigned currID;
};

#endif