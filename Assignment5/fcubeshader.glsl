varying vec4 outColor;
varying mat4 model;
varying vec4 fVertex;
varying vec3 fNormal;
uniform int fMaterial;
uniform bool usePhong;
uniform mat4 fView;
uniform vec3 flight2pos;
vec3 LightPos1 = vec3(0.0, 0.0, 0.0);
vec3 LightPos2 = flight2pos;
struct Materialf{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    float shinyness;
};
Materialf fm1 = Materialf(vec4(0.1,0.0,0.0,1.0), vec4(1.0,0.0,0.0,1.0), vec4(1.0,0.8,0.8,1.0), 10.0);
Materialf fm2 = Materialf(vec4(0.0,0.1,0.0,1.0), vec4(0.0,1.0,0.0,1.0), vec4(0.0,0.0,0.0,1.0), 1.0);
Materialf fm3 = Materialf(vec4(0.0,0.0,0.3, 1.0), vec4(0.0,0.0,1.0,1.0), vec4(0.5,0.5,1.0,1.0), 2.0);
void main()
{
    Materialf mat;
    if(fMaterial == 1)
        mat = fm1;
    else if(fMaterial == 2)
        mat = fm2;
    else
        mat = fm3;
    if(usePhong){
        vec4 transformed = fView*model*fVertex;
        vec4 transformed2 = model*fVertex;
        vec3 normalDirection = normalize((fView*model*vec4(fNormal,0.0)).xyz);
        vec3 normalDirection2 = normalize((model*vec4(fNormal,0.0)).xyz);
        vec3 viewDirection = normalize(vec3(fView *model * fVertex));
        vec3 viewDirection2 = normalize(vec3(model*fVertex));
        vec3 positionToLightSource = vec3(LightPos1 - transformed.xyz);
        vec3 positionToLightSource2 = vec3(LightPos2 - transformed2.xyz);
        float distance = length(positionToLightSource);
        float distance2 = length(positionToLightSource2);
        vec3 lightDirection = normalize(positionToLightSource);
        vec3 lightDirection2 = normalize(positionToLightSource2);
        float attenuation = (1.0 / (1.0 + (0.2* pow(distance,2))));
        float attenuation2 = (1.0/ (1.0 + (0.2* pow(distance2,2))));
        float diffuse = attenuation * max(0.0, dot(normalDirection, lightDirection));
        diffuse = min(diffuse,1.0);
        float diffuse2 = attenuation2*max(0.0, dot(normalDirection2, lightDirection2));
        diffuse2 = min(diffuse2,1.0);
        vec4 specularReflection;
        vec4 specularReflection2;
        if (dot(normalDirection, lightDirection) < 0.0)
        {
            specularReflection = vec4(0.0, 0.0, 0.0,1.0);
        }
        else{
            vec3 reflectDir = reflect(-lightDirection, normalDirection);
            specularReflection = attenuation * mat.specularColor *
            pow(max(0.0, dot(reflectDir, normalize(-viewDirection))), mat.shinyness);
            specularReflection = min(specularReflection,1.0);
        }
        if (dot(normalDirection2, lightDirection2) < 0.0)
        {
            specularReflection2 = vec4(0.0, 0.0, 0.0,1.0);
        }
        else{
            vec3 reflectDir = reflect(-lightDirection2, normalDirection2);
            specularReflection2 = attenuation2 * mat.specularColor *
            pow(max(0.0, dot(reflectDir, normalize(-viewDirection2))), mat.shinyness);
            specularReflection2 = min(specularReflection2,1.0);
        }
        gl_FragColor = mat.diffuseColor*diffuse + mat.ambientColor + specularReflection+ mat.diffuseColor*diffuse2 + specularReflection2;
    }
    else
        gl_FragColor = outColor;
}
