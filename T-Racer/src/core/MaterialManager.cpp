#include <assimp/material.h>
#include <assimp/scene.h>

// The diffrent material types.
#include "MatDiffuse.h"
#include "MatMirrors.h"
#include "MatGlass.h"

#include "MaterialManager.h"
#include "TextureManager.h"

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

int T_racer_MaterialManager::createMaterial(const aiScene* scene, const aiMaterial* matData, T_racer_TextureManager* textures, std::string matType, std::string overrideTexture)
{
	aiString aiName; std::string name;
	int textureIndex = -1;
	matData->Get(AI_MATKEY_NAME, aiName);
	AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, textureIndex);
	name = aiName.C_Str();

	int matIndex = createMaterial(name);

	if (matIndex == T_RACER_MATERIAL_NULL) 
	{
		T_racer_Material*  newMat = nullptr;
		// Create the material. Set it to diffuse for now. (Need a good way to determine diffrent properties.)
		if(matType == "Diffuse") { newMat = new T_racer_Materials_BasicDiffuse(); }
		else if (matType == "Mirror") { newMat = new T_racer_Materials_Mirror(); }
		else if(matType == "Glass") {newMat = new T_racer_Materials_Dilectric_Glass(); }
		else { newMat = new T_racer_Materials_BasicDiffuse(); }

		newMat->setName(name);

		// Set the texture.
		if (overrideTexture == "") 
		{
			if (textureIndex == -1)
			{
				aiString path;
				if (AI_FAILURE == matData->GetTexture(aiTextureType_DIFFUSE, 0, &path))
				{
					// No texture, set an albedo.
					aiColor3D diffColour;
					matData->Get(AI_MATKEY_COLOR_DIFFUSE, diffColour);
					newMat->albedo = T_racer_Math::Colour(diffColour.r, diffColour.g, diffColour.b);
				}
				else
				{
					newMat->setTexture(textures->createTexture(path.C_Str()));
				}
			}
			else
			{
				newMat->setTexture(textures->createTexture(name, scene->mTextures[textureIndex]));
			}
		}
		else 
		{
			newMat->setTexture(textures->createTexture(overrideTexture));
		}

		materials.emplace_back(newMat);
		matIndex = materials.size() - 1;
	}

	return matIndex;
}

T_racer_Material* T_racer_MaterialManager::retrieveMaterial(int matID)
{
	return materials[matID].get();
}