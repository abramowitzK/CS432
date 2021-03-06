//
// Created by kyle on 2/3/16.
//

#include "Mesh.h"
#include "Vertex.h"

Mesh::Mesh(std::vector<vec4> points, std::vector<unsigned> indicies, std::vector<vec4> colors, std::vector<vec3> normals) {
    m_points = points;
    m_colors = colors;
    m_indices = indicies;
    m_normals = normals;
    m_vertices = std::vector<Vertex3D>();
}
Mesh::Mesh(){}

Mesh::~Mesh() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void Mesh::Init(GLint program) {
    GenerateVertices();
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex3D), m_vertices.data(), GL_STATIC_DRAW);
    //Generate ibo for object (index buffer)
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned), m_indices.data(), GL_STATIC_DRAW);
    GLint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(0));
    GLint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(vec4)));
    GLint vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(vec4)*2));

}

void Mesh::Draw(GLint program) {
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}

void Mesh::GenerateVertices(){
    for(int i = 0; i < m_points.size(); i++){
        Vertex3D vert;
        vert.Position = m_points[i];
        vert.Color = m_colors[i];
        vert.normal = m_normals[i];
        m_vertices.push_back(vert);
    }
}
