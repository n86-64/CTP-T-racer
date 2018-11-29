/** @file TextureManager.h
*  @brief A collection of textures for use in the system.
*
*  Defines a texture loading system which aquires textures dynamicly.
*  Stored using a hash table in order to reduce complexity.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/


#pragma once
#include <map>
#include <memory>

#include "Texture.h"



class T_racer_TextureManager 
{
public:
	T_racer_TextureManager() = default;

	T_racer_Texture2D*   createTexture(std::string textureName);

private:
	T_racer_Texture2D* loadTexture(std::string texName);

private:
	std::map<std::string, std::unique_ptr<T_racer_Texture2D>>   textures;
};
