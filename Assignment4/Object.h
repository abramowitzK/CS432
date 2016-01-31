//
// Created by kyle on 1/30/16.
//

#ifndef ASSIGNMENT4_OBJECT_H
#define ASSIGNMENT4_OBJECT_H


#include <GL/glew.h>
#include <vector>
#include "Vertex.h"

class Object {

public:
    Object();
    virtual ~Object();
    virtual void Init(GLuint program);
    virtual void Draw(GLint program);
    virtual void Update(float time);
    void RotateX(float x);
    void RotateY(float y);
    void RotateZ(float z);
    void Translate(float x, float y, float z);
    void Scale(float x, float y, float z);
    mat4 GetTransform();
    void Reset();
private:
    std::vector<unsigned> m_indices;
    vec4 m_translation;
    vec3 m_rotation;
    vec3 m_scale;
    GLuint m_ibo;
    GLuint m_vbo;
    GLuint m_uniformLocation;
};


#endif //ASSIGNMENT4_OBJECT_H
