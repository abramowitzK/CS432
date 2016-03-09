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
    m_vbo = 0;
    m_ibo = 0;
    m_mesh = mesh;
    m_stop = false;
    m_radius = 25;
    m_para = false;
    m_speed = 0.1;
    m_height = 10.0;
    m_eye = vec4(-15.0, 15.0, 10.0, 1.0);
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
}
void Object::SetControlPoints(std::vector<Vertex3D> points){
    m_control = points;
}
void Object::Init(GLuint program, BezierPointReader rdr) {

    m_program = Angel::InitShader("vlinesAndPoints.glsl","flinesAndPoints.glsl");
    SetControlPoints(rdr.GetControlPoints());
    m_control[0].Color = vec4(0.0,0.0,1.0,1.0);
    auto temp = MakeAxes();
    m_control.insert(m_control.end(), temp.begin(), temp.end());
    glUseProgram(m_program);
    glLineWidth(5);
    glGenBuffers(1,&m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_control.size()*sizeof(Vertex3D), m_control.data(), GL_STATIC_DRAW);
    GLint vPosition = glGetAttribLocation(m_program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(0));
    GLint vColor = glGetAttribLocation(m_program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(vec4)));
    GLint vNormal = glGetAttribLocation(m_program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(vec4)*2));
    m_linePLocation = glGetUniformLocation(m_program, "p");
    m_lineBoolLocation = glGetUniformLocation(m_program, "transform");
    m_lineMVPLocation = glGetUniformLocation(m_program, "mvp");
    glUseProgram(program);
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
    glUseProgram(program);
    glUniform1i(m_gouraudLocation, m_gouraud);
    glUniform1i(m_usePhongLocation, m_usePhong);
    glUniform1i(m_vMatLocation, m_mat);
    glUniform1i(m_fMatLocation, m_mat);
    glUniform3fv(m_vlightPosLocation,1,m_lightLocation);
    glUniform3fv(m_flightPosLocation,1,m_lightLocation);
    mat4 v = Angel::LookAt(m_eye, vec4(3.0,3.0,0.0, 1.0), vec4(0.0,1.0,0.0,1.0));
    glUniformMatrix4fv(m_mLocation, 1, GL_TRUE, GetTransform());

    mat4 proj;
    if(!m_para)
        proj = Angel::Perspective(30.0f, 1.0, 0.1f, 1000.0f);
    else
        proj= Angel::Ortho(-1.0, 1.0, -1.0, 1.0, 0.1f, 1000.0f);
    glUniformMatrix4fv(m_vLocation, 1, GL_TRUE,  v);
    glUniformMatrix4fv(m_fViewLocation, 1, GL_TRUE, v);
    glUniformMatrix4fv(m_pLocation,1, GL_TRUE, proj);
    glUseProgram(m_program);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo );
    GLint vPosition = glGetAttribLocation(m_program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(0));
    GLint vColor = glGetAttribLocation(m_program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(vec4)));
    GLint vNormal = glGetAttribLocation(m_program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), BUFFER_OFFSET(sizeof(vec4)*2));
    glUniformMatrix4fv(m_lineMVPLocation, 1, GL_TRUE, proj*v*GetTransform());
    glUniform1i(m_lineBoolLocation, GL_TRUE);
    glDrawArrays(GL_POINTS, 0, 16);
    glUniformMatrix4fv(m_linePLocation, 1, GL_TRUE, proj*v);
    glUniform1i(m_lineBoolLocation, GL_FALSE);
    glDrawArrays(GL_LINES, 16,6);
    m_mesh.Draw(program);
}

void Object::Update(float time, BezierPointReader rdr) {

    float x = m_radius * cosf(time / 360.0 * m_speed);
    float z = m_radius * sinf(time / 360.0 * m_speed);
    m_eye.x = x;
    m_eye.z = z;
    m_eye.y = m_height;
    m_lightLocation.x = cosf(m_lightAngle)*m_lightRadius;
    m_lightLocation.y = m_lightHeight;
    m_lightLocation.z = sinf(m_lightAngle)*m_lightRadius;

}
void Object::UpdatePoints(BezierPointReader rdr){
    SetControlPoints(rdr.GetControlPoints());
    auto temp = MakeAxes();
    m_control.insert(m_control.end(), temp.begin(), temp.end());
    m_control[index%16].Color = vec4(0.0,0.0,1.0,1.0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_control.size()*sizeof(Vertex3D), m_control.data(), GL_STATIC_DRAW);

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

void Object::ChangeMesh(Mesh mesh, GLuint program){
    m_mesh = mesh;
    m_mesh.Init(program);
}
std::vector<Vertex3D> Object::MakeAxes(){
    std::vector<Vertex3D> verts(6);
    verts[0].Position = vec4(0.0,0.0,0.0,1.0);
    verts[0].Color = vec4(1.0,0.0,0.0,1.0);
    verts[1].Position  = vec4(-10.0,0.0,0.0,1.0);
    verts[1].Color = vec4(1.0,0.0,0.0,1.0);
    verts[2].Position  = vec4(0.0,0.0,0.0,1.0);
    verts[2].Color = vec4(0.0,1.0,0.0,1.0);
    verts[3].Position  = vec4(0,10.0,0.0,1.0);
    verts[3].Color = vec4(0.0,1.0,0.0,1.0);
    verts[4].Position  = vec4(0.0,0.0,0.0,1.0);
    verts[4].Color = vec4(0.0,0.0,1.0,1.0);
    verts[5].Position  = vec4(0.0,0.0,-10.0,1.0);
    verts[5].Color = vec4(0.0,0.0,1.0,1.0);
    return verts;
}

