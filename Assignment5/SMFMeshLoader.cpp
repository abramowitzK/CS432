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
    std::vector<vec3> normals;
    while(!in.eof()){
        std::string line;
        std::getline(in, line);
        if(line[0] == 'f'){
            //face
            ParseFace(indices, line);
        } else if (line[0] == 'v'){
            //vertex
            ParseVertex(vertices, line);
        }
    }
    std::vector<vec4> newVerts;
    for(int i = 0; i < indices.size(); i++){
        vec4 temp = vertices[indices[i]];
        newVerts.push_back(vec4(temp.x,temp.y,temp.z, 1.0));
        colors.push_back(vec4(1.0,0.0,0.0,1.0));
    }
    for(int i = 0; i<newVerts.size(); i+=1){
        CalcNormals(i,newVerts,normals);
    }
    m_resourceMap[filename] = Mesh(newVerts,colors,normals);
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


void SMFMeshLoader::CalcNormals(int triangle, std::vector<vec4> vertices, std::vector<vec3>& normals) {
    vec4 p1 = vertices[triangle];
    vec4 p2 = vertices[triangle+1];
    vec4 p3 = vertices[triangle+2];
    vec4 u = p2 - p1;
    vec4 v = p3 - p1;
    vec3 n = Angel::cross(u,v);
    n = Angel::normalize(n);
    //Assign the same normal to each vertex of the triangle
    /*for(int i = 0; i < 3; i++) {
        normals.push_back(vec3(n.x, n.y, n.z));
    }*/
    normals.push_back(vec3(n.x,n.y,n.z));
    normals.push_back(vec3(n.x,n.y,n.z));
    normals.push_back(vec3(n.x,n.y,n.z));
    //std::cout << n.x << n.y << n.z << std::endl;
}
