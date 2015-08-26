#version 400
const int MAX_NUM_LIGHTS = 8; // max number of lights

in vec3 VexterPosEye;
in vec2 TexCoord;
in vec3 ViewDir;
in vec3 LightDirStaticTan;


uniform vec3 LightColor;
uniform float LightDiffuseIntensity;
uniform float LightAmbientIntensity;

struct MaterialInfo
{
	vec3 Ka;            // Ambient reflectivity
	vec3 Ks;            // Specular reflectivity
	float Shininess;    // Specular shininess factor
};
//uniform MaterialInfo Material;

layout(location = 0) out vec4 FragColor;

// Const Section
const float QNConstFloatNode0 = 0;

const float QNConstFloatNode1 = 1;

const float QNConstFloatNode2 = 0.1;


// Textures Section
uniform sampler2D QNTextureNode0;

uniform sampler2D QNTextureNode1;


// Functions Section
vec4 Lerp0()
{
	vec4 ValX = vec4(QNConstFloatNode0);
	vec4 Valy = vec4(QNConstFloatNode1);
	vec4 t = vec4(QNConstFloatNode2);
	return mix(ValX, Valy, t);
}

vec4 Multiply0()
{
	vec4 A = vec4(Lerp0());
	vec4 B = vec4(texture(QNTextureNode0, TexCoord));
	return A * B;
}


vec3 BlinnPhong(vec3 diffR, vec3 norm, vec3 specularLvl, float Shininess)
{

	// this is blinn phong
	vec3 h = normalize(LightDirStaticTan + ViewDir);

	vec3 ambient = (LightAmbientIntensity *  LightColor);

	float sDotN = max(dot(LightDirStaticTan, norm), 0.0);

	vec3 diffuse = (LightDiffuseIntensity *  LightColor) * diffR * sDotN;

	vec3 spec = vec3(0.0);

	if (sDotN > 0.0)
		spec = LightColor * specularLvl * pow(max(dot(h, norm), 0.0), Shininess);

	return ambient + diffuse + spec;
}
void main() 
{

	vec4 colorBase = vec4(Multiply0());
	vec4 specularLvl = vec4(vec4(0.55));
	vec4 normal = 2 * vec4( texture(QNTextureNode1, TexCoord))-1;
	vec4 alpha = vec4(vec4(1.0));
	vec4 lightIntensity = vec4(0.0);
	float shininess = 25;

	lightIntensity += BlinnPhong(colorBase.rgb, normal.rgb, specularLvl.rgb, shininess);
	FragColor = lightIntensity;
	FragColor.a = alpha.r;
}