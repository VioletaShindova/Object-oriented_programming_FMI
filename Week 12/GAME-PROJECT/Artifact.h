#pragma once

#ifndef __ARTIFACT_HEADER_INCLUDED_

#define __ARTIFACT_HEADER_INCLUDED_

#include <iostream>

class LivingThings;

class Artifact
{
public:
	virtual ~Artifact() noexcept = default;

	virtual void interact(LivingThings& interactWithArtifact) = 0;
	virtual void draw(std::ostream& os) const = 0;
	virtual Artifact* clone() const = 0;

private:
};

#endif