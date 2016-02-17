//
// Created by kyle on 1/30/16.
//

#include "Object.h"
#include "Vertex.h"

Object::Object(Mesh mesh) {
    m_translation = vec4(0.0f,0.0f,0.0f,1.0f);
    m_rotation = vec3(0.0f, 90.0f, 0.0f);
    m_scale = vec3(1.0f, 1.0f, 1.0f);
    m_vbo = 0;
    m_ibo = 0;
    m_mesh = mesh;
    m_stop = false;
    m_radius = 3;
    m_para = false;
    m_speed = 1.0;
    m_height = 0.0;
    m_eye = vec4(-3.0, m_height, 0.0, 1.0);
    m_gouraud = true;
    m_usePhong = false;
    m_mat = 1;
    m_lightAngle = 180.0f;
    m_lightLocation = vec3();
    m_lightHeight = 0.0;
    m_lightRadius = 5.0;
}



Object::~Object() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void Object::Init(GLuint program) {
    m_mLocation =  glGetUniformLocation(program, "mMatrix");
    m_vLocation = glGetUniformLocation(program, "vMatrix");
    m_pLocation = glGetUniformLocation(program, "pMatrix");
    m_gouraudLocation = glGetUniformLocation(program, "gouraud");
    m_usePhongLocation = glGetUniformLocation(program, "usePhong");
    m_fViewLocation = glGetUniformLocation(program, "fView");
    m_fMatLocation = glGetUniformLocation(program, "fMaterial");
    m_vMatLocation = glGetUniformLocation(program, "vMaterial");
    m_vlightPosLocation = glGetUniformLocation(program, "vlight2pos");
    m_flightPosLocation = glGetUniformLocation(program, "flight2pos");
    m_mesh.Init(program);
    m_lightLocation.x = cosf(m_lightAngle) * m_lightRadius;
    m_lightLocation.y = m_lightHeight;
    m_lightLocation.z = sinf(m_lightAngle) * m_lightRadius;
}

void Object::Draw(GLint program) {
    //view cube from -5 units away in the z direction
    glUniform1i(m_gouraudLocation, m_gouraud);
    glUniform1i(m_usePhongLocation, m_usePhong);
    glUniform1i(m_vMatLocation, m_mat);
    glUniform1i(m_fMatLocation, m_mat);
    glUniform3fv(m_vlightPosLocation,1,m_lightLocation);
    glUniform3fv(m_flightPosLocation,1,m_lightLocation);
    mat4 v = Angel::LookAt(m_eye,vec4(0.0,0.0,0.0,1.0), vec4(0.0,1.0,0.0,1.0));
    glUniformMatrix4fv(m_mLocation, 1, GL_TRUE, GetTransform());
    mat4 proj;
    if(!m_para)
        proj = Angel::Perspective(30.0f, 1.0, 0.1f, 1000.0f);
    else
        proj= Angel::Ortho(-1.0, 1.0, -1.0, 1.0, 0.1f, 1000.0f);
    glUniformMatrix4fv(m_vLocation, 1, GL_TRUE,  v);
    glUniformMatrix4fv(m_fViewLocation, 1, GL_TRUE, v);
    glUniformMatrix4fv(m_pLocation,1, GL_TRUE, proj);
    m_mesh.Draw(program);
}

void Object::Update(float time) {
    float x = m_radius * cosf(time / 360.0 * m_speed);
    float z = m_radius * sinf(time / 360.0 * m_speed);
    m_eye.x = x;
    m_eye.z = z;
    m_eye.y = m_height;
    m_lightLocation.x = cosf(m_lightAngle)*m_lightRadius;
    m_lightLocation.y = m_lightHeight;
    m_lightLocation.z = sinf(m_lightAngle)*m_lightRadius;

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

