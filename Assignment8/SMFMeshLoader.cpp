//
// Created by kyle on 2/3/16.
//

#include "SMFMeshLoader.h"

SMFMeshLoader::SMFMeshLoader() {
    m_resourceMap = std::map<std::string, Mesh>();
}

void SMFMeshLoader::LoadFile(std::string filename) {
    //Create an input filestream
    std::ifstream in;
    in.open(filename);
    std::vector<vec4> vertices;
    std::vector<unsigned> indices;
    std::vector<vec4> colors;
    std::vector<vec3> faceNormals;
    std::vector<vec3> normals;
    std::string line;
    while(std::getline(in,line)){
        if(line[0] == 'f'){
            //face
            ParseFace(indices, line);
            colors.push_back(vec4(1.0,0.0,0.0,1.0));
        } else if (line[0] == 'v'){
            //vertex
            ParseVertex(vertices, line);
            colors.push_back(vec4(1.0,0.0,0.0,1.0));
        }
    }
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
        vec3 n = Angel::cross(u,v);
        faceNormals.push_back(vec3(n.x,n.y,n.z));
    }
    for(int i = 0; i < indices.size(); i++){
        unsigned f = i/3;
        unsigned v = indices[i];
        normals[v] += faceNormals[f];
    }
    for(int i = 0; i < normals.size(); i++){
        normals[i] = Angel::normalize(normals[i]);
    }
    m_resourceMap[filename] = Mesh(vertices,indices,colors,normals);
    //std::cout << normals[105] << std::endl;
}

Mesh SMFMeshLoader::GetMesh(std::string filename) {
    return m_resourceMap[filename];
}

/**
 * Precondition - Line is a 3d vertex line (ie in format "v 1.0 2.0 3.0")
 */
void SMFMeshLoader::ParseVertex(std::vector<vec4> &vertices, const std::string line) {
    //Split line on space delimiter
    std::vector<std::string> split = splitLine(line, ' ');
    vec4 ret = vec4(1.0);
    for(int i = 1; i < 4; i++){
        ret[i-1] = std::stof(split[i]);
    }
    vertices.push_back(ret);
}

void SMFMeshLoader::ParseFace(std::vector<unsigned> &indices, const std::string line) {
    std::vector<std::string> split = splitLine(line, ' ');
    for(int i = 1; i < 4; i++){
       indices.push_back((unsigned)std::stoul(split[i])-1);
    }
}


void SMFMeshLoader::CalcFaceNormals(int triangle, const std::vector<unsigned> &indices, const std::vector<vec4> &vertices, std::vector<vec3>& faceNormals) {
    vec4 p1 = vertices[indices[triangle]];
    vec4 p2 = vertices[indices[triangle+1]];
    vec4 p3 = vertices[indices[triangle+2]];
    vec4 u = p2 - p1;
    vec4 v = p3 - p1;
    vec3 n = Angel::cross(u,v);
    faceNormals[triangle] = vec3(n.x,n.y,n.z);
}
void SMFMeshLoader::CalcVertexNormals(const std::vector<unsigned> &indices, const std::vector<vec3> &faceNormals, std::vector<vec3>& normals) {
    for(int i = 0; i < indices.size(); i++){
        unsigned f = i/3;
        unsigned v = indices[i];
        normals[v] += faceNormals[f];
        Angel::normalize(normals[v]);
    }
}
