//
// Created by kyle on 1/10/16.
//

#ifndef REGULAR_POLYGON_H
#define REGULAR_POLYGON_H
#include "Angel.h"
#include "Vertex.h"
#include "Shape.h"
#include <vector>

class RegularPolygon : public Shape{
public:

    RegularPolygon(unsigned int numSides, vec4 color, vec2 center, float radius);
    virtual void Init(float angle) override ;
    virtual void Update(float time) override ;
    virtual void Draw(GLuint program) override ;
    inline virtual void SetColor(vec4 color)
    {
        m_color = color;
    }
    inline vec4 GetColor() const
    {
        return m_color;
    }
protected:
    GLuint m_vbo;
    vec4 m_color;
    unsigned int m_numSides;
    vec2 m_center;
    std::vector<Vertex2D> m_vertices;
    float m_radius;
};


#endif
