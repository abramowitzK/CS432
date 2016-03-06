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
#include "BezierPointReader.h"

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
        if(m_radius > 15.0)
            m_radius -= 0.3;
    }
    inline void IncreaseAngle(){
        m_angle += 0.05;
    }
    inline void DecreaseAngle(){
        m_angle -= 0.05;
    }
    inline void SetColor(int i){
        m_color = i;
    }
    inline void Select(){
        m_selected = true;
    }
    inline void Unselect(){
        m_selected = false;
    }
    void DrawToFBO(GLint program);


private:
    unsigned int index = 0;
    Mesh m_mesh;
    vec4 m_translation;
    vec3 m_rotation;
    vec3 m_scale;
    GLint m_mLocation;
    GLint m_vLocation;
    GLint m_pLocation;
    GLint m_fViewLocation;
    GLint m_colorLocation;
    GLint m_fboLocation;
    vec4 m_eye;
    bool m_selected;
    int m_color;
    float m_radius;
    float m_height;
    float m_speed;
    float m_angle;
};


#endif //ASSIGNMENT4_OBJECT_H
