attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec3 vNormal;

varying vec4 outColor;
varying mat4 model;
varying mat4 view;
varying vec4 fVertex;
varying vec3 fNormal;


//Just the m matrix. We can't use the view matrix with lighting calcs because it will change
//Based on camera location and orientation
uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;
uniform bool gouraud;
uniform int vMaterial;
uniform vec3 vlight2pos;
uniform vec4 flatColor;
vec3 LightPos1 = vec3(0.0, 0.0, 0.0);
struct Material{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    float shinyness;
};
Material m1 = Material(vec4(0.1,0.0,0.0,1.0), vec4(1.0,0.0,0.0,1.0), vec4(1.0,0.8,0.8,1.0), 20.0);
Material m2 = Material(vec4(0.0,0.1,0.0,1.0), vec4(0.0,1.0,0.0,1.0), vec4(0.0,0.0,0.0,1.0), 1.0);
Material m3 = Material(vec4(0.0,0.0,0.3, 1.0), vec4(0.0,0.0,1.0,1.0), vec4(0.5,0.5,1.0,1.0), 2.0);
void main()
{
    Material mat;
    if(vMaterial == 1)
        mat = m1;
    else if(vMaterial == 2)
        mat = m2;
    else
        mat = m3;
    if(gouraud){
        mat4 modelView = vMatrix*mMatrix;
        //LightPos1 = (modelView * vec4(LightPos1,1.0)).xyz;
        mat4 normalMatrix = mMatrix;
        //Transform the normal and the vertex into camera coordinates. Don't apply projection.
        vec4 transformed= (modelView*vPosition);
        //vec4 transformed2 =mMatrix * vPosition;
        //vec3 transformedVertex2 = (transformed2.xyz)/transformed2.w;
        vec3 transformedVertex = vec3(transformed)/transformed.w;
        vec3 transformedNormal = normalize((modelView*vec4(vNormal,0.0)).xyz);
        //vec3 transformedNormal2 = normalize((mMatrix*vec4(vNormal,0.0)).xyz);//normalize((mMatrix*vec4(vNormal,0.0))).xyz;
        //Calculate the distance from the lights to the vertex after it's been transformed
        float distance = length(LightPos1 - transformedVertex);
        //float distance2 = length(LightPos2 - transformedVertex2);
        //Get the vector from vertex to light
        vec3 lightVector = normalize(LightPos1 - transformedVertex);
        //vec3 lightVector2 = normalize(LightPos2 - transformedVertex2);
        //Calculate the diffuse coefficient using inverse square law and dot prod
        float diffuse = max(dot(transformedNormal, lightVector), 0.0);
        //float diffuse2 = max(dot(transformedNormal2, lightVector2), 0.0);
        float attenuation = (100.0 / (1.0 + ( pow(distance,2))));
        //float attenuation2 = (1.0/ (1.0 + (0.2* pow(distance2,2))));
        diffuse = diffuse * attenuation;
        //diffuse2 = diffuse2 * attenuation2;
        //Set the final color
        outColor = mat.ambientColor +
        +mat.diffuseColor*diffuse;
        //+mat.diffuseColor* diffuse2;
    }
    else{
        model = mMatrix;
        view = vMatrix;
        fVertex = ( vPosition);
        fNormal = (vec4(vNormal,0.0)).xyz;
        outColor = mat.diffuseColor;
    }

    gl_Position =  pMatrix * vMatrix * mMatrix * vPosition ;
}
