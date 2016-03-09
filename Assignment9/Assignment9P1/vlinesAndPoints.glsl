attribute vec4 vPosition;
attribute vec4 vColor;
uniform mat4 mvp;
uniform mat4 p;
uniform bool transform;
varying vec4 outColor;
void main() {
    outColor = vColor;
    if(transform)
        gl_Position = mvp * vPosition;
    else
        gl_Position = p * vPosition;
}
