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
    inline void IncrementSpeed(){
        m_speed+=0.1;
    }
    inline void DecrementSpeed(){
        m_speed-=0.1;
    }
    inline void IncreaseHeight(){
        m_height += 0.1;
    }
    inline void DecreaseHeight(){
        m_height -= 0.1;
    }
    inline void IncreaseRadius(){
        m_radius += 0.3;
    }
    inline void DecreaseRadius(){
        m_radius -= 0.3;
    }
    inline void Stop(){
        m_stop = true;
    }
    inline void Start(){
        m_stop = false;
    }
    inline void SetPara(bool para){
        m_para = para;
    }


private:
    bool m_para;
    bool m_stop;
    Mesh m_mesh;
    vec4 m_translation;
    vec3 m_rotation;
    vec3 m_scale;
    GLuint m_ibo;
    GLuint m_vbo;
    GLint m_mvLocation;
    GLint m_mvpLocation;
    vec4 m_eye;
    float m_radius;
    float m_height;
    float m_speed;
};


#endif //ASSIGNMENT4_OBJECT_H
