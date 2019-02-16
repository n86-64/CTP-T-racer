#include "MatDiffuse.h"
#include "MatMirrors.h"
#include "MatGlass.h"

#include "MaterialManager.h"

T_racer_MaterialManager::T_racer_MaterialManager()
{
	materials.emplace_back(std::make_unique<T_racer_Materials_BasicDiffuse>()); // Initialise a basic diffuse.
	matSize++;
}

T_racer_Material* T_racer_MaterialManager::retrieveMaterial(int matID)
{
	return materials[matID].get();
}

T_racer_Material* T_racer_MaterialManager::retrieveMaterial(std::string name)
{
	for (int i = 0; i < matSize; i++) 
	{
		if (materials[i]->getName() == name) 
		{
			return materials[i].get();
		}
	}

	return nullptr;
}
