#include "Math_Sampler.h"

float T_racer_Math::Sampler::Random()
{
	return data(mersenneTwist);
}

T_racer_Math::Vector T_racer_Math::Sampler::Random2()
{
	return T_racer_Math::Vector(data(mersenneTwist), data(mersenneTwist));
}

T_racer_Math::Vector T_racer_Math::Sampler::Random3()
{
	return T_racer_Math::Vector(data(mersenneTwist), data(mersenneTwist), data(mersenneTwist));
}
