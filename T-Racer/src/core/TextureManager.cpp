#include <SFML/Graphics.hpp>

#include "TextureManager.h"


T_racer_TextureManager::T_racer_TextureManager()
{
	// Create a default texture availible for use in the renderer. (Simply a 256x256 white colour background.)
	T_racer_Texture2D* defaultTex = new T_racer_Texture2D(256, 256);
	textures.emplace(std::pair<std::string, std::unique_ptr<T_racer_Texture2D>>("default", defaultTex));
}

T_racer_Texture2D* T_racer_TextureManager::createTexture(std::string textureName)
{
	T_racer_Texture2D*  tex = nullptr;
	auto  result = textures.find(textureName);

	if (result != textures.end()) 
	{
		tex = result->second.get();
	}
	else 
	{
		tex = loadTexture(textureName);
	}

	return tex;
}

T_racer_Texture2D * T_racer_TextureManager::createTexture(std::string name, aiTexture* texture)
{
	T_racer_Texture2D*  tex = nullptr;
	auto  result = textures.find(name);

	if (result != textures.end())
	{
		tex = result->second.get();
	}
	else
	{
		// Texture is embedded so create from assimp directly.
		textures.emplace(std::pair<std::string, std::unique_ptr<T_racer_Texture2D>>(name, new T_racer_Texture2D(texture)));
	}

	return tex;
}

T_racer_Texture2D* T_racer_TextureManager::loadTexture(std::string texName)
{
	sf::Image  imageFile;
	if (imageFile.loadFromFile(texName)) 
	{
		sf::Color  col;
		T_racer_Texture2D* texture = new T_racer_Texture2D(imageFile.getSize().x, imageFile.getSize().y);
		textures.emplace(std::pair<std::string, std::unique_ptr<T_racer_Texture2D>>(texName, texture));

		for (int y = 0; y < imageFile.getSize().y; y++) 
		{
			for (int x = 0; x < imageFile.getSize().x; x++)
			{
				col = imageFile.getPixel(x, y);
				texture->copyPixelValues(x, y, col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
			}
		}

		return texture;
	}

	return nullptr;
}
