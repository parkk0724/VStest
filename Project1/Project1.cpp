// Project1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
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
	//// t.Transpose()를 하게 된다면, sk.Root(0,0) = t.a1; sk.Root(0,1) = t.a2; ... 

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
    std::cout << "Hello World!\n"; 
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
