#version 400

in vec3 VexterPosEye;
in vec2 TexCoord;
in vec3 ViewDir;
in vec3 LightDirStaticTan;

uniform vec3 LightColor;
uniform float LightDiffuseIntensity;
uniform float LightAmbientIntensity;
layout(location = 0) out vec4 FragColor;

// Const Section
const vec4 SPC_Vector4DNode0 = vec4(0, 1, 0, 0);

const float SPC_ConstFloatNode0 = 50;


// Textures Section
uniform sampler2D SPC_TextureNode0;

uniform sampler2D SPC_TextureNode1;

uniform sampler2D SPC_TextureNode2;

uniform sampler2D SPC_TextureNode3;

uniform sampler2D SPC_TextureNode4;


// Functions Section
vec4 SPC_LerpNode0()
{
	vec4 ValX = vec4(texture(SPC_TextureNode0, TexCoord));
	vec4 Valy = vec4(SPC_Vector4DNode0);
	vec4 t = vec4(texture(SPC_TextureNode1, TexCoord).r);
	return mix(ValX, Valy, t);
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

	vec4 colorBase = vec4(SPC_LerpNode0());
	vec4 specularLvl = vec4(texture(SPC_TextureNode2, TexCoord));
	vec4 normal = 2 * vec4( texture(SPC_TextureNode3, TexCoord))-1;
	vec4 alpha = vec4(texture(SPC_TextureNode4, TexCoord));
	vec4 lightIntensity = vec4(0.0);
	float shininess = SPC_ConstFloatNode0;

	lightIntensity += BlinnPhong(colorBase.rgb, normal.rgb, specularLvl.rgb, shininess);
	FragColor = lightIntensity;
	FragColor.a = alpha.r;
}