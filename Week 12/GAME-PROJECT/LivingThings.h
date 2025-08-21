#pragma once

#ifndef __LIVING_THINGS_HEADER_INCLUDED_

#define __LIVING_THINGS_HEADER_INCLUDED_

#include <iostream>

class Artifact;


class LivingThings
{
public:
	LivingThings();
	LivingThings(const char* name, int power = 100, int blood = 1000);
	LivingThings(const LivingThings& other);
	LivingThings& operator=(const LivingThings& other);
	virtual ~LivingThings() noexcept;

	void setName(const char* name);
	void setPower(int power);
	void setBlood(int blood);

	inline const char* getName() const noexcept { return name; }
	inline unsigned getPower() const noexcept { return power; }
	inline unsigned getBlood() const noexcept { return blood; }
	inline unsigned getMaxBlood() const noexcept { return maxBlood; }

	virtual void interact(Artifact& interactWithArtifact) = 0;
	virtual LivingThings* clone() const = 0;
private:
	void setMaxBlood(int maxBlood);
	void freeDynamic();
	void copyDynamic(const LivingThings& other);

	char* name;
	unsigned power;
	unsigned blood;

	unsigned maxBlood;
};

#endif