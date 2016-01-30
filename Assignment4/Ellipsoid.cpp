//
// Created by kyle on 1/10/16.
//

#include "Ellipsoid.h"
Ellipsoid::Ellipsoid(vec4 color, vec2 center, float radius, bool varyColor, float verticalScale, bool breathe)
{
    m_verticalScale = verticalScale;
    m_varyColor = varyColor;
    m_color = color;
    m_center = center;
    m_vertices = std::vector<Vertex2D>();
    m_radius = radius;
    m_originalRadius = radius;
    m_breath = breathe;
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
void Ellipsoid::Update(float time)
{
    m_radius = m_originalRadius * fabs(sin(1/360.0*time));
    glDeleteBuffers(1, &m_vbo);
    m_vertices.clear();
    if(m_breath) {
        glDeleteBuffers(1, &m_vbo);
        const int numIter = 360;
        vec4 base = m_color;
        vec4 tempColor;
        for(int i = 0; i < numIter; i++) {
            if(m_varyColor){
                tempColor = base *(2.0 * M_PI * i / (double)numIter)/(2.0*M_PI);
            }
            else
                tempColor = base;
            m_vertices.push_back(Vertex2D(vec2((float)(m_center.x + (m_radius) * cos(2 * M_PI * i / numIter)),
                                               (float)(m_center.y + (m_radius) * sin(2 * M_PI * i / numIter) * m_verticalScale)), tempColor ));
        }
        glGenBuffers( 1, &m_vbo);
        glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
        glBufferData( GL_ARRAY_BUFFER, ((unsigned int)m_vertices.size())*sizeof(Vertex2D), &m_vertices[0], GL_STATIC_DRAW );
    }
}
void Ellipsoid::Init(float angle) {
	const int numIter = 360;
	vec4 base = m_color;
	vec4 tempColor;
    for(int i = 0; i < numIter; i++) {
        if(m_varyColor){
            tempColor = base *(2.0 * M_PI * i / (double)numIter)/(2.0*M_PI);
        }
		else
			tempColor = base;
        m_vertices.push_back(Vertex2D(vec2((float)(m_center.x + m_radius * cos(2 * M_PI * i / numIter)),
                                           (float)(m_center.y + m_radius * sin(2 * M_PI * i / numIter) * m_verticalScale)), tempColor ));
    }
 //   m_vertices.push_back(Vertex2D(m_vertices[numIter-1].Position, m_vertices[numIter-1].Color));
    glGenBuffers( 1, &m_vbo);
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER, ((unsigned int)m_vertices.size())*sizeof(Vertex2D), &m_vertices[0], GL_STATIC_DRAW );

}
