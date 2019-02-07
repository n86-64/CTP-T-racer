#include "Math_Sampler.h"

T_racer_Math::Sampler::Sampler()
{
	mersenneTwist = std::mt19937(rngEngine());
	data = std::uniform_real_distribution<float>(-1.0f, 1.0f);
}

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
