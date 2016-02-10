//
// Created by kyle on 2/3/16.
//

#include "Mesh.h"
#include "Vertex.h"

Mesh::Mesh(std::vector<vec4> points, std::vector<vec4> colors, std::vector<vec3> normals) {
    m_points = points;
    m_colors = colors;
    m_normals = normals;
    m_vertices = std::vector<Vertex3D>();
}
Mesh::Mesh(){}

Mesh::~Mesh() {
    glDeleteBuffers(1, &m_vbo);
}

void Mesh::Init(GLint program) {
    GenerateVertices();
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex3D), m_vertices.data(), GL_STATIC_DRAW);
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
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
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
