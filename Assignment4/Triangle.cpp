//
// Created by kyle on 1/10/16.
//

#include "Triangle.h"

Triangle::Triangle(vec4 vert1Color, vec4 vert2Color, vec4 vert3Color, float radius, vec2 center) {
    m_center = center;
    m_vertices = std::vector<Vertex2D>();
    m_radius = radius;
    m_colors = std::vector<vec4>();
    m_colors.push_back(vert1Color);
    m_colors.push_back(vert2Color);
    m_colors.push_back(vert3Color);
}

void Triangle::Init(float angle) {
    for(int i = 0; i < 3; i++) {
        m_vertices.push_back(Vertex2D(vec2((float)(m_center.x + m_radius * cos(2 * M_PI * i / 3 - (M_PI/6))),
                                           (float)(m_center.y + m_radius * sin(2 * M_PI * i / 3 - (M_PI/6)))), m_colors[i] ));
    }
    m_vertices.push_back(m_vertices[1]);
    glGenBuffers( 1, &m_vbo);
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER, ((unsigned int)m_vertices.size())*sizeof(Vertex2D), &m_vertices[0], GL_STATIC_DRAW );
}
void Triangle::Update(float time) { }
void Triangle::Draw(GLuint program) {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    GLuint colorLoc = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
                           BUFFER_OFFSET(0) );
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer( colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
                           BUFFER_OFFSET(sizeof(vec2)) );
    glDrawArrays(GL_TRIANGLES, 0 , (unsigned int)m_vertices.size());
    glDisableVertexAttribArray(loc);
    glDisableVertexAttribArray(colorLoc);

}
