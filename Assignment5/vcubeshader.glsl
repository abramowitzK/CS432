attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec3 vNormal;

varying vec4 outColor;

//Just the m matrix. We can't use the view matrix with lighting calcs because it will change
//Based on camera location and orientation
uniform mat4 mvMatrix;
//mv and p matrix
uniform mat4 pMatrix;

vec3 LightPos1 = vec3(0.75, 0.0, 0.75);
vec3 LightPos2 = vec3(-0.75, 0.0, -0.75);
void main()
{
    //Transform the normal and the vertex into camera coordinates. Don't apply projection.
    vec3 transformedVertex = (mvMatrix*vPosition).xyz;
    vec3 transformedNormal = (mvMatrix*vec4(vNormal,0.0)).xyz;
    //Calculate the distance from the lights to the vertex after it's been transformed
    float distance = length(LightPos1 - transformedVertex);
    float distance2 = length(LightPos2 - transformedVertex);
    //Get the vector from vertex to light
    vec3 lightVector = normalize(LightPos1 - transformedVertex);
    vec3 lightVector2 = normalize(LightPos2 - transformedVertex);
    //Calculate the diffuse coefficient using inverse square law and dot prod
    float diffuse = max(dot(transformedNormal, lightVector), 0.15);
    diffuse = diffuse * (1.0 / (1.0 + (0.2 * pow(distance,2))));
    float diffuse2 = max(dot(transformedNormal, lightVector2), 0.15);
    diffuse2 = diffuse2 * (1.0/(1.0 + (0.3 * pow(distance2, 2))));
    //Sum the effects of the lights per vertex
    diffuse += diffuse2;
    //Set the final color
    outColor = vColor * diffuse;
    gl_Position =  pMatrix * vPosition ;
}
