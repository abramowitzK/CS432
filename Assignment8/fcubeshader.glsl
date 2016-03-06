varying mat4 model;
varying vec4 fVertex;
varying vec3 fNormal;
uniform mat4 fView;
uniform int color;
uniform bool fbo;
vec3 LightPos1 = vec3(0.0, 0.0, 0.0);
struct Materialf{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
    float shinyness;
};
Materialf fm1 = Materialf(vec4(0.4,0.0,0.0,1.0), vec4(1.0,0.0,0.0,1.0), vec4(1.0,0.8,0.8,1.0), 10.0);
Materialf fm2 = Materialf(vec4(0.0,0.4,0.0,1.0), vec4(0.0,1.0,0.0,1.0), vec4(0.8,1.0,0.8,1.0), 10.0);
Materialf fm3 = Materialf(vec4(0.0,0.0,0.4,1.0), vec4(0.0,0.0,1.0,1.0), vec4(0.8,0.8,1.0,1.0), 10.0);
Materialf fm4 = Materialf(vec4(0.0,0.0,0.0,1.0), vec4(0.0,0.0,0.0,1.0), vec4(1.0,1.0,1.0,1.0), 10.0);
void main()
{
    Materialf mat;
    if(color == 0)
        mat = fm1;
    else if (color == 1)
        mat = fm2;
    else if (color == 2)
        mat = fm3;
    else
        mat = fm4;

    vec4 transformed = fView*model*fVertex;
    vec3 normalDirection = normalize((fView*model*vec4(fNormal,0.0)).xyz);
    vec3 viewDirection = normalize(vec3(fView *model * fVertex));
    vec3 positionToLightSource = vec3(LightPos1 - transformed.xyz);
    float distance = length(positionToLightSource);
    vec3 lightDirection = normalize(positionToLightSource);
    float attenuation = (100.0 / (1.0 + (pow(distance,2))));
    float diffuse = attenuation * max(0.0, dot(normalDirection, lightDirection));
    diffuse = min(diffuse,1.0);
    vec4 specularReflection;

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
    if(!fbo)
        gl_FragColor = mat.diffuseColor*diffuse + mat.ambientColor + specularReflection;
    else
        gl_FragColor = mat.diffuseColor;
}
