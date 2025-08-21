#pragma once

#ifndef __PLAYER_HEADER_INCLUDED_

#define __PLAYER_HEADER_INCLUDED_

#include "LivingThings.h"

class Player : public LivingThings
{
public:
	Player();

	void setCurrentPosition(int currentPosition);

	inline unsigned getCurrentPosition() const noexcept { return currentPosition; }

	virtual void interact(Artifact& interactWithArtifact) override;
	virtual LivingThings* clone() const override;
private:
	unsigned currentPosition;
};

#endif