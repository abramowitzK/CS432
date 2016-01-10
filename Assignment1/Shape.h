//
// Created by kyle on 1/10/16.
//

#ifndef ASSIGNMENT1_SHAPE_H
#define ASSIGNMENT1_SHAPE_H
#include "Angel.h"
#include <vector>
class Shape {
public:

    Shape(unsigned int numSides, vec4 color, vec2 center, float radius);


    virtual void Init();
    virtual void Draw(GLuint program);
protected:
    GLuint m_vbo;
    vec4 m_color;
    unsigned int m_numSides;
    vec2 m_center;
    std::vector<vec2> m_vertices;
    float m_radius;
};


#endif //ASSIGNMENT1_SHAPE_H
