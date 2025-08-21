#pragma once

#ifndef __PRESENT_HEADER_INCLUDED_

#define __PRESENT_HEADER_INCLUDED_

#include "Subject.h"

class Player;

enum class PresentType {
	INVALID,
	BLOOD,
	POWER,
	MAGIC,
	LIFE,
	COUNT
};

class Present : virtual public Subject
{
public:
	Present();
	Present(int type = 0, int value = 0);
	
	void setType(int type);
	void setValue(int value);

	inline PresentType getPresentType() const noexcept { return type; }
	inline unsigned getValue() const noexcept { return value; }

	virtual void interact(LivingThings& interactWithArtifact) override;
	virtual void draw(std::ostream& os) const override;
	virtual Artifact* clone() const override;

private:
	PresentType type;
	unsigned value;
};

#endif