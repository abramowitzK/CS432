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
        m_speed+=1;
    }
    inline void DecrementSpeed(){
        m_speed-=1;
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
    inline void SetGouraud(bool shading){
        if(shading) {
            m_gouraud = true;
            m_usePhong = false;
        }
        else {
            m_usePhong = true;
            m_gouraud = false;
        }
    }
    inline void SetMat(int mat){
        m_mat = mat;
    }
    inline void IncrementAngle(){
        m_lightAngle+=0.2;
    }
    inline void DecrementAngle(){
        m_lightAngle-=0.2;
    }
    inline void IncrementHeight(){
        m_lightHeight+=0.05;
    }
    inline void DecrementHeight(){
        m_lightHeight-=0.05;
    }
    inline void IncrementLightRadius(){
        m_lightRadius += 0.1;
    }
    inline void DecrementLightRadius(){
        m_lightRadius-=0.1;
    }

private:
    GLint m_mat;
    bool m_para;
    bool m_stop;
    bool m_gouraud;
    bool m_usePhong;
    Mesh m_mesh;
    vec4 m_translation;
    vec3 m_rotation;
    vec3 m_scale;
    vec3 m_lightLocation;
    GLuint m_ibo;
    GLuint m_vbo;
    GLint m_mLocation;
    GLint m_vLocation;
    GLint m_pLocation;
    GLint m_gouraudLocation;
    GLint m_usePhongLocation;
    GLint m_fViewLocation;
    GLint m_vMatLocation;
    GLint m_fMatLocation;
    GLint m_vlightPosLocation;
    GLint m_flightPosLocation;
    vec4 m_eye;
    float m_radius;
    float m_height;
    float m_speed;
    float m_lightRadius;
    float m_lightHeight;
    float m_lightAngle;
};


#endif //ASSIGNMENT4_OBJECT_H
