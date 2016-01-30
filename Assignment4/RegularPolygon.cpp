//
// Created by kyle on 1/10/16.
//

#include "RegularPolygon.h"
RegularPolygon::RegularPolygon(unsigned int numSides, vec4 color, vec2 center, float radius) {
    m_numSides = numSides;
    m_color = color;
    m_center = center;
    m_vertices = std::vector<Vertex2D>();
    m_radius = radius;
}

void RegularPolygon::Init(float angle) {
    m_vertices.push_back(Vertex2D(m_center, m_color));
    for(unsigned int i = 0; i < m_numSides; i++) {
        m_vertices.push_back(Vertex2D(vec2((float)(m_center.x + m_radius * cos(2 * M_PI * i / m_numSides+ M_PI/4 + angle)),
                                  (float)(m_center.y + m_radius * sin(2 * M_PI * i / m_numSides + M_PI/4 + angle))), m_color));
    }
    m_vertices.push_back(m_vertices[1]);
    glGenBuffers( 1, &m_vbo);
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER, ((unsigned int)m_vertices.size())*sizeof(Vertex2D), &m_vertices[0], GL_STATIC_DRAW );
}
void RegularPolygon::Update(float time) {
    glDeleteBuffers(1, &m_vbo);
    m_vertices.clear();
    Init(time * M_PI/360);
}
void RegularPolygon::Draw(GLuint program) {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    GLuint colorLoc = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
                           BUFFER_OFFSET(0) );
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer( colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D),
                          BUFFER_OFFSET(sizeof(vec2)) );
    glDrawArrays(GL_TRIANGLE_FAN, 0 , (unsigned int)m_vertices.size());
    glDisableVertexAttribArray(loc);
    glDisableVertexAttribArray(colorLoc);
}
