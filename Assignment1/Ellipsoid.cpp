//
// Created by kyle on 1/10/16.
//

#include "Ellipsoid.h"
Ellipsoid::Ellipsoid(vec4 color, vec2 center, float radius, bool varyColor, float verticalScale = 1.0)
{
    m_verticalScale = verticalScale;
    m_varyColor = varyColor;
    m_color = color;
    m_center = center;
    m_vertices = std::vector<Vertex2D>();
    m_radius = radius;
}
void Ellipsoid::Draw(GLuint program) {
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

void Ellipsoid::Init() {
    m_vertices.push_back(Vertex2D(m_center, m_color));
    for(int i = 0; i < 100; i++) {
        if(m_varyColor){
            m_color.x = m_color.x *(2.0 * M_PI * i / 100.0)/(2.0*M_PI);
        }
        m_vertices.push_back(Vertex2D(vec2((float)(m_center.x + m_radius * cos(2 * M_PI * i / 100)),
                                           (float)(m_center.y + m_radius * sin(2 * M_PI * i / 100) * m_verticalScale)), m_color ));
    }
    m_vertices.push_back(m_vertices[1]);
    glGenBuffers( 1, &m_vbo);
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER, ((unsigned int)m_vertices.size())*sizeof(Vertex2D), &m_vertices[0], GL_STATIC_DRAW );

}
