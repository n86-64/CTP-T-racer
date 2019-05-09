#include "Materials.h"

void T_racer_Material::setTexture(T_racer_Texture2D* newTexture)
{
	materialTexture = newTexture;
}

T_racer_Math::Colour T_racer_Material::sampleTexture(float u, float v)
{
	T_racer_Math::Colour rtnValue = albedo; 
	if (materialTexture) 
	{
		rtnValue = materialTexture->interpolatePointBilinear(u, v);
	}

	return rtnValue;
}
