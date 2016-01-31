attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 outColor;

uniform mat4 mvMatrix;
void
main()
{
    gl_Position = mvMatrix * vPosition ;
    outColor = vColor;
}
