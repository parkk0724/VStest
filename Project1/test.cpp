


#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "d3dx9.h"


#pragma comment(lib, "assimp-vc140-mt.lib")
#pragma comment(lib, "d3dx9d.lib")


using namespace std;

//struct Vertex
//{
//   D3DXVECTOR3 position;
//   D3DXVECTOR3 normal;
//   D3DXVECTOR2 uv;
//   uint8_t jointIndices[4];
//   float jointWeights[4];
//};

struct Joint
{
	string name;
	int parent;
};

struct Skeleton
{
	vector<Joint> joints;
	D3DXMATRIXA16 Root;
	aiMatrix4x4 t;
};

Skeleton sk;

void ReadSkeleton(const aiNode* node, int index, int parent)
{
	//aiMatrix4x4 t = node->mTransformation;
	////t.Transpose();
	//// t.Transpose()�� �ϰ� �ȴٸ�, sk.Root(0,0) = t.a1; sk.Root(0,1) = t.a2; ... 

	//sk.Root(0, 0) = t.a1;
	//sk.Root(1, 0) = t.a2; // ...

	Joint joint;
	joint.name = node->mName.C_Str();
	joint.parent = parent;


	sk.joints.push_back(joint);

	cout << joint.name << endl;

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
		ReadSkeleton(node->mChildren[i], sk.joints.size(), index);
}

//void ReadMesh(const aiNode* node)
//{
//   // position
//
//   // normal
//
//   // uv
//
//   // joint index
//
//   // joint weight
//
//
//   for (unsigned int i = 0; i < node->mNumChildren; ++i)
//      ReadMesh(node->mChildren[i]);
//}

int main()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("male.skeleton.x", aiProcess_JoinIdenticalVertices | aiProcess_ConvertToLeftHanded);



	for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; ++i)
		ReadSkeleton(scene->mRootNode->mChildren[i], 0, -1);


	// ReadMesh(scene->mRootNode);

	// ���̳ʸ�
	// 1. ���� ���� (1����Ʈ) : uint8_t

	// 2. �̸��� ����Ʈ ��(4����Ʈ) : int
	// 3. �̸� ������ : char[]
	// 4. �θ� �ε���(4����Ʈ) : int




	return 0;
}