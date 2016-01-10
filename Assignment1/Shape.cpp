//
// Created by kyle on 1/10/16.
//

#include "Shape.h"
Shape::Shape(unsigned int numSides, vec4 color, vec2 center, float radius) {
    m_numSides = numSides;
    m_color = color;
    m_center = center;
    m_vertices = std::vector<vec2>();
    m_radius = radius;
}

void Shape::Init() {
    m_vertices.push_back(m_center);
    for(int i = 0; i < m_numSides; i++) {
        m_vertices.push_back(vec2((float)(m_center.x + m_radius * cos(2 * M_PI * i / m_numSides)),
                                  (float)(m_center.y + m_radius * sin(2 * M_PI * i / m_numSides))));
    }
    m_vertices.push_back(m_vertices[1]);
    glGenBuffers( 1, &m_vbo);
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER, ((unsigned int)m_vertices.size())*sizeof(vec2), &m_vertices[0], GL_STATIC_DRAW );
}

void Shape::Draw(GLuint program) {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    GLuint colorLoc = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, sizeof(vec2),
                           BUFFER_OFFSET(0) );
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer( colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(vec4),
                          BUFFER_OFFSET(0) );
    glDrawArrays(GL_TRIANGLE_FAN, 0 , (unsigned int)m_vertices.size());
    glDisableVertexAttribArray(loc);
    glDisableVertexAttribArray(colorLoc);
}
