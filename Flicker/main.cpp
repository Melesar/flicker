#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>

int main(int argc, char** argv)
{
    Assimp::Importer importer;
    const aiScene* carModel = importer.ReadFile("resources/Car.fbx", 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

    std::cout << "Importer created" << std::endl;
}
