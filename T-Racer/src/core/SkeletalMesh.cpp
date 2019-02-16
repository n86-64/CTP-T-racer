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
		// Here we load the meshes into the scene. 
		loadMeshesInAssimpScene(sceneObject);
		//LoadMeshRecursive(sceneObject, name);
		//LoadAnimationsRecursive(sceneObject);
	}
}

void T_racer_Resource_SkeletalMesh::loadMeshesInAssimpScene(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumMeshes; i++) 
	{
		meshes.emplace_back(new T_racer_Resource_SkeletalMesh_Mesh(scene->mMeshes[i]));
	}
}

void T_racer_Resource_SkeletalMesh::loadNodesRecursive(const aiNode * scene, T_racer_Math::Matrix4X4 transform)
{
}
