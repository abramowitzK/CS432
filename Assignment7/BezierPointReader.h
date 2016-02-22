//
// Created by kyle on 2/22/16.
//

#ifndef ASSIGNMENT5_BEZIERPOINTREADER_H
#define ASSIGNMENT5_BEZIERPOINTREADER_H
#include "Mesh.h"
#include "Vertex.h"
#include <Angel.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

class BezierPointReader {
public:
    BezierPointReader();
    void LoadFile(std::string filename);
    Mesh GetMesh(int sampling);
    vec4 GetPointOnBezierSurface(float u, float v);
private:
    vec3 ParseVertex(std::string line);
    float Bernstein(float t, int i);
    Mesh TesselateBezierPatch(int sampling);
    vec3 m_controlPoints[4][4];

    void CalcFaceNormals(int triangle, const std::vector<unsigned int> &indices, const std::vector<vec4> &vertices,
                         std::vector<vec3> &faceNormals);

    void CalcVertexNormals(const std::vector<unsigned int> &indices, const std::vector<vec3> &faceNormals,
                           std::vector<vec3> &normals);
};


#endif //ASSIGNMENT5_BEZIERPOINTREADER_H
