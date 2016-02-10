attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec3 vNormal;

varying vec4 outColor;

uniform mat4 mvMatrix;
uniform mat4 pMatrix;

vec3 LightPos1 = vec3(1.0, 0.0, 0.0);
vec3 LightPos2 = vec3(-0.75, 0.0, 0.0);
void main()
{
    //Transform the normal and the vertex into camera coordinates. Don't apply projection.
    vec3 transformedVertex = vec3(mvMatrix*vPosition);
    vec3 transformedNormal = vec3(mvMatrix*vec4(vNormal,0.0));
    float distance = length(LightPos1 - transformedVertex);
    float distance2 = length(LightPos2 - transformedVertex);
    vec3 lightVector = normalize(LightPos1 - transformedVertex);
    vec3 lightVector2 = normalize(LightPos2 - transformedVertex);
    float diffuse = max(dot(transformedNormal, lightVector), 0.2);
    diffuse = diffuse * (1.0 / (1.0 + (0.05 * distance * distance)));
    float diffuse2 = max(dot(transformedNormal, lightVector), 0.3);
    diffuse2 = diffuse2 * (1.0/(1.0 + (0.01 * distance2 * distance2)));
    diffuse += diffuse2;
    outColor = vColor * diffuse;
    gl_Position =  pMatrix * vPosition ;
}
