//
// Created by kyle on 2/3/16.
//

#ifndef ASSIGNMENT5_SMFLOADER_H
#define ASSIGNMENT5_SMFLOADER_H
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Angel.h"
#include "StringUtils.h"
class SMFMeshLoader {
public:
    SMFMeshLoader();
    void LoadFile(std::string filename);
    Mesh GetMesh(std::string filename);
private:
    void CalcNormals(int triangle,std::vector<vec4> vertices, std::vector<vec3>& normals);
    void ParseVertex(std::vector<vec4> &vertices, const std::string line);
    void ParseFace(std::vector<unsigned> &indices, const std::string line);
private:
    std::map<std::string, Mesh> m_resourceMap;
};


#endif //ASSIGNMENT5_SMFLOADER_H
