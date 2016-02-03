//
// Created by kyle on 1/30/16.
//

#include "Object.h"
#include "Vertex.h"

Object::Object() {
    m_translation = vec4(0.0f,0.0f,0.0f,1.0f);
    m_rotation = vec3(30.0f, 30.0f, 0.0f);
    m_scale = vec3(1.0f, 1.0f, 1.0f);
    m_vbo = 0;
    m_ibo = 0;
    m_indices = std::vector<unsigned>(36);
}

Object::~Object() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void Object::Init(GLuint program) {

    Vertex3D temp[8];
    temp[0].Position = vec4(-0.5, -0.5, 0.5, 1.0);
    temp[0].Color = vec4(0.0,0.0,0.0,1.0);
    temp[1].Position =vec4(-0.5, 0.5, 0.5, 1.0);
    temp[1].Color =vec4(1.0,0.0,0.0,1.0);
    temp[2].Position =vec4(0.5, 0.5, 0.5, 1.0);
    temp[2].Color =vec4(1.0,1.0,0.0,1.0);
    temp[3].Position =vec4(0.5, -0.5, 0.5, 1.0);
    temp[3].Color =vec4(0.0,1.0,0.0,1.0);
    temp[4].Position =vec4(-0.5, -0.5, -0.5, 1.0);
    temp[4].Color =vec4(0.0,0.0,1.0,1.0);
    temp[5].Position =vec4(-0.5, 0.5, -0.5, 1.0);
    temp[5].Color =vec4(1.0,0.0,1.0,1.0);
    temp[6].Position =vec4(0.5, 0.5, -0.5, 1.0);
    temp[6].Color =vec4(1.0,1.0,1.0,1.0);
    temp[7].Position =vec4(0.5, -0.5f, -0.5f, 1.0);
    temp[7].Color =vec4(0.0,1.0,1.0,1.0);
    //Set up vertices and colors for those vertices;
    unsigned indices[36]= {
            1,0,3,
            1,3,2,
            2,3,7,
            2,7,6,
            3,0,4,
            3,4,7,
            6,5,1,
            6,1,2,
            4,5,6,
            4,6,7,
            5,4,0,
            5,0,1
    };
    //Save the indices for later in case we want to do something with them
    for(unsigned i = 0; i < 36; i++) {
        m_indices[i] = indices[i];
    }
    //Generate vbo for object
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 8*sizeof(Vertex3D), temp, GL_STATIC_DRAW);
    //Generate ibo for object (index buffer)
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned), m_indices.data(), GL_STATIC_DRAW);
    //set vertex attrib pointers

    //Get uniform location once and store since we won't be changing shaders or anything like that.
    m_uniformLocation =  glGetUniformLocation(program, "mvMatrix");

    GLint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(0));
    GLint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(vec4)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void Object::Draw(GLint program) {
    //view cube from -5 units away in the z direction
    mat4 mv = GetTransform();
    glUniformMatrix4fv(m_uniformLocation, 1, GL_TRUE, mv);
    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
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
