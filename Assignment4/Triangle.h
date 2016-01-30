//
// Created by kyle on 1/10/16.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "Angel.h"
#include "Shape.h"
#include "Vertex.h"
#include <vector>

class Triangle : public Shape{
public:
    Triangle(vec4 vert1Color, vec4 vert2Color, vec4 vert3Color, float radius, vec2 center);
    virtual void Init(float angle) override;
    virtual void Update(float time) override;
    virtual void Draw(GLuint program) override;
    inline virtual void SetColor(vec4 color)
    {
        //no op here
    }
    inline vec4 GetColor() const {
        return vec4(0.0);
    }

private:
    GLuint m_vbo;
    std::vector<vec4> m_colors;
    vec2 m_center;
    std::vector<Vertex2D> m_vertices;
    float m_radius;
};


#endif
