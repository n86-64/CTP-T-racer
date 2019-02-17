#include <assimp/material.h>

// The diffrent material types.
#include "MatDiffuse.h"
#include "MatMirrors.h"
#include "MatGlass.h"

#include "MaterialManager.h"

T_racer_MaterialManager::T_racer_MaterialManager()
{
	materials.emplace_back(std::make_unique<T_racer_Materials_BasicDiffuse>()); // Initialise a basic diffuse.
	matSize++;
}

int T_racer_MaterialManager::createMaterial(std::string name)
{
	for (int i = 0; i < matSize; i++)
	{
		if (materials[i]->getName() == name)
		{
			return i;
		}
	}

	return T_RACER_MATERIAL_NULL;
}

int T_racer_MaterialManager::createMaterial(const aiMaterial* matData)
{
	aiString aiName; std::string name;
	matData->Get(AI_MATKEY_NAME, aiName);
	name = aiName.C_Str();

	int matIndex = createMaterial(name);

	if (matIndex == T_RACER_MATERIAL_NULL) 
	{
		// Create the material. Set it to diffuse for now. (Need a good way to determine diffrent properties.)
		T_racer_Material*  newMat = new T_racer_Materials_BasicDiffuse();
		newMat->setName(name);
		materials.emplace_back(newMat);
		matIndex = materials.size() - 1;
	}

	return matIndex;
}

T_racer_Material* T_racer_MaterialManager::retrieveMaterial(int matID)
{
	return materials[matID].get();
}