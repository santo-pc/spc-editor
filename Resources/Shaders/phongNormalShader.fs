#version 400

in vec3 VexterPosEye;
in vec2 TexCoord;
in vec3 ViewDir;
in vec3 LightDirStaticTan;


uniform sampler2D ColorTex;
uniform sampler2D NormalMapTex;
uniform sampler2D SpecularMapTex;
uniform vec3 LightColor;
uniform float LightDiffuseIntensity;
uniform float LightAmbientIntensity;


layout(location = 0) out vec4 FragColor;


vec3 BlinnPhong(vec3 diffR, vec3 norm, vec3 specularLvl, float Shininess)
{

	/*float diffuseIntensity = 0.80;
	float ambientIntensity = 0.82;
	float shininess = 25;
	vec3 lighColor = vec3(0.7, 0.7, 0.7);
	*/
	// this is blinn phong
	vec3 h = normalize(LightDirStaticTan + ViewDir);

	vec3 ambient = (LightAmbientIntensity *  LightColor);

	float sDotN = max(dot(LightDirStaticTan, norm), 0.0);

	vec3 diffuse = (LightDiffuseIntensity *  LightColor) * diffR * sDotN;

	vec3 spec = vec3(0.0);

	if (sDotN > 0.0)
		spec = LightColor * specularLvl * pow(max(dot(h, norm), 0.0), Shininess);



	//diffuse = vec3(0.0);
	//ambient = vec3(0.0);

	//return vec3(1.0, 0.0, 0.0); /*+  /*diffuse /*+ spec*/;
	return ambient + diffuse + spec;
}



void main()
{
	// Lookup the normal and color from the normal map and diffuse map
	vec4 normal = 2 * texture(NormalMapTex, TexCoord) - 1.0;
	//vec4 normal = texture( NormalMapTex, TexCoord );	

	vec4 texColor = texture(ColorTex, TexCoord);

	vec4 specularLvl = texture(SpecularMapTex, TexCoord);

	vec4 TotalLight = vec4(0.0);

	FragColor = vec4(0.0);

	TotalLight += vec4(BlinnPhong(texColor.rgb, normal.rgb, specularLvl.rgb, 25), 1.0);


	FragColor = TotalLight;// * texColor;	
	//FragColor = texColor;
	//FragColor = texture( NormalMapTex, TexCoord );
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);	

	FragColor.a = 1;


}
//layout(location = 0) out vec4 FragColor;
/*in vec3 LightDirStaticTan;
in vec3 varNormal;
in vec3 ViewDir;


void main()
{
    vec3 varNormal = vec4(2 * texture(NormalMapTex, TexCoord) - 1.0).rgb;
	// set important material values
    float roughnessValue = 0.3; // 0 : smooth, 1: rough
    float F0 = 0.8; // fresnel reflectance at normal incidence
    float k = 0.2; // fraction of diffuse reflection (specular reflection = 1 - k)
    vec3 lightColor = vec3(0.9, 0.1, 0.1);
    
    // interpolating normals will change the length of the normal, so renormalize the normal.
    vec3 normal = normalize(varNormal);
    
    // do the lighting calculation for each fragment.
    float NdotL = max(dot(normal, LightDirStaticTan), 0.0);
    
    float specular = 0.0;
    if(NdotL > 0.0)
    {
        vec3 eyeDir = normalize(ViewDir);

        // calculate intermediary values
        vec3 halfVector = normalize(LightDirStaticTan + eyeDir);
        float NdotH = max(dot(normal, halfVector), 0.0); 
        float NdotV = max(dot(normal, eyeDir), 0.0); // note: this could also be NdotL, which is the same value
        float VdotH = max(dot(eyeDir, halfVector), 0.0);
        float mSquared = roughnessValue * roughnessValue;
        
        // geometric attenuation
        float NH2 = 2.0 * NdotH;
        float g1 = (NH2 * NdotV) / VdotH;
        float g2 = (NH2 * NdotL) / VdotH;
        float geoAtt = min(1.0, min(g1, g2));
     
        // roughness (or: microfacet distribution function)
        // beckmann distribution function
        float r1 = 1.0 / ( 4.0 * mSquared * pow(NdotH, 4.0));
        float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
        float roughness = r1 * exp(r2);
        
        // fresnel
        // Schlick approximation
        float fresnel = pow(1.0 - VdotH, 5.0);
        fresnel *= (1.0 - F0);
        fresnel += F0;
        
        specular = (fresnel * geoAtt * roughness) / (NdotV * NdotL * 3.14);
    }
    
    vec3 finalValue = lightColor * NdotL * (k + specular * (1.0 - k));
    gl_FragColor  = vec4(finalValue, 1.0);
}*/