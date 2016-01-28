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
    Ellipsoid(vec4 color, vec2 center, float radius, bool varyColor, float verticalScale, bool breathe);
    virtual void Init(float angle) override;
    virtual void Update(float time) override;
    virtual void Draw(GLuint program) override ;
    inline virtual void SetColor(vec4 color)
    {
        m_color = color;
    }
    inline vec4 GetColor() const {
        return m_color;
    }

private:
    bool m_breath;
    bool m_varyColor;
    GLuint m_vbo;
    vec4 m_color;
    vec2 m_center;
    std::vector<Vertex2D> m_vertices;
    float m_radius;
    float m_originalRadius;
    float m_verticalScale;
};


#endif
