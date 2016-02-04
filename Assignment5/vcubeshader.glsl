attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec3 vNormal;

varying vec4 outColor;
varying vec4 outVert;
varying vec3 outNorm;

uniform mat4 mvMatrix;
void
main()
{
    gl_Position = mvMatrix * vPosition ;
    outColor = vColor;
}
