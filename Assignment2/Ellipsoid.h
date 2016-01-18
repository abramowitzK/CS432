//
// Created by kyle on 1/10/16.
//

#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "Angel.h"
#include "Shape.h"
#include "Vertex.h"
#include <vector>

class Ellipsoid : public Shape{
public:
    Ellipsoid(vec4 color, vec2 center, float radius, bool varyColor, float verticalScale);
    virtual void Init();

    virtual void Draw(GLuint program);

private:
    bool m_varyColor;
    GLuint m_vbo;
    vec4 m_color;
    vec2 m_center;
    std::vector<Vertex2D> m_vertices;
    float m_radius;
    float m_verticalScale;
};


#endif
