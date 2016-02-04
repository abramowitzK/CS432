//
// Created by kyle on 1/30/16.
//

#ifndef ASSIGNMENT4_OBJECT_H
#define ASSIGNMENT4_OBJECT_H

#include <GL/glew.h>
#include <vector>
#include <string>
#include "Vertex.h"
#include "Mesh.h"
class Object {

public:
    Object(Mesh mesh);
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
    Mesh m_mesh;
    vec4 m_translation;
    vec3 m_rotation;
    vec3 m_scale;
    GLuint m_ibo;
    GLuint m_vbo;
    GLint m_uniformLocation;
};


#endif //ASSIGNMENT4_OBJECT_H
