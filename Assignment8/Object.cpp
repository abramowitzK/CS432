//
// Created by kyle on 1/30/16.
//

#include "Object.h"
#include "Vertex.h"
#include "BezierPointReader.h"

Object::Object(Mesh mesh) {
    m_translation = vec4(0.0f,0.0f,0.0f,1.0f);
    m_rotation = vec3(0.0f, 90.0f, 0.0f);
    m_scale = vec3(1.0f, 1.0f, 1.0f);
    m_mesh = mesh;
    m_radius = 25;
    m_speed = 1.0;
    m_height = 10.0;
    m_eye = vec4(0, 0, -10.0, 1.0);
    m_angle = 0.0;
}

Object::~Object() {
}
void Object::Init(GLuint program) {
    m_mLocation =  glGetUniformLocation(program, "mMatrix");
    m_vLocation = glGetUniformLocation(program, "vMatrix");
    m_pLocation = glGetUniformLocation(program, "pMatrix");
    m_fViewLocation = glGetUniformLocation(program, "fView");
    m_colorLocation = glGetUniformLocation(program, "color");
    m_fboLocation = glGetUniformLocation(program, "fbo");
    m_mesh.Init(program);
}

void Object::Draw(GLint program) {
    glUseProgram(program);
    glUniform1i(m_fboLocation, GL_FALSE);
    mat4 v = Angel::LookAt(m_eye, vec4(0.0,0.0,0.0, 1.0), vec4(0.0,1.0,0.0,1.0));
    glUniformMatrix4fv(m_mLocation, 1, GL_TRUE, GetTransform());
    if(!m_selected)
        glUniform1i(m_colorLocation, m_color);
    else
        glUniform1i(m_colorLocation, 3);
    mat4 proj = Angel::Perspective(30.0f, 1.0, 0.1f, 1000.0f);
    glUniformMatrix4fv(m_vLocation, 1, GL_TRUE,  v);
    glUniformMatrix4fv(m_fViewLocation,1,GL_TRUE, v);
    glUniformMatrix4fv(m_pLocation,1, GL_TRUE, proj);
    m_mesh.Draw(program);
}

void Object::Update(float time) {
    float x = m_radius*cosf(m_angle);
    float z = m_radius*sinf(m_angle);
    m_eye.x = x;
    m_eye.z = z;
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


void Object::DrawToFBO(GLint program) {
    glUseProgram(program);
    glUniform1i(m_fboLocation, GL_TRUE);
    mat4 v = Angel::LookAt(m_eye, vec4(0.0,0.0,0.0, 1.0), vec4(0.0,1.0,0.0,1.0));
    glUniformMatrix4fv(m_mLocation, 1, GL_TRUE, GetTransform());
    if(!m_selected)
        glUniform1i(m_colorLocation, m_color);
    else
        glUniform1i(m_colorLocation, 3);
    mat4 proj = Angel::Perspective(30.0f, 1.0, 0.1f, 1000.0f);
    glUniformMatrix4fv(m_vLocation, 1, GL_TRUE,  v);
    glUniformMatrix4fv(m_fViewLocation,1,GL_TRUE, v);
    glUniformMatrix4fv(m_pLocation,1, GL_TRUE, proj);
    m_mesh.Draw(program);
}
