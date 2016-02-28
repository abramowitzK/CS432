uniform int color;
void main(){
    vec4 c;
    if(color == 0)
        c = vec4(1.0,0.0,0.0,1.0);
    else if( color == 1)
        c = vec4(0.0,1.0,0.0,1.0);
    else if( color == 2)
        c = vec4(0.0,0.0,1.0,1.0);
    gl_FragColor = c;
}