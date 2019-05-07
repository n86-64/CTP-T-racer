#include <queue>

#include "MaterialManager.h"
#include "TextureManager.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "SkeletalMesh.h"

bool T_racer_Resource_SkeletalMesh::loadSkeletalMesh(std::string name, T_racer_MaterialManager* materials, T_racer_TextureManager* textures, std::string matType, std::string overrideTexture)
{
	Assimp::Importer fileLoader;

	const aiScene* sceneObject = fileLoader.ReadFile(name,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (!sceneObject)
	{
		// Return reporting an error in the process.
		printf("ERROR - Failed tp load model object.");
		return false;
	}
	else
	{
		this->name = name;
		T_racer_Math::Matrix4X4   transform;

		// Here we load the meshes into the scene. 
		loadMeshesInAssimpScene(sceneObject, materials, textures, matType, overrideTexture);
		loadNodesRecursive(sceneObject->mRootNode, transform, -1);
		return true;
	}
}

std::vector<Triangle> T_racer_Resource_SkeletalMesh::draw(T_racer_MaterialManager* materials, T_racer_TextureManager* textures, std::string overrideTexture)
{
	Triangle                                newPrimative;
	std::vector<Triangle>					modelTriangles;
	T_racer_Resource_SkeletalMesh_Node*		node = nullptr;

	// Uses queue mechanism to aquire the correct set of triangles.
	std::queue<int> nodeToRender;
	nodeToRender.emplace(0);
	int vIndex = 0;

	T_racer_Vertex  verts[3];
	T_racer_Math::Vector interpolatedNormal;


	while (nodeToRender.size() > 0) 
	{
		node = &nodes[nodeToRender.front()];

		for (int index : node->getModelIndicies()) 
		{
			// Loads the models into ram.
			for (int i = 0; i < meshes[index].modelIndicies.size(); i++) 
			{
				verts[vIndex] = meshes[index].modelVerticies[meshes[index].modelIndicies[i]];
				verts[vIndex].position = node->getModelMatrix() * verts[vIndex].position;
				vIndex++;

				if (vIndex == 3) 
				{
					vIndex = 0;
					newPrimative = Triangle(verts[0], verts[1], verts[2]);

					// Add the smooth normals together.
					interpolatedNormal = T_racer_Math::cross(verts[1].position - verts[0].position, verts[2].position - verts[0].position);
					meshes[index].modelVerticies[meshes[index].modelIndicies[i - 2]].normalSmooth += interpolatedNormal;
					meshes[index].modelVerticies[meshes[index].modelIndicies[i - 1]].normalSmooth += interpolatedNormal;
					meshes[index].modelVerticies[meshes[index].modelIndicies[i]].normalSmooth += interpolatedNormal;

					newPrimative.setMaterialIndex(meshes[index].materialID);
					modelTriangles.emplace_back(newPrimative);
				}
			}
		}

		for (int nIndex : node->getChildren()) 
		{
			nodeToRender.emplace(nIndex);
		}

		nodeToRender.pop();
	}

	if (modelTriangles.size() == 0) 
	{
		for (int j = 0; j < meshes.size(); j++)
		{
			// Loads the models into ram.
			for (int i = 0; i < meshes[j].modelIndicies.size(); i++)
			{
				verts[vIndex] = meshes[j].modelVerticies[meshes[j].modelIndicies[i]];
				vIndex++;

				if (vIndex == 3)
				{
					vIndex = 0;
					newPrimative = Triangle(verts[0], verts[1], verts[2]);

					// Add the 
					//interpolatedNormal = T_racer_Math::cross(verts[1].position - verts[0].position, verts[2].position - verts[0].position);
					//meshes[vIndex].modelVerticies[meshes[vIndex].modelIndicies[i - 2]].normalSmooth += interpolatedNormal;
					//meshes[vIndex].modelVerticies[meshes[vIndex].modelIndicies[i - 1]].normalSmooth += interpolatedNormal;
					//meshes[vIndex].modelVerticies[meshes[vIndex].modelIndicies[i]].normalSmooth += interpolatedNormal;


					newPrimative.setMaterialIndex(meshes[j].materialID);
					modelTriangles.emplace_back(newPrimative);
				}
			}

			//for (T_racer_Vertex& vertex :  meshes[j].modelVerticies) 
			//{
			//	vertex.normalSmooth.normaliseSelf();
			//}
		}
	}

	return modelTriangles;
}

void T_racer_Resource_SkeletalMesh::loadMeshesInAssimpScene(const aiScene* scene, T_racer_MaterialManager* materials, T_racer_TextureManager* textures, std::string matType, std::string overrideTexture)
{
	T_racer_Resource_SkeletalMesh_Mesh newMesh;
	int matIndex = -1;

	// Load materials and textures here. 
	for (int i = 0; i < scene->mNumMeshes; i++) 
	{
		newMesh = T_racer_Resource_SkeletalMesh_Mesh(scene->mMeshes[i]);
		matIndex = materials->createMaterial(scene, scene->mMaterials[scene->mMeshes[i]->mMaterialIndex], textures, matType, overrideTexture);
		newMesh.materialID = matIndex;
		meshes.emplace_back(newMesh);
	}
}

void T_racer_Resource_SkeletalMesh::loadNodesRecursive(const aiNode * scene, T_racer_Math::Matrix4X4 transform, int parent)
{
	T_racer_Math::Matrix4X4 model = transform * T_racer_Math::Matrix4X4(scene->mTransformation);

	nodes.emplace_back(T_racer_Resource_SkeletalMesh_Node());

	T_racer_Resource_SkeletalMesh_Node* newNode = &(nodes[nodes.size() - 1]);
	newNode->setParent(parent);
	newNode->setModelMatrix(model);

	newNode->setMeshSize(scene->mNumMeshes);

	int index = nodes.size() - 1;

	if (parent != -1)
	{
		nodes[parent].addChild(index);
	}

	for (int j = 0; j < scene->mNumChildren; j++)
	{
		loadNodesRecursive(scene->mChildren[j], model, index);
	}
}