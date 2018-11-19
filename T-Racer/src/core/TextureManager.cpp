#include <SFML/Graphics.hpp>

#include "TextureManager.h"


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
