#include <queue>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "SkeletalMesh.h"

void T_racer_Resource_SkeletalMesh::loadSkeletalMesh(std::string name)
{
	Assimp::Importer fileLoader;

	const aiScene* sceneObject = fileLoader.ReadFile(name,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_ConvertToLeftHanded
	);

	if (!sceneObject)
	{
		// Return reporting an error in the process.
		printf("ERROR - Failed tp load model object.");
		return;
	}
	else
	{
		this->name = name;
		T_racer_Math::Matrix4X4   transform;

		// Here we load the meshes into the scene. 
		loadMeshesInAssimpScene(sceneObject);
		loadNodesRecursive(sceneObject->mRootNode, transform, 0);
		
	}
}

std::vector<Triangle> T_racer_Resource_SkeletalMesh::draw()
{
	std::vector<Triangle>					modelTriangles;
	T_racer_Resource_SkeletalMesh_Node*		node = nullptr;

	// Uses queue mechanism to aquire the correct set of triangles.
	std::queue<int> nodeToRender;
	nodeToRender.emplace(0);
	int vIndex = 0;

	T_racer_Vertex  verts[3];


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
					modelTriangles.emplace_back(Triangle(verts[0], verts[1], verts[2]));
				}
			}
		}
	}

	return ;
}

void T_racer_Resource_SkeletalMesh::loadMeshesInAssimpScene(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumMeshes; i++) 
	{
		meshes.emplace_back(T_racer_Resource_SkeletalMesh_Mesh(scene->mMeshes[i]));
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