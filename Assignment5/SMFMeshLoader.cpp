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
    while(!in.eof()){
        std::string line;
        std::getline(in, line);
        if(line[0] == 'f'){
            //face
            ParseFace(indices, line);
            colors.push_back(vec4(0.5));
        } else if (line[0] == 'v'){
            //vertex
            ParseVertex(vertices, line);
            colors.push_back(vec4(0.5));
        }
    }
    m_resourceMap[filename] = Mesh(vertices,indices,colors);
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


