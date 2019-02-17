#include "Mesh.h"

T_racer_Resource_SkeletalMesh_Mesh::T_racer_Resource_SkeletalMesh_Mesh(aiMesh* newMesh)
{
	T_racer_Vertex vertexObj;
	for (int v = 0; v < newMesh->mNumVertices; v++) 
	{
		vertexObj.position = T_racer_Math::Vector(newMesh->mVertices[v]);
		vertexObj.normal = T_racer_Math::Vector(newMesh->mNormals[v]);

		if (newMesh->mTextureCoords[0] != nullptr) 
		{
			vertexObj.texCoord = T_racer_Math::Vector(newMesh->mTextureCoords[0][v]);
		}
		else 
		{
			vertexObj.texCoord = T_racer_Math::Vector(0.0f, 0.0f, 0.0f);
		}
		
		modelVerticies.emplace_back(vertexObj);
	}

	for (int i = 0; i < newMesh->mNumFaces; i++) 
	{
		for (int j = 0; j < newMesh->mFaces[i].mNumIndices; j++) 
		{
			modelIndicies.emplace_back(newMesh->mFaces[i].mIndices[j]);
		}
	}
}
