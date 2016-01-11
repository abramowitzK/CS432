//
// Created by kyle on 1/10/16.
//

#ifndef ASSIGNMENT1_SHAPE_H
#define ASSIGNMENT1_SHAPE_H
#include "Angel.h"
#include "Vertex.h"
#include "Shape.h"
#include <vector>

class RegularPolygon : public Shape{
public:

    RegularPolygon(unsigned int numSides, vec4 color, vec2 center, float radius);
    virtual void Init() override ;
    virtual void Draw(GLuint program) override ;
protected:
    GLuint m_vbo;
    vec4 m_color;
    unsigned int m_numSides;
    vec2 m_center;
    std::vector<Vertex2D> m_vertices;
    float m_radius;
};


#endif //ASSIGNMENT1_SHAPE_H
