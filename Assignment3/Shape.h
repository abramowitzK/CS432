//
// Created by kyle on 1/10/16.
//
#ifndef SHAPE_H
#define SHAPE_H
#include <GL/glew.h>

class Shape
{
public:
    virtual ~Shape(){};
    virtual void Draw(GLuint program) = 0;
    virtual void Init(float angle) = 0;
    virtual void Update(float time) = 0;
    virtual void SetColor(vec4 color) = 0;
    virtual vec4 GetColor() const = 0;
};
#endif