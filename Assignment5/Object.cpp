//
// Created by kyle on 1/30/16.
//

#include "Object.h"
#include "Vertex.h"

Object::Object(Mesh mesh) {
    m_translation = vec4(0.0f,0.0f,0.0f,1.0f);
    m_rotation = vec3(30.0f, 30.0f, 0.0f);
    m_scale = vec3(1.0f, 1.0f, 1.0f);
    m_vbo = 0;
    m_ibo = 0;
    m_mesh = mesh;
}



Object::~Object() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void Object::Init(GLuint program) {
       m_uniformLocation =  glGetUniformLocation(program, "mvMatrix");
       m_mesh.Init(program);
}

void Object::Draw(GLint program) {
    //view cube from -5 units away in the z direction
    mat4 mv = GetTransform();
    mat4 proj = Angel::Perspective(30.0f, 1.0, 0.1f, 1000.0f);
    proj*=mv;
    glUniformMatrix4fv(m_uniformLocation, 1, GL_TRUE, proj);
    m_mesh.Draw(program);
}

void Object::Update(float time) {

    //Only needed if we're updating animation or physics or something like that.
}

void Object::RotateX(float x) {
    m_rotation.x += x;
}

void Object::RotateY(float y) {
    m_rotation.y += y;
}
void Object::RotateZ(float z){
    m_rotation.z += z;
}
void Object::Translate(float x, float y, float z) {
    m_translation.x += x;
    m_translation.y += y;
    m_translation.z += z;
}

void Object::Scale(float x, float y, float z) {
    m_scale.x += x;
    m_scale.y += y;
    m_scale.z += z;
}

mat4 Object::GetTransform(){
    //Called each frame. Constructs transformation matrix from transformation data
    mat4 scale = Angel::Scale(m_scale);
    mat4 rotation = Angel::RotateX(m_rotation.x)* Angel::RotateY(m_rotation.y) * Angel::RotateZ(m_rotation.z);
    mat4 translation = Angel::Translate(m_translation);
    return  translation * rotation * scale;
}

void Object::Reset() {
    //Reset to initial position
    m_translation = vec4(0.0f,0.0f,0.0f,1.0f);
    m_rotation = vec3(30.0f, 30.0f, 0.0f);
    m_scale = vec3(1.0f, 1.0f, 1.0f);
}

