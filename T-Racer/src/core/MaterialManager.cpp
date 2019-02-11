#include "MatDiffuse.h"
#include "MatMirrors.h"
#include "MatGlass.h"

#include "MaterialManager.h"

T_racer_MaterialManager::T_racer_MaterialManager()
{
	materials.emplace_back(std::make_unique<T_racer_Materials_Dilectric_Glass>()); // Initialise a basic diffuse.
}

T_racer_Material* T_racer_MaterialManager::retrieveMaterial(int matID)
{
	return materials[matID].get();
}
