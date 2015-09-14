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
const float SPC_ConstFloatNode0 = 0.3;


// Textures Section
uniform sampler2D SPC_TextureNode0;


// Functions Section
vec4 SPC_MultiplyNode0()
{
	vec4 A = vec4(texture(SPC_TextureNode0, TexCoord));
	vec4 B = vec4(SPC_ConstFloatNode0);
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

	vec4 colorBase = vec4(SPC_MultiplyNode0());
	vec4 specularLvl = vec4(vec4(0.55));
	vec4 normal = 2 * vec4( vec4(0.48, 0.48, 0.99, 1))-1;
	vec4 alpha = vec4(vec4(1.0));
	vec4 lightIntensity = vec4(0.0);
	float shininess = 25;

	lightIntensity += BlinnPhong(colorBase.rgb, normal.rgb, specularLvl.rgb, shininess);
	FragColor = lightIntensity;
	FragColor.a = alpha.r;
}