#version 400
const int MAX_NUM_LIGHTS = 8; // max number of lights

in vec3 LightDir[MAX_NUM_LIGHTS];
in vec3 VexterPosEye;
in vec2 TexCoord;
in vec3 ViewDir;
in vec3 LightDirStaticTan;

uniform sampler2D ColorTex;
uniform sampler2D NormalMapTex;
uniform sampler2D SpecularMapTex;

uniform int Model;
uniform int LightsCount;  // actual number of lights 


struct MaterialInfo
{
	vec3 Ka;            // Ambient reflectivity
	vec3 Ks;            // Specular reflectivity
	float Shininess;    // Specular shininess factor
};
//uniform MaterialInfo Material;

layout(location = 0) out vec4 FragColor;

// Const Section

// Textures Section

// Functions Section

vec3 BlinnPhong(int lightIndex, vec3 diffuseRef, vec3 norm, vec3 specularLvl)
{
	MaterialInfo Material;
	Material.Ka = vec3(0.3);
	Material.Ks = vec3(0.2);
	Material.Shininess = 25;
	float diffuseIntensity = 0.50;
	float ambientIntensity = 0.52;
	vec3 lighColor = vec3(0.7, 0.7, 0.7);

	// this is blinn phong
	vec3 h = normalize(LightDirStaticTan + ViewDir);

	vec3 ambient = (ambientIntensity *  lighColor) * Material.Ka;

	float sDotN = max(dot(LightDirStaticTan, norm), 0.0);

	vec3 diffuse = (diffuseIntensity *  lighColor) * diffuseRef * sDotN;

	vec3 spec = vec3(0.0);

	if (sDotN > 0.0)
		spec = lighColor * specularLvl * pow(max(dot(h, norm), 0.0), Material.Shininess);

	return ambient + diffuse + spec;
}
void main() 
{	vec4 colorBase = vec4(NO CONNECTION MADE);
	vec4 specularLvl = vec4(NO CONNECTION MADE);
	vec4 normal = vec4(NO CONNECTION MADE);
	vec4 alpha = vec4(NO CONNECTION MADE);
	vec4 lightIntensity = vec4(0.0);
	vec4 colorAux = vec4(0.0);

	lightIntensity += BlinnPhong(0, colorBase.rgb, normal.rgb, specularLvl.rgb);

	FragColor = lightIntensity;

	FragColor.a = alpha.a;

}
