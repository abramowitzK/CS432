//
// Created by kyle on 2/22/16.
//

#include "BezierPointReader.h"
#include "StringUtils.h"
#include "Vertex.h"

BezierPointReader::BezierPointReader(){

}
void BezierPointReader::LoadFile(std::string filename){
    std::ifstream in;
    in.open(filename);
    std::string line;
    //Read in the control points
    int i = 0;
    int j = 0;
    while(std::getline(in, line)){
        m_controlPoints[i/4][j%4] = ParseVertex(line);
        i++;
        j++;
    }

}
Mesh BezierPointReader::GetMesh(int sampling ){
    return TesselateBezierPatch(sampling);
}

vec3 BezierPointReader::ParseVertex(std::string line) {
    //Split line on space delimiter
    std::vector<std::string> split = splitLine(line, ' ');
    vec3 ret = vec3(1.0);
    for(int i = 0; i < 3; i++){
        if(i < 2)
            ret[i] = std::stof(split[i]);
        else
            ret[i] = std::stof(split[i]);

    }
    return ret;
}

Mesh BezierPointReader::TesselateBezierPatch(int sampling) {

    float deltaI = (float) (1.0 / (float)(sampling-1.0));
    float deltaJ = deltaI;

    vec4 samples[sampling][sampling];
    vec2 UV[sampling][sampling];
    //Get all the points that we need
    for(int i = 0; i < sampling; i++){
        for(int j = 0; j < sampling; j++){
            samples[i][j] = GetPointOnBezierSurface(deltaI*i, deltaJ*j);
            UV[i][j] = vec2(deltaI*i, deltaJ*j);
        }

    }
    std::vector<vec4> vertices = std::vector<vec4>();
    std::vector<vec4> colors=std::vector<vec4>();
    std::vector<unsigned> indices=std::vector<unsigned>();
    std::vector<vec2> uv = std::vector<vec2>();
    for(int i = 0; i < sampling; i++){
        for(int j = 0; j < sampling; j++){
            //Push vertices back one row at a time
            vertices.push_back(samples[i][j]);
            uv.push_back(UV[i][j]);
                colors.push_back(vec4(0.5));
        }
    }
    for(int i = 0; i < sampling-1; i++){
        for(int j = 0; j < sampling-1; j++){
            indices.push_back(i*sampling +j);
            indices.push_back(i*sampling + j+1);
            indices.push_back(i*sampling + sampling + j);
            indices.push_back(i*sampling + j + 1);
            indices.push_back(i*sampling + sampling + j + 1);
            indices.push_back(i*sampling + sampling + j);
        }
    }
    std::vector<vec3> normals=std::vector<vec3>();
    std::vector<vec3> faceNormals=std::vector<vec3>();

    normals.resize(indices.size());
    /*for(int i = 0; i<faceNormals.size(); i++){
        CalcFaceNormals(i,indices,vertices,faceNormals);
    }*/
    for(int i = 0; i < indices.size(); i+=3){
        vec4 p1 = vertices[indices[i]];
        vec4 p2 = vertices[indices[i+1]];
        vec4 p3 = vertices[indices[i+2]];
        vec4 u = p2 - p1;
        vec4 v = p3 - p1;
        vec3 n = Angel::cross(v,u);
        faceNormals.push_back(vec3(n.x,n.y,n.z));
    }
    for(unsigned int i = 0; i < indices.size(); i++){
        unsigned f = i/3;
        unsigned v = indices[i];
        normals[v] += faceNormals[f];
    }
    for(int i = 0; i < normals.size(); i++){
        normals[i] = Angel::normalize(normals[i]);
    }
    //CalcVertexNormals(indices,faceNormals,normals);
    return Mesh(vertices, indices,colors,normals, uv);


}

vec4 BezierPointReader::GetPointOnBezierSurface(float u, float v) {
    float x,y,z;
    vec4 ret(0.0);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            ret+=m_controlPoints[i][j]*Bernstein(u,j)*Bernstein(v,i);
        }
    }
    ret[3] = 1.0;
    return ret;
}

float BezierPointReader::Bernstein(float t, int i){
    switch (i){
        case 0:
            return (float) pow(1.0 - t, 3.0);
        case 1:
            return (float)(3.0*t*pow(1.0-t, 2.0));
        case 2:
            return (float)(3.0*pow(t,2.0)*(1.0-t));
        case 3:
            return (float)pow(t,3.0);
    }
}
void BezierPointReader::CalcFaceNormals(int triangle, const std::vector<unsigned> &indices, const std::vector<vec4> &vertices, std::vector<vec3>& faceNormals) {
    vec4 p1 = vertices[indices[triangle]];
    vec4 p2 = vertices[indices[triangle+1]];
    vec4 p3 = vertices[indices[triangle+2]];
    vec4 u = p2 - p1;
    vec4 v = p3 - p1;
    vec3 n = Angel::cross(u,v);
    faceNormals[triangle] = vec3(n.x,n.y,n.z);
}
void BezierPointReader::CalcVertexNormals(const std::vector<unsigned> &indices, const std::vector<vec3> &faceNormals, std::vector<vec3>& normals) {
    for(int i = 0; i < indices.size(); i++){
        unsigned f = i/3;
        unsigned v = indices[i];
        normals[v] += faceNormals[f];
        Angel::normalize(normals[v]);
    }
}

std::vector<Vertex3D> BezierPointReader::GetControlPoints() {
    std::vector<Vertex3D> ret;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            Vertex3D vert;
            vert.Position = m_controlPoints[i][j];
            vert.Color = vec4(0.0,1.0,0.0,1.0);
            vert.normal = vec3(0.0,0.0,0.0);
            ret.push_back(vert);
        }
    }
    return ret;
}
