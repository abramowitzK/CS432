attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec3 vNormal;

varying mat4 model;
varying mat4 view;
varying vec4 fVertex;
varying vec3 fNormal;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

void main()
{
    model = mMatrix;
    view = vMatrix;
    fVertex = (vPosition);
    fNormal = (vec4(vNormal,0.0)).xyz;
    gl_Position =  pMatrix * vMatrix * mMatrix * vPosition ;
}
