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
    virtual void Init() = 0;
};
#endif