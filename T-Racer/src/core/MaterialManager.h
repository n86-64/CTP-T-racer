/** @file MaterialManager.h
*  @brief A material collection system.
*
*  A storage class which stores refrences to all materials.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <vector>

#include  "core/Materials.h"

struct aiMaterial;
struct aiScene;

class T_racer_TextureManager;

constexpr int T_RACER_MATERIAL_NULL = -1;

class T_racer_MaterialManager
{
public:
	T_racer_MaterialManager();


	int				    createMaterial(std::string name);
	int					createMaterial(const aiScene* scene, const aiMaterial* matData, T_racer_TextureManager* textures, std::string matType, std::string overrideTexture);
	T_racer_Material*   retrieveMaterial(int matID);

private:
	std::vector<std::unique_ptr<T_racer_Material>>  materials;
	int matSize = 0;
};