#include "helpers/OBJ_Loader.h"
#include "ModelLoader.h"

void T_racer_ResourceModel::loadModel(std::string pathNames)
{
	// Here we load OBJ models. 
	// Nothing too fancy just load the meshes.
	objl::Loader   fileStream;
	T_racer_Vertex vertex[3];
	int index = 0;

	if (fileStream.LoadFile(pathNames)) 
	{
		for (int i = 0; i < fileStream.LoadedMeshes.size(); i++) 
		{
			for (int j = 0; j < fileStream.LoadedMeshes[i].Vertices.size(); j++) 
			{
				objl::Vertex*  vertexPtr = &fileStream.LoadedMeshes[i].Vertices[j];
				vertex[index].position = T_racer_Math::Vector(vertexPtr->Position.X, vertexPtr->Position.Y, vertexPtr->Position.Z);
				vertex[index].normal= T_racer_Math::Vector(vertexPtr->Normal.X, vertexPtr->Normal.Y, vertexPtr->Normal.Z);
				vertex[index].texCoord = T_racer_Math::Vector(vertexPtr->TextureCoordinate.X, vertexPtr->TextureCoordinate.Y);

				if (index == 2) 
				{
					modelTriangles.emplace_back(vertex[0], vertex[1], vertex[2]);
					index = 0;
				}
				else 
				{
					index++;
				}
			}
		}
	}
}

std::vector<Triangle>* T_racer_ResourceModel::getModelTriangles()
{
	return &modelTriangles;
}
