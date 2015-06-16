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

uniform float AtteConstantTest;
uniform float AtteLinearTest;
uniform float AtteExpTest;

struct PointLightInfo 
{
	vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;
	vec4  Position;	    // Eye coords
	float AtteConstant;
	float AtteLinear;
	float AtteExp;
};

uniform PointLightInfo Light[MAX_NUM_LIGHTS];

struct MaterialInfo 
{
  vec3 Ka;            // Ambient reflectivity
  vec3 Ks;            // Specular reflectivity
  float Shininess;    // Specular shininess factor
};
uniform MaterialInfo Material;

layout( location = 0 ) out vec4 FragColor;


vec3 CWShading(int lightIndex, vec3 diffR, vec3 norm, vec3 specularLvl)
{
	
	float diffuseIntensity = 0.50;
	float ambientIntensity = 0.52;
	vec3 lighColor = vec3(0.7, 0.7, 0.7);
	
	// this is blinn phong
	vec3 h = normalize(LightDirStaticTan + ViewDir); 
    
	vec3 ambient = (ambientIntensity *  lighColor) * Material.Ka;

    float sDotN = max( dot(LightDirStaticTan, norm), 0.0 );
    
	vec3 diffuse = (diffuseIntensity *  lighColor) * diffR * sDotN;

    vec3 spec = vec3(0.0);
    
	if( sDotN > 0.0 )
		spec =  lighColor * specularLvl * pow(max(dot(h,norm), 0.0), Material.Shininess);	
			
    return ambient +  diffuse + spec;
}


float CalcAttenuation(int i)
{
		float Distance = length(VexterPosEye - Light[i].Position.xyz);
			
		//float Attenuation = AtteConstantTest +  AtteLinearTest * Distance +  AtteExpTest * Distance * Distance;
		
		//float Attenuation = 0.005 +  0.00001 * Distance +  0.000005 * Distance * Distance;
		float Attenuation = 0.005 +  0.00001 * Distance +   0.000005 * Distance * Distance;  // Si sube esto mas oscuro
		//float Attenuation = 0.05 +  0.000001 * Distance +  0.00005 * Distance * Distance;
	
	
		//float Attenuation = Light[i].AtteConstant +  Light[i].AtteLinear * 
		//		Distance +  Light[i].AtteExp * Distance * Distance;
		
				
		return Attenuation;
}

vec4 CalcPointLight(int Index, vec3 diffuse, vec3 normal, vec3 specularLvl)
{
    vec3 Color = CWShading(Index, diffuse, normal, specularLvl);    
	return vec4(Color, 1.0); 
}

void main() 
{
    // Lookup the normal and color from the normal map and diffuse map
    vec4 normal = 2 * texture( NormalMapTex, TexCoord ) - 1.0;	
	
	vec4 texColor = texture( ColorTex, TexCoord );
	
	vec4 specularLvl = texture( SpecularMapTex, TexCoord );
	
	vec4 TotalLight =  vec4(0.0);// noise4(normal.x); // vec4(0.0);
	
	vec4 colorAux = vec4(0.0);
	
	FragColor = vec4(0.0);
	
	
	TotalLight += CalcPointLight(0, texColor.rgb, normal.rgb, specularLvl.rgb);		
	
	
	FragColor = TotalLight * texColor;	
	//FragColor = normal;
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);	
	
	FragColor.a = 1;
		
		
}