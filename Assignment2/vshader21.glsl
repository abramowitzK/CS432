attribute vec4 vPosition;
attribute vec4 vColor;
varying vec4 outColor;
void
main()
{
    gl_Position = vPosition;
    outColor = vColor;
}
