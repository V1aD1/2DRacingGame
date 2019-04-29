#pragma once

#include "Entity.h"

class ParticleEmitter
{
private:
	static const int c_pool_size = 100;

public:
	ParticleEmitter();
	virtual ~ParticleEmitter();
};