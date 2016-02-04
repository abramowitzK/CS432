//
// Created by kyle on 2/3/16.
//

#ifndef ASSIGNMENT5_MESH_H
#define ASSIGNMENT5_MESH_H

#include <vector>
#include "Angel.h"
#include "Vertex.h"
class Mesh {
public:
    Mesh(std::vector<vec4> points, std::vector<unsigned> indicies, std::vector<vec4> colors, std::vector<vec3> normals);
    Mesh();
    ~Mesh();
    void Init(GLint program);
    void Draw(GLint program);

private:
    void GenerateVertices();
    std::vector<vec4> m_points;
    std::vector<unsigned> m_indices;
    std::vector<vec4> m_colors;
    std::vector<Vertex3D> m_vertices;
    std::vector<vec3> m_normals;
    GLuint m_vbo;
    GLuint m_ibo;
};


#endif //ASSIGNMENT5_MESH_H
